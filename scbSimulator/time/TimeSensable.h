#pragma once

#include "TimeServer.h"

namespace time
{
	class TimeSensable
	{
	public:
		TimeSensable();
		virtual ~TimeSensable();

		virtual void timeToWork(int signal, unsigned long long time);
		virtual void idleTimer(unsigned long long time) abstract;

	protected:
		void addIdleTimer();
		void deleteIdleTimer();

		void addTimeToWork(unsigned long long delay, int signal);
		void deleteTimeToWork();
		void deleteTimeToWork(int signal);
		void changeTimeToWork(unsigned long long delay);
		void changeTimeToWork(int signal, unsigned long long delay);

		unsigned long long getWorkingTime() const;

		void cleanupTimers();

	private:
		bool hasIdleTimer;
	};


	inline void TimeSensable::addIdleTimer()
	{
		if (!this->hasIdleTimer)
		{
			this->hasIdleTimer = true;
			TimeServer::getInstance()->addIdleTimer(this);
		}
	}

	inline void TimeSensable::deleteIdleTimer()
	{
		if (this->hasIdleTimer)
		{
			this->hasIdleTimer = false;
			TimeServer::getInstance()->deleteIdleTimer(this);
		}
	}

	inline void TimeSensable::cleanupTimers()
	{
		auto timeServer = TimeServer::getInstance();
		timeServer->deleteIdleTimer(this);
		timeServer->deleteTimeToWork(this);
		this->hasIdleTimer = false;
	}

	inline void TimeSensable::addTimeToWork(unsigned long long delay, int signal)
	{
		TimeServer::getInstance()->addTimeToWork(this, delay, signal);
	}

	inline void TimeSensable::deleteTimeToWork()
	{
		TimeServer::getInstance()->deleteTimeToWork(this);
	}

	inline void TimeSensable::deleteTimeToWork(int signal)
	{
		TimeServer::getInstance()->deleteTimeToWork(this, signal);
	}

	inline void TimeSensable::changeTimeToWork(unsigned long long delay)
	{
		TimeServer::getInstance()->changeTimeToWork(this, delay);
	}

	inline void TimeSensable::changeTimeToWork(int signal, unsigned long long delay)
	{
		TimeServer::getInstance()->changeTimeToWork(this, signal, delay);
	}

	inline unsigned long long TimeSensable::getWorkingTime() const
	{
		return TimeServer::getInstance()->getWorkingTime();
	}
}
