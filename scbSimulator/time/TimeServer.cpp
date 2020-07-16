#include <windows.h>
#include <algorithm>

#include "TimeServer.h"
#include "TimeSensable.h"
#include "..\scb\AbstractScheme.h"

using namespace time;

using scb::AbstractScheme;

TimeServer* TimeServer::instance = nullptr;

TimeServer::TimeServer()
{
	TimeServer::instance = this;
	this->time = GetTickCount64();
}

TimeServer::~TimeServer()
{
	TimeServer::instance = nullptr;
}

void TimeServer::tick()
{
	this->time = GetTickCount64();

	// Выбрать из очереди готовые таймеры
	while(!this->timerDeque.empty())
	{
		auto rec = this->timerDeque.front();
		if ( this->time < rec.timeToWork)
			break;
		unsigned long long time = rec.timeToWork;
		rec.object->timeToWork(rec.signal, time);
		this->timerDeque.pop_front();
	}

	// Раздать свободный таймер всем нуждающимся устройствам
	auto now = this->idleList.cbegin();
	while(now != this->idleList.cend())
		(*(now++))->idleTimer(this->time);
}

void TimeServer::addTimeToWork(TimeSensable* object, unsigned long long delay, int signal)
{
	if (object != nullptr)
	{
		unsigned long long time = this->time + delay;
		auto rec = find_if(this->timerDeque.cbegin(), this->timerDeque.cend(), 
			[time](const TimerRecord& rec)->bool { return time >= rec.timeToWork; });
		this->timerDeque.emplace(rec, object, time, signal);
	}
}

void TimeServer::deleteTimeToWork(TimeSensable* object)
{
	if (object != nullptr)
	{
		auto rem = remove_if(this->timerDeque.begin(), this->timerDeque.end(), 
			[object](const TimerRecord& rec)->bool { return object == rec.object; });
		this->timerDeque.erase(rem, this->timerDeque.cend());
	}
}

void TimeServer::deleteTimeToWork(TimeSensable* object, int signal)
{
	if (object != nullptr)
	{
		auto rem = remove_if(this->timerDeque.begin(), this->timerDeque.end(), 
			[object, signal](const TimerRecord& rec)->bool { return (object == rec.object) && (signal == rec.signal); });
		this->timerDeque.erase(rem, this->timerDeque.cend());
	}
}

void TimeServer::changeTimeToWork(TimeSensable* object, unsigned long long delay)
{
	if (object != nullptr)
	{
		auto rem = find_if(this->timerDeque.cbegin(), this->timerDeque.cend(), 
			[object](const TimerRecord& rec)->bool { return object == rec.object; });
		int signal = (*rem).signal;
		this->timerDeque.erase(rem);
		this->addTimeToWork(object, delay, signal);
	}
}

void TimeServer::changeTimeToWork(TimeSensable* object, int signal, unsigned long long delay)
{
	if (object != nullptr)
	{
		this->deleteTimeToWork(object, signal);
		this->addTimeToWork(object, delay, signal);
	}
}
