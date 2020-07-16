#include "PultTabloButtonKmd.h"
#include "AbstractScheme.h"

using namespace scb;

PultTabloButtonKmd::PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit) :
	PultTabloAbstractButton(ownerScheme, color, onBit)
{
}

PultTabloButtonKmd::PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit, int offBit) :
	PultTabloAbstractButton(ownerScheme, color, onBit, offBit)
{
}

PultTabloButtonKmd::~PultTabloButtonKmd()
{

}

void PultTabloButtonKmd::initialize()
{
	if (this->offContactBit >= 0)
		this->ownerScheme->setStatusBit(this->offContactBit);
}

void PultTabloButtonKmd::press()
{
	switch (this->status)
	{
		case 0:
			// инициировать нажатие
			this->timeStamp = this->getWorkingTime();
			this->status = 1;
			this->addIdleTimer();
			break;
		case 3:
			// прекратить отпускание и с этого места начать нажатие
			this->status = 1;
			break;
	}
}

void PultTabloButtonKmd::release()
{
	switch (this->status)
	{
		case 1:
			// прекратить нажатие и с этого места начать отпускание
			this->status = 3;
			break;
		case 2:
			// инициировать отпускание
			this->timeStamp = this->getWorkingTime();
			this->status = 3;
			this->addIdleTimer();
			break;
	}
}

void PultTabloButtonKmd::idleTimer(unsigned long long time)
{
	float delta = static_cast <float> (time - this->timeStamp);
	this->timeStamp = time;
	if (this->status == 1)
	{
		this->position += delta / this->pressTime;
		if ((this->contactStatus == 0) and (this->position > this->offBorder))
		{
			if (this->offContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->offContactBit);
			this->contactStatus = 1;
		}
		if ((this->contactStatus == 1) and (this->position > this->onBorder))
		{
			if (this->onContactBit >= 0)
				this->ownerScheme->setStatusBit(this->onContactBit);
			this->contactStatus = 2;
		}
		if (this->position < 1.0f)
			return;
		else
		{
			this->position = 1.0f;
			this->status = 2;
			this->timeStamp = 0;
		}
	}
	else if (this->status == 3)
	{
		this->position -= delta / this->pressTime;
		if ((this->contactStatus == 2) and (this->position < this->onBorder))
		{
			if (this->onContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->onContactBit);
			this->contactStatus = 1;
		}
		if ((this->contactStatus == 1) and (this->position < this->offBorder))
		{
			if (this->offContactBit >= 0)
				this->ownerScheme->setStatusBit(this->offContactBit);
			this->contactStatus = 0;
		}
		if (this->position > 0.0f)
			return;
		else
		{
			this->position = 0.0f;
			this->status = 0;
			this->timeStamp = 0;
		}
	}
	// удалить себя из списка пассивных таймеров
	this->deleteIdleTimer();
}
