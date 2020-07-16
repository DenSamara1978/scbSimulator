#include "AbstractScheme.h"
#include "LightSignalLamp.h"

using namespace scb;

using time::Timer;

LightSignalLamp::LightSignalLamp(AbstractScheme* ownerScheme) :
	AbstractSchemeDevice(ownerScheme),
	status(0),
	bright(0.0f),
	timeStamp(0),
	velocity(0.0f)
{
}

LightSignalLamp::~LightSignalLamp()
{
}

void LightSignalLamp::initialize()
{
	// пустой вызов
}

void LightSignalLamp::changeStatus(const OutputStream& param)
{
	static char targetStatus[] = {0, 1, 2, 2, 3, 3, 3, 3, 0, 4, 5, 5, 6, 6, 6, 6};

	int oldStatus = this->status;
	this->status = targetStatus[param.mask[0] & 0xF];
	if (oldStatus != this->status)
	{
		this->timeStamp = Timer::getInstance()->getWorkingTime();
		if (LightSignalLamp::targetBright[this->status] > this->bright)
			this->velocity = lampOnVelocity;
		else
			this->velocity = lampOffVelocity;
		this->addIdleTimer();
	}
}

void LightSignalLamp::idleTimer(unsigned long long time)
{
	float bright = this->bright + this->velocity * (time - this->timeStamp) / 1000.0f;
	this->timeStamp = time;
	if (((bright <= LightSignalLamp::targetBright[this->status]) and (this->bright >= LightSignalLamp::targetBright[this->status])) or
		((bright >= LightSignalLamp::targetBright[this->status]) and (this->bright <= LightSignalLamp::targetBright[this->status])))
	{
		this->bright = LightSignalLamp::targetBright[this->status];
		this->velocity = 0.0f;
		this->deleteIdleTimer();
	}
	else
		this->bright = bright;
}
