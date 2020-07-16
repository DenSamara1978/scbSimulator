#include "PultTabloButtonKmdf.h"
#include "AbstractScheme.h"

using namespace scb;

PultTabloButtonKmdf::PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit) :
	PultTabloAbstractButton(ownerScheme, color, onBit)
{
}

PultTabloButtonKmdf::PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit, int offBit) :
	PultTabloAbstractButton(ownerScheme, color, onBit, offBit)
{
}

PultTabloButtonKmdf::~PultTabloButtonKmdf()
{

}

void PultTabloButtonKmdf::initialize()
{
	if (this->offContactBit >= 0)
		this->ownerScheme->setStatusBit(this->offContactBit);
}

void PultTabloButtonKmdf::press()
{
	switch (this->status)
	{
		case 0:
		case 4:
			// инициировать нажатие
			this->timeStamp = this->getWorkingTime();
			this->status++;
			this->addIdleTimer();
			break;
		case 3:
			// прекратить отпускание и с этого места начать нажатие
			this->status = 5;
			break;
		case 7:
			// прекратить отпускание и с этого места начать нажатие
			this->status = 1;
			break;
	}
}

void PultTabloButtonKmdf::release()
{
	switch (this->status)
	{
		case 1:
			// прекратить нажатие и с этого места начать отпускание
			this->status = 7;;
			break;
		case 5:
			// прекратить нажатие и с этого места начать отпускание
			this->status = 3;
			break;
		case 2:
		case 6:
			// инициировать отпускание
			this->timeStamp = this->getWorkingTime();
			this->status++;
			this->addIdleTimer();
			break;
	}

}

void PultTabloButtonKmdf::idleTimer(unsigned long long time)
{
	float delta = static_cast <float> (time - this->timeStamp);
	this->timeStamp = time;
	switch (this->status)
	{
		case 1:
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
			break;
		case 3:
			this->position -= delta / this->pressTime;
			if (this->position > this->fixBorder)
				return;
			else
			{
				this->position = this->fixBorder;
				this->status = 4;
				this->timeStamp = 0;
			}
			break;
		case 5:
			this->position += delta / this->pressTime;
			if (this->position < 1.0f)
				return;
			else
			{
				this->position = 1.0f;
				this->status = 6;
				this->timeStamp = 0;
			}
			break;
		case 7:
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
			break;
	}
	// удалить себя из списка пассивных таймеров
	this->deleteIdleTimer();
}
