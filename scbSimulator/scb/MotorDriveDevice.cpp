#include "AbstractScheme.h"
#include "MotorDriveDevice.h"
#include "..\track\Switch.h"

using namespace scb;

MotorDriveDevice::MotorDriveDevice(AbstractScheme* ownerScheme) :
	AbstractSchemeDevice(ownerScheme),
	temperature(20.0f),
	frostAmount1(0.0f),
	frostAmount2(0.0f),
	frostAmount3(0.0f),
	frostAmount4(0.0f),
	flapPosition(0.0f),
	gatePosition(1.0f),
	controlLinePosition(1.0f),
	autoSwitch12Position(-1.0f),
	autoSwitch34Position(1.0f),
	reductorPhase(this->workingSector / 2.0f),
	autoSwitchGap(0.0f),
	motorPhase(0.0f),
	leftSwivelCamPosition(1.0f),
	rightSwivelCamPosition(0.0f),
	flapStatus(0),
	motorStatus(0),
	friction(false),
	leftSwivelCamFalling(false),
	rightSwivelCamFalling(false),
	timeStamp(0),
	trackSwitch(nullptr),
	controlLinePresence(true),
	isGateClose(true)
{
}

MotorDriveDevice::~MotorDriveDevice()
{

}

inline void MotorDriveDevice::recalculateAutoSwitch()
{
	// Находим положение левого автопереключателя ( 1-2 )
	float old = this->autoSwitch12Position;
	if ((this->controlLinePosition > 0.0f) and this->controlLinePresence)
		this->autoSwitch12Position = -this->leftSwivelCamPosition;
	else
		this->autoSwitch12Position = 1.0f - 2.0f * this->leftSwivelCamPosition;

	if ((old < -this->autoSwitchLevel) and (this->autoSwitch12Position > -this->autoSwitchLevel))
		this->ownerScheme->resetStatusBit(this->autoSwitch12PowerBit);
	if ((old > -this->autoSwitchLevel) and (this->autoSwitch12Position < -this->autoSwitchLevel))
		this->ownerScheme->setStatusBit(this->autoSwitch12PowerBit);
	if ((old < this->autoSwitchLevel) and (this->autoSwitch12Position > this->autoSwitchLevel))
		this->ownerScheme->setStatusBit(this->autoSwitch12ControlBit);
	if ((old > this->autoSwitchLevel) and (this->autoSwitch12Position < this->autoSwitchLevel))
		this->ownerScheme->resetStatusBit(this->autoSwitch12ControlBit);

	// Находим положение правого автопереключателя ( 3-4 )
	old = this->autoSwitch34Position;
	if ((this->controlLinePosition < 1.0f) and this->controlLinePresence)
		this->autoSwitch34Position = -this->rightSwivelCamPosition;
	else
		this->autoSwitch34Position = 1.0f - 2.0f * this->rightSwivelCamPosition;

	if ((old < -this->autoSwitchLevel) and (this->autoSwitch34Position > -this->autoSwitchLevel))
		this->ownerScheme->resetStatusBit(this->autoSwitch34PowerBit);
	if ((old > -this->autoSwitchLevel) and (this->autoSwitch34Position < -this->autoSwitchLevel))
		this->ownerScheme->setStatusBit(this->autoSwitch34PowerBit);
	if ((old < this->autoSwitchLevel) and (this->autoSwitch34Position > this->autoSwitchLevel))
		this->ownerScheme->setStatusBit(this->autoSwitch34ControlBit);
	if ((old > this->autoSwitchLevel) and (this->autoSwitch34Position < this->autoSwitchLevel))
		this->ownerScheme->resetStatusBit(this->autoSwitch34ControlBit);
}

void MotorDriveDevice::setSwitch(track::Switch* point)
{
	this->trackSwitch = point;
	if (point != nullptr)
		point->setDrive(this);
}

void MotorDriveDevice::initialize()
{
	this->ownerScheme->setStatusBit(this->autoSwitch12PowerBit);
	this->ownerScheme->setStatusBit(this->autoSwitch34ControlBit);
	this->ownerScheme->setStatusBit(this->lockSwitchBit);
	this->ownerScheme->setStatusBit(this->autoSwitch1FrostBit);
	this->ownerScheme->setStatusBit(this->autoSwitch2FrostBit);
	this->ownerScheme->setStatusBit(this->autoSwitch3FrostBit);
	this->ownerScheme->setStatusBit(this->autoSwitch4FrostBit);
}

void MotorDriveDevice::flapDown()
{
	switch (this->flapStatus)
	{
		case 0:
			// инициировать опускание
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->flapStatus = 1;
			this->addIdleTimer();
			break;
		case 4:
			// прекратить поднятие и с этого места начать опускание
			this->flapStatus = 2;
			break;
		case 5:
			// прекратить поднятие и с этого места начать опускание
			this->flapStatus = 1;
			break;
	}
}

void MotorDriveDevice::flapUp()
{
	switch (this->flapStatus)
	{
		case 3:
			// инициировать поднятие
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->flapStatus = 4;
			this->addIdleTimer();
			break;
		case 1:
			// прекратить опускание и с этого места начать поднятие
			this->flapStatus = 5;
			break;
		case 2:
			// прекратить опускание и с этого места начать поднятие
			this->flapStatus = 4;
			break;
	}

}

void MotorDriveDevice::leftWedgeInsert()
{
	this->trackSwitch->increaseLeftObstacle();
}

void MotorDriveDevice::leftWedgeRemove()
{
	this->trackSwitch->decreaseLeftObstacle();
}

void MotorDriveDevice::rightWedgeInsert()
{
	this->trackSwitch->increaseRightObstacle();
}

void MotorDriveDevice::rightWedgeRemove()
{
	this->trackSwitch->decreaseRightObstacle();
}

float MotorDriveDevice::getLeftWedgePosition() const
{
	return this->trackSwitch->getLeftObstacle();
}

float MotorDriveDevice::getRightWedgePosition() const
{
	return this->trackSwitch->getRightObstacle();
}

void MotorDriveDevice::changeStatus(const OutputStream& param)
{
	switch (param.mask[0] & 3)
	{
		case 0:
			if (this->motorStatus > 0)
			{
				this->ownerScheme->resetStatusBit(this->workingAmperageBit);
				this->ownerScheme->resetStatusBit(this->frictionAmperageBit);
				this->motorStatus = 0;
				this->friction = false;
			}
			break;
		case 1:
			// Питание двигателя для движения шибера вправо
			switch (this->motorStatus)
			{
				case 0:
					this->ownerScheme->setStatusBit(this->workingAmperageBit);
					this->friction = false;
					this->isGateClose = false;
					this->addIdleTimer();
					if (this->timeStamp == 0)
						this->timeStamp = this->getWorkingTime();
				case 3:
				case 4:
					this->ownerScheme->resetStatusBit(this->frictionAmperageBit);
					this->friction = false;
					this->isGateClose = false;
					this->motorStatus = 1;
					break;
			}
			break;
		case 2:
			// Питание двигателя для движения шибера влево
			switch (this->motorStatus)
			{
				case 0:
					this->ownerScheme->setStatusBit(this->workingAmperageBit);
					this->friction = false;
					this->isGateClose = false;
					this->addIdleTimer();
					if (this->timeStamp == 0)
						this->timeStamp = this->getWorkingTime();
				case 1:
				case 2:
					this->ownerScheme->resetStatusBit(this->frictionAmperageBit);
					this->friction = false;
					this->isGateClose = false;
					this->motorStatus = 3;
					break;
			}
			break;
	}
}

void MotorDriveDevice::idleTimer(unsigned long long time)
{
	int deleteMark = 0xFF;

	// Обработка курбельной заслонки
	float delta = static_cast<float> (time - this->timeStamp);
	switch (this->flapStatus)
	{
		case 1:
			if ((this->flapPosition += delta / this->flapTime) > this->lockSwitchLevel)
			{
				this->ownerScheme->resetStatusBit(this->lockSwitchBit);
				this->flapStatus = 2;
			}
			deleteMark &= 0xFE;
			this->timeStamp = time;
			break;
		case 2:
			if ((this->flapPosition += delta / this->flapTime) > 1.0f)
			{
				this->flapPosition = 1.0f;
				this->flapStatus = 3;
			}
			else
			{
				deleteMark &= 0xFE;
				this->timeStamp = time;
			}
			break;
		case 4:
			if ((this->flapPosition -= delta / this->flapTime) < this->lockSwitchLevel)
			{
				this->ownerScheme->setStatusBit(this->lockSwitchBit);
				this->flapStatus = 5;
			}
			deleteMark &= 0xFE;
			this->timeStamp = time;
			break;
		case 5:
			if ((this->flapPosition -= delta / this->flapTime) < 0.0f)
			{
				this->flapPosition = 0.0f;
				this->flapStatus = 0;
			}
			else
			{
				deleteMark &= 0xFE;
				this->timeStamp = time;
			}
			break;
	}

	// Обработка работы якоря двигателя
	float deltaPhase = 0.0f;
	switch (this->motorStatus)
	{
		case 1:
			deltaPhase = delta * this->motorRatePerSecondWork * 360.0f / 1000.0f;
			deleteMark &= 0xFD;
			break;
		case 2:
			deltaPhase = delta * this->motorRatePerSecondFriction * 360.0f / 1000.0f;
			deleteMark &= 0xFD;
			break;
		case 3:
			deltaPhase = -delta * this->motorRatePerSecondWork * 360.0f / 1000.0f;
			deleteMark &= 0xFD;
			break;
		case 4:
			deltaPhase = -delta * this->motorRatePerSecondFriction * 360.0f / 1000.0f;
			deleteMark &= 0xFD;
			break;
	}
	this->motorPhase += deltaPhase;

	deltaPhase /= this->gearRatio;
	if ((deleteMark & 2) == 0)
	{
		// Если вращался якорь двигателя, надо повернуть редуктор, а следом и шибер
		if (deltaPhase < 0.0f)
		{
			// Поворот муфты по часовой
			if (this->autoSwitchGap < this->gapSector)
			{
				// Еще есть зазор
				if ((this->autoSwitchGap += -deltaPhase) > this->gapSector)
				{
					// Уменьшаем зазор
					deltaPhase = this->autoSwitchGap - this->gapSector;
					this->autoSwitchGap = this->gapSector;
				}
				else
					deltaPhase = 0.0f;

				// При необходимости поднимаем правый поворотный кулачок
				this->rightSwivelCamFalling = false;
				if (this->rightSwivelCamPosition < 1.0f)
					this->rightSwivelCamPosition = this->autoSwitchGap / this->gapSector;
			}
			else
				this->rightSwivelCamPosition = 1.0f;

			if (deltaPhase == 0.0f)
				this->reductorPhase = this->gatePosition * (this->workingSector - this->gapSector) - this->workingSector / 2.0f + (this->gapSector - this->autoSwitchGap);
			else
			{
				// Двигаем шибер влево
				this->gatePosition += deltaPhase / (this->workingSector - this->gapSector);
				this->trackSwitch->shiftWorkingRodLeft(this->gatePosition, this->friction);
				this->reductorPhase = this->gatePosition * (this->workingSector - this->gapSector) - this->workingSector / 2.0f;

				if (this->gatePosition <= 0.0f)
				{
					this->gatePosition = 0.0f;
					this->friction = true;
					this->isGateClose = true;
					// шибер достиг крайнего левого положения
					if (this->leftSwivelCamPosition > 0.0f)
					{
						// открылся паз муфты для левого поворотного кулачка
						this->leftSwivelCamFalling = true;
						deleteMark &= 0xFB;
					}
				}

				if (this->friction)
				{
					// При движении шибера встречено препятствие
					if ((this->motorStatus == 1) || (this->motorStatus == 3))
						this->motorStatus++;
					this->ownerScheme->setStatusBit(this->frictionAmperageBit);
				}
				else
				{
					// При движении шибера препятствие не обнаружено
					if ((this->motorStatus == 2) || (this->motorStatus == 4))
						this->motorStatus--;
					this->ownerScheme->resetStatusBit(this->frictionAmperageBit);
				}
			}
		}
		else if (deltaPhase > 0.0f)
		{
			// Поворот муфты против часовой
			if (this->autoSwitchGap > 0.0f)
			{
				// Еще есть зазор
				if ((this->autoSwitchGap -= deltaPhase) < 0.0f)
				{
					// Уменьшаем зазор
					deltaPhase = this->autoSwitchGap;
					this->autoSwitchGap = 0.0f;
				}
				else
					deltaPhase = 0.0f;

				// При необходимости поднимаем левый поворотный кулачок
				this->leftSwivelCamFalling = false;
				if (this->leftSwivelCamPosition < 1.0f)
					this->leftSwivelCamPosition = 1.0f - this->autoSwitchGap / this->gapSector;
			}
			else
				this->leftSwivelCamPosition = 1.0f;

			if (deltaPhase == 0.0f)
				this->reductorPhase = this->gatePosition * (this->workingSector - this->gapSector) - this->workingSector / 2.0f + this->gapSector - this->autoSwitchGap;
			else
			{
				// Двигаем шибер вправо
				this->gatePosition += deltaPhase / (this->workingSector - this->gapSector);
				this->trackSwitch->shiftWorkingRodRight(this->gatePosition, this->friction);
				this->reductorPhase = this->gatePosition * (this->workingSector - this->gapSector) - this->workingSector / 2.0f + this->gapSector;

				if (this->gatePosition >= 1.0f)
				{
					this->gatePosition = 1.0f;
					this->isGateClose = true;
					this->friction = true;
					// шибер достиг крайнего правого положения
					if (this->rightSwivelCamPosition > 0.0f)
					{
						// открылся паз муфты для правого поворотного кулачка
						this->rightSwivelCamFalling = true;
						deleteMark &= 0xF7;
					}
				}

				if (this->friction)
				{
					// При движении шибера встречено препятствие
					if ((this->motorStatus == 1) || (this->motorStatus == 3))
						this->motorStatus++;
					this->ownerScheme->setStatusBit(this->frictionAmperageBit);
				}
				else
				{
					// При движении шибера препятствие не обнаружено
					if ((this->motorStatus == 2) || (this->motorStatus == 4))
						this->motorStatus--;
					this->ownerScheme->resetStatusBit(this->frictionAmperageBit);
				}
			}
		}
	}

	// Разбираем вынужденное падение левого поворотного кулачка в паз муфты
	if (this->leftSwivelCamFalling)
	{
		if ((this->leftSwivelCamPosition -= delta / this->swivelCamFallingTime) < 0.0f)
		{
			this->leftSwivelCamPosition = 0.0f;
			this->leftSwivelCamFalling = false;
			deleteMark |= 4;
		}
		else
			deleteMark &= 0xFB;
	}

	// Разбираем вынужденное падение правого поворотного кулачка в паз муфты
	if (this->rightSwivelCamFalling)
	{
		if ((this->rightSwivelCamPosition -= delta / this->swivelCamFallingTime) < 0.0f)
		{
			this->rightSwivelCamPosition = 0.0f;
			this->rightSwivelCamFalling = false;
			deleteMark |= 8;
		}
		else
			deleteMark &= 0xF7;
	}

	this->recalculateAutoSwitch();

	if (deleteMark == 0xFF)
	{
		// удалить себя из списка пассивных таймеров
		this->deleteIdleTimer();
		this->timeStamp = 0;
	}
	else
		this->timeStamp = time;
}

void MotorDriveDevice::shiftControlRod(float position)
{
	// Сдвиг контрольных линеек контрольными тягами
	if (this->controlLinePresence)
	{
		this->controlLinePosition = position;
		this->recalculateAutoSwitch();
	}
}

bool MotorDriveDevice::shiftGate(float position)
{
	// Сдвиг шибера рабочей тягой
	// Возврат false, если тяга переламывается
	if ((((position < 1.0f) and (this->gatePosition >= 1.0f)) ||
		((position > 0.0f) and (this->gatePosition <= 0.0f))) && this->isGateClose)
		return false;

	float delta = position - this->gatePosition;
	float old = this->autoSwitchGap;
	float old1 = this->reductorPhase;

	this->gatePosition = position;
	if ((this->motorStatus == 0) and (delta != 0.0f))
	{
		// Если двигатель выключен, но перевод не замкнут и есть движение шибера, надо расчитать новые положения механических частей без вызова таймера покоя
		// Поворотные кулачки при этом не могут мешать, поскольку незамкнутый привод имеет оба поднятых кулачка
		if (delta < 0.0f)
		{
			// Шибер сдвинули влево
			if ((this->autoSwitchGap -= delta) > this->gapSector)
			{
				this->autoSwitchGap = this->gapSector;
				delta += this->autoSwitchGap - old;
			}
		}
		else
		{
			// Шибер сдвинули вправо
			if ((this->autoSwitchGap -= delta) < 0.0f)
			{
				this->autoSwitchGap = 0.0f;
				delta -= old - this->autoSwitchGap;
			}
		}
		this->reductorPhase += delta * (this->workingSector - this->gapSector);
		this->motorPhase += delta * (this->workingSector - this->gapSector) * this->gearRatio;
	}
	return true;
}
