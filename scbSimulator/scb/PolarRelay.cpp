#include "PolarRelay.h"
#include "AbstractScheme.h"
#include "..\time\Timer.h"

using namespace scb;

using time::Timer;

PolarRelay::PolarRelay(AbstractScheme* ownerScheme, int directionalbit, int reverseBit) :
	directionalContactBit(directionalbit),
	reverseContactBit(reverseBit),
	Relay(ownerScheme)
{
}

PolarRelay::~PolarRelay()
{
}

void PolarRelay::initialize()
{
	this->ownerScheme->setStatusBit(this->directionalContactBit);
}

void PolarRelay::setMode(unsigned long mode)
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

	// dir == 1 если движение начинается или онон продолжается в том же направлении
	// dir == -1 если движение меняет направление

	switch (this->status)
	{
		case 0:
			// Начать процесс трогания в переведенное
			this->timeStamp = time;
			this->status = 1;
			Timer::getInstance()->addTimeToWork(this, starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 1:
			if (dir == 1)
			{
				// Продолжаем трогаться в переведенное по другому времени
				newDelay = static_cast<unsigned long long> (starting * (1.0f - (static_cast <float> (time - this->timeStamp)) / this->starting));
				this->timeStamp = time - starting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переходим в прямое положение
				this->timeStamp = 0;
				this->status = 0;
				Timer::getInstance()->deleteTimeToWork(this);
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 2:
			if (dir == 1)
			{
				// Продолжаем перелет в переведенное другому времени
				newDelay = static_cast<unsigned long long> (shifting * (1.0f - (static_cast <float> (time - this->timeStamp)) / this->shifting));
				this->timeStamp = time - shifting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переключаемся в состояние перелета в прямое
				newDelay = static_cast<unsigned long long> (shifting * (static_cast <float> (time - this->timeStamp) / this->shifting));
				this->timeStamp = time - shifting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
				this->status = 5;
			}
			break;
		case 3:
			// Начать процесс трогания в прямое
			this->timeStamp = time;
			this->status = 4;
			Timer::getInstance()->addTimeToWork(this, starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 4:
			if (dir == 1)
			{
				// Продолжаем трогаться в прямое по другому времени
				newDelay = static_cast<unsigned long long> (starting * (1.0f - (static_cast <float> (time - this->timeStamp)) / this->starting));
				this->timeStamp = time - starting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переходим в переведенное положение
				this->timeStamp = 0;
				this->status = 3;
				Timer::getInstance()->deleteTimeToWork(this);
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 5:
			if (dir == 1)
			{
				// Продолжаем перелет в прямое по другому времени
				newDelay = static_cast<unsigned long long> (shifting * (1.0f - (static_cast <float> (time - this->timeStamp)) / this->shifting));
				this->timeStamp = time - shifting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// Переключаемся в состояние перелета в переведенное
				newDelay = static_cast<unsigned long long> (shifting * (static_cast <float> (time - this->timeStamp) / this->shifting));
				this->timeStamp = time - shifting + newDelay;
				Timer::getInstance()->changeTimeToWork(this, newDelay);
				this->starting = starting;
				this->shifting = shifting;
				this->status = 2;
			}
			break;
	}
	this->targetMode = mode;
}

void PolarRelay::timeToWork(int signal, unsigned long long time)
{
	unsigned long long timeDelay;
	switch (this->status)
	{
		case 1:
			if (this->directionalContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->directionalContactBit);
			this->timeStamp = time;
			this->status = 2;
			timeDelay = this->timeSamples[this->targetMode].shifting;
			Timer::getInstance()->addTimeToWork(this, timeDelay, 0);
			break;
		case 2:
			if (this->reverseContactBit >= 0)
				this->ownerScheme->setStatusBit(this->reverseContactBit);
			this->timeStamp = 0;
			this->status = 3;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
		case 4:
			if (this->reverseContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->reverseContactBit);
			this->timeStamp = time;
			this->status = 5;
			timeDelay = this->timeSamples[this->targetMode].shifting;
			Timer::getInstance()->addTimeToWork(this, timeDelay, 0);
			break;
		case 5:
			if (this->directionalContactBit >= 0)
				this->ownerScheme->setStatusBit(this->directionalContactBit);
			this->timeStamp = 0;
			this->status = 0;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
	}
}
