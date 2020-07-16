#include "NeutralRelay.h"
#include "AbstractScheme.h"
#include "..\time\Timer.h"

using namespace scb;

using time::Timer;

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit) :
	offContactBit(0),
	onContactBit(onBit),
	offBridgeContactBit(0),
	onBridgeContactBit(0),
	hasOffContact(false),
	hasBridgeContact(false),
	Relay(ownerScheme)
{
}

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit) :
	offContactBit(offBit),
	onContactBit(onBit),
	offBridgeContactBit(0),
	onBridgeContactBit(0),
	hasOffContact(true),
	hasBridgeContact(false),
	Relay(ownerScheme)
{
}

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit, int onBridgeBit, int offBridgeBit) :
	offContactBit(offBit),
	onContactBit(onBit),
	offBridgeContactBit(offBridgeBit),
	onBridgeContactBit(onBridgeBit),
	hasOffContact(true),
	hasBridgeContact(true),
	Relay(ownerScheme)
{
}

NeutralRelay::~NeutralRelay()
{
}

void NeutralRelay::initialize()
{
	if (this->hasOffContact)
		this->ownerScheme->setStatusBit(this->offContactBit);
	if (this->hasBridgeContact)
		this->ownerScheme->setStatusBit(this->offBridgeContactBit);
}

void NeutralRelay::setMode(unsigned long mode)
{
	if (this->targetMode == mode)
	{
		// Целевой режим соответствует вычисленному, ничего не менять
		return;
	}
	unsigned long long newDelay, time;
	time = Timer::getInstance()->getWorkingTime();

	int starting = -1;
	int shifting = -1;
	int dir = 0;

	for (const auto& sample : this->timeSamples)
	{
		if ((sample.modeFrom == this->currentMode) && (sample.modeTo == mode))
		{
			starting = sample.starting;
			shifting = sample.shifting;
			dir = 1;
			break;
		}
	}
	if (dir == 0)
	{
		for (const auto& sample : this->timeSamples)
		{
			if ((sample.modeFrom == this->targetMode) && (sample.modeTo == mode))
			{
				starting = sample.starting;
				shifting = sample.shifting;
				dir = -1;
				break;
			}
		}
	}
	if (starting == -1)
	{
		// Указанная смена режима не изменит положения реле
		this->currentMode = mode;
		return;
	}

	// dir == 1 если движение начинается или оно продолжается в том же направлении
	// dir == -1 если движение меняет направление

	float differenceTime = static_cast<float> (time - this->timeStamp);
	float interval;

	switch (this->status)
	{
		case 0:
			// Начать процесс трогания на подъем
			this->timeStamp = time;
			this->status = 1;
			Timer::getInstance()->addTimeToWork(this, starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 1:
			if (dir == 1)
			{
				// Продолжаем трогаться на подъем по другому времени
				newDelay = static_cast<unsigned long long> (starting * (1.0f - differenceTime / this->starting));
				this->timeStamp = time - starting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переходим в положение без тока
				this->timeStamp = 0;
				this->status = 0;
				Timer::getInstance()->deleteTimeToWork(this);
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 2:
			interval = shifting * differenceTime / this->shifting;
			newDelay = static_cast<unsigned long long> ((dir == 1) ? shifting - interval : interval);
			if (dir != 1)
				this->status = 5;
			this->timeStamp = time - shifting + newDelay;
			Timer::getInstance()->changeTimeToWork(this, newDelay);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 3:
			// Начать процесс трогания на отпускание
			this->timeStamp = time;
			this->status = 4;
			Timer::getInstance()->addTimeToWork(this, starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 4:
			if (dir == 1)
			{
				// Продолжаем трогаться на отпадание по другому времени
				newDelay = static_cast<unsigned long long> (starting * (1.0f - differenceTime / this->starting));
				this->timeStamp = time - starting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переходим в положение под током
				this->timeStamp = 0;
				this->status = 3;
				Timer::getInstance()->deleteTimeToWork(this);
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 5:
			interval = shifting * differenceTime / this->shifting;
			newDelay = static_cast<unsigned long long> ((dir == 1) ? shifting - interval : interval);
			if (dir != 1)
				this->status = 2;
			this->timeStamp = time - shifting + newDelay;
			Timer::getInstance()->changeTimeToWork(this, newDelay);
			this->starting = starting;
			this->shifting = shifting;
			break;
	}
	this->targetMode = mode;
}

void NeutralRelay::timeToWork(int signal, unsigned long long time)
{
	switch (this->status)
	{
		case 1:
			if (this->hasOffContact && (this->offContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->offContactBit);
			if (this->hasBridgeContact && (this->onBridgeContactBit >= 0))
				this->ownerScheme->setStatusBit(this->onBridgeContactBit);
			this->timeStamp = time;
			this->status = 2;
			Timer::getInstance()->addTimeToWork(this, this->shifting, 0);
			break;
		case 2:
			if (this->onContactBit >= 0)
				this->ownerScheme->setStatusBit(this->onContactBit);
			if (this->hasBridgeContact && (this->offBridgeContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->offBridgeContactBit);
			this->timeStamp = 0;
			this->status = 3;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
		case 4:
			if (this->onContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->onContactBit);
			if (this->hasBridgeContact && (this->offBridgeContactBit >= 0))
				this->ownerScheme->setStatusBit(this->offBridgeContactBit);
			this->timeStamp = time;
			this->status = 5;
			Timer::getInstance()->addTimeToWork(this, this->shifting, 0);
			break;
		case 5:
			if (this->hasOffContact && (this->offContactBit >= 0))
				this->ownerScheme->setStatusBit(this->offContactBit);
			if (this->hasBridgeContact && (this->onBridgeContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->onBridgeContactBit);
			this->timeStamp = 0;
			this->status = 0;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
	}
}
