#pragma once

#include <deque>
#include <list>
#include <algorithm>
#include "TimerRecord.h"

using std::deque;
using std::list;

namespace time
{
	class TimeSensable;

	class TimeServer
	{
	public:
		~TimeServer();

		void addIdleTimer(TimeSensable* object);
		void deleteIdleTimer(TimeSensable* object);

		void addTimeToWork(TimeSensable* object, unsigned long long delay, int signal);
		void deleteTimeToWork(TimeSensable* object);
		void deleteTimeToWork(TimeSensable* object, int signal);
		void changeTimeToWork(TimeSensable* object, unsigned long long delay);
		void changeTimeToWork(TimeSensable* object, int signal, unsigned long long delay);

		void tick();
		unsigned long long getWorkingTime() const;

		static TimeServer* getInstance ();

	private:
		TimeServer();

		static TimeServer* instance;

		unsigned long long time;

		list<TimeSensable*> idleList;
		deque<TimerRecord> timerDeque;

	};

	inline TimeServer* TimeServer::getInstance()
	{
		if (TimeServer::instance == nullptr)
			TimeServer::instance = new TimeServer;
		return TimeServer::instance;
	}

	inline unsigned long long TimeServer::getWorkingTime() const
	{
		return this->time;
	}

	inline void TimeServer::addIdleTimer(TimeSensable* object)
	{
		this->idleList.push_back(object);
	}

	inline void TimeServer::deleteIdleTimer(TimeSensable* object)
	{
		this->idleList.remove(object);
	}
}