#include <windows.h>
#include <algorithm>

#include "Timer.h"
#include "..\scb\AbstractScheme.h"
#include "..\scb\AbstractSchemeDevice.h"

using namespace time;

using scb::AbstractScheme;
using scb::AbstractSchemeDevice;

Timer* Timer::instance = nullptr;

Timer::Timer()
{
	Timer::instance = this;
}

Timer::~Timer ()
{
	Timer::instance = nullptr;
}

void Timer::tick()
{
	this->time = GetTickCount64();

	// Выбрать из очереди готовые таймеры
	while(!this->timerDeque.empty())
	{
		auto rec = this->timerDeque.front();
		if ( this->time < rec.timeToWork)
			break;
		unsigned long long time = rec.timeToWork;
		rec.device->timeToWork(rec.signal, time);
		this->timerDeque.pop_front();
	}

	// Рассчитать схемы из очереди
	while (!this->recalculateDeque.empty ())
	{
		this->recalculateDeque.front ()->recalculate();
		this->recalculateDeque.pop_front();
	}

	// Раздать свободный таймер всем нуждающимся устройствам
	auto now = this->idleList.cbegin();
	while(now != this->idleList.cend())
		(*(now++))->idleTimer(this->time);
}

void Timer::addTimeToWork(AbstractSchemeDevice* device, unsigned long long delay, int signal)
{
	if (device != nullptr)
	{
		unsigned long long time = this->time + delay;
		auto rec = find_if(this->timerDeque.cbegin(), this->timerDeque.cend(), 
			[time](const TimerRecord& rec)->bool { return time >= rec.timeToWork; });
		this->timerDeque.emplace(rec, device, time, signal);
	}
}

void Timer::deleteTimeToWork(AbstractSchemeDevice* device)
{
	if (device != nullptr)
	{
		auto rem = remove_if(this->timerDeque.begin(), this->timerDeque.end(), 
			[device](const TimerRecord& rec)->bool { return device == rec.device; });
		this->timerDeque.erase(rem, this->timerDeque.cend());
	}
}

void Timer::deleteTimeToWork(AbstractSchemeDevice* device, int signal)
{
	if (device != nullptr)
	{
		auto rem = remove_if(this->timerDeque.begin(), this->timerDeque.end(), 
			[device, signal](const TimerRecord& rec)->bool { return (device == rec.device) && (signal == rec.signal); });
		this->timerDeque.erase(rem, this->timerDeque.cend());
	}
}

void Timer::changeTimeToWork(AbstractSchemeDevice* device, unsigned long long delay)
{
	if (device != nullptr)
	{
		auto rem = find_if(this->timerDeque.cbegin(), this->timerDeque.cend(), 
			[device](const TimerRecord& rec)->bool { return device == rec.device; });
		int signal = (*rem).signal;
		this->timerDeque.erase(rem);
		this->addTimeToWork(device, delay, signal);
	}
}

void Timer::changeTimeToWork(AbstractSchemeDevice* device, int signal, unsigned long long delay)
{
	if (device != nullptr)
	{
		this->deleteTimeToWork(device, signal);
		this->addTimeToWork(device, delay, signal);
	}
}
