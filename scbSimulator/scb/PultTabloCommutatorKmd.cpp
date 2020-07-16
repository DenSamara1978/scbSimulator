#include "PultTabloCommutatorKmd.h"

using namespace scb;

using time::Timer;


PultTabloCommutatorKmd::PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit) :
	PultTabloAbstractCommutator(ownerScheme, color, leftPositionOnBit, leftPositionOffBit, rightPositionOnBit, rightPositionOffBit)
{
	this->switchPosition = -1.0f;
}

PultTabloCommutatorKmd::PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit) :
	PultTabloAbstractCommutator(ownerScheme, color, leftPositionOnBit, leftPositionOffBit, rightPositionOnBit, rightPositionOffBit, onBit, offBit)
{
	this->switchPosition = -1.0f;
}

PultTabloCommutatorKmd::~PultTabloCommutatorKmd()
{

}

void PultTabloCommutatorKmd::initialize()
{
	if (this->switchRightOffContactBit >= 0)
		this->ownerScheme->setStatusBit(this->switchRightOffContactBit);
	if (this->switchLeftOnContactBit >= 0)
		this->ownerScheme->setStatusBit(this->switchLeftOnContactBit);
	if (this->pressOffContactBit >= 0)
		this->ownerScheme->setStatusBit(this->pressOffContactBit);
}

void PultTabloCommutatorKmd::turnCw()
{
	switch (this->switchStatus)
	{
		case 0:
			// Ќачать поворот направо
			if (this->timeStamp == 0)
				this->timeStamp = Timer::getInstance()->getWorkingTime();
			this->switchStatus = 1;
			this->addIdleTimer();
			break;
		case 3:
			// ѕрекратить поворот налево и начать с этого места поворот направо
			this->switchStatus = 1;
			break;
	}
}

void PultTabloCommutatorKmd::turnCcw()
{
	switch (this->switchStatus)
	{
		case 1:
			// ѕрекратить поворот направо и начать с этого места поворот налево
			this->switchStatus = 3;
			break;
		case 2:
			// Ќачать поворот налево
			if (this->timeStamp == 0)
				this->timeStamp = Timer::getInstance()->getWorkingTime();
			this->switchStatus = 3;
			break;
	}
}

void PultTabloCommutatorKmd::idleTimer(unsigned long long time)
{
	int markToDelete = 0xFF;
	float delta = static_cast <float> (time - this->timeStamp);

	// —начала изучаетс€ режим нажати€
	if (this->pressStatus == 1)
	{
		this->pressPosition += delta / this->pressTime;
		if ((this->pressContactStatus == 0) and (this->pressPosition > this->pressOffBorder))
		{
			if (this->pressOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->pressOffContactBit);
			this->pressContactStatus = 1;
		}
		if ((this->pressContactStatus == 1) and (this->pressPosition > this->pressOnBorder))
		{
			if (this->pressOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->pressOnContactBit);
			this->pressContactStatus = 2;
		}
		if (this->pressPosition >= 1.0f)
		{
			this->pressPosition = 1.0f;
			this->pressStatus = 2;
		}
		else
			markToDelete &= 0xFE;
	}
	else if (this->pressStatus == 3)
	{
		this->pressPosition -= delta / this->pressTime;
		if ((this->pressContactStatus == 2) and (this->pressPosition < this->pressOnBorder))
		{
			if (this->pressOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->pressOnContactBit);
			this->pressContactStatus = 1;
		}
		if ((this->pressContactStatus == 1) and (this->pressPosition < this->pressOffBorder))
		{
			if (this->pressOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->pressOffContactBit);
			this->pressContactStatus = 0;
		}
		if (this->pressPosition <= 0.0f)
		{
			this->pressPosition = 0.0f;
			this->pressStatus = 0;
		}
		else
			markToDelete &= 0xFE;
	}

	// «атем изучаетс€ режим поворота
	if (this->switchStatus == 1)
	{
		this->switchPosition += 2.0f * delta / this->switchTime;
		if ((this->switchContactStatus == 0) and (this->switchPosition > -this->switchOnBorder))
		{
			if (this->switchLeftOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchLeftOnContactBit);
			this->switchContactStatus = 1;
		}
		if ((this->switchContactStatus == 1) and (this->switchPosition > -this->switchOffBorder))
		{
			if (this->switchLeftOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchLeftOffContactBit);
			this->switchContactStatus = 2;
		}
		if ((this->switchContactStatus == 2) and (this->switchPosition > this->switchOffBorder))
		{
			if (this->switchRightOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchRightOffContactBit);
			this->switchContactStatus = 3;
		}
		if ((this->switchContactStatus == 3) and (this->switchPosition > this->switchOnBorder))
		{
			if (this->switchRightOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchRightOnContactBit);
			this->switchContactStatus = 4;
		}
		if (this->switchPosition >= 1.0f)
		{
			this->switchPosition = 1.0f;
			this->switchStatus = 2;
		}
		else
			markToDelete &= 0xFD;
	}
	else if (this->switchStatus == 3)
	{
		this->switchPosition -= 2.0f * delta / this->switchTime;
		if ((this->switchContactStatus == 4) and (this->switchPosition < this->switchOnBorder))
		{
			if (this->switchRightOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchRightOnContactBit);
			this->switchContactStatus = 3;
		}
		if ((this->switchContactStatus == 3) and (this->switchPosition < this->switchOffBorder))
		{
			if (this->switchRightOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchRightOffContactBit);
			this->switchContactStatus = 2;
		}
		if ((this->switchContactStatus == 2) and (this->switchPosition < -this->switchOffBorder))
		{
			if (this->switchLeftOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchLeftOffContactBit);
			this->switchContactStatus = 1;
		}
		if ((this->switchContactStatus == 1) and (this->switchPosition < -this->switchOnBorder))
		{
			if (this->switchLeftOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchLeftOnContactBit);
			this->switchContactStatus = 0;
		}
		if (this->switchPosition <= -1.0f)
		{
			this->switchPosition = -1.0f;
			this->switchStatus = 0;
		}
		else
			markToDelete &= 0xFD;
	}

	// удалить себ€ из списка пассивных таймеров
	if (markToDelete == 0xFF)
	{
		this->deleteIdleTimer();
		this->timeStamp = 0;
	}
	else
		this->timeStamp = time;
}
