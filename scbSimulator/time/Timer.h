#pragma once

#include <deque>
#include <list>
#include <algorithm>
#include "TimerRecord.h"

using std::deque;
using std::list;

namespace scb
{
	class AbstractScheme;
	class AbstractSchemeDevice;
}

using scb::AbstractScheme;
using scb::AbstractSchemeDevice;

namespace time
{

	class Timer
	{
	public:
		Timer ();
		~Timer ();

		void addSchemeToRecalculate(AbstractScheme* scheme);
		void deleteSchemeToRecalculate(AbstractScheme* scheme);

		void addIdleTimer(AbstractSchemeDevice* device);
		void deleteIdleTimer(AbstractSchemeDevice* device);

		void addTimeToWork(AbstractSchemeDevice* device, unsigned long long delay, int signal);
		void deleteTimeToWork(AbstractSchemeDevice* device);
		void deleteTimeToWork(AbstractSchemeDevice* device, int signal);
		void changeTimeToWork(AbstractSchemeDevice* device, unsigned long long delay);
		void changeTimeToWork(AbstractSchemeDevice* device, int signal, unsigned long long delay);

		void tick();
		unsigned long long getWorkingTime() const;

		static Timer* getInstance ();

	private:
		static Timer* instance;

		unsigned long long time;

		deque<AbstractScheme*> recalculateDeque;
		list<AbstractSchemeDevice*> idleList;
		deque<TimerRecord> timerDeque;

	};

	inline Timer* Timer::getInstance()
	{
		return Timer::instance;
	}

	inline unsigned long long Timer::getWorkingTime() const
	{
		return this->time;
	}

	inline void Timer::addSchemeToRecalculate(AbstractScheme* scheme)
	{
		this->recalculateDeque.push_back (scheme);
	}

	inline void Timer::deleteSchemeToRecalculate(AbstractScheme* scheme)
	{
		auto rem = remove(this->recalculateDeque.begin(), this->recalculateDeque.end(), scheme);
		this->recalculateDeque.erase(rem, this->recalculateDeque.cend());
	}

	inline void Timer::addIdleTimer(AbstractSchemeDevice* device)
	{
		this->idleList.push_back(device);
	}

	inline void Timer::deleteIdleTimer(AbstractSchemeDevice* device)
	{
		this->idleList.remove(device);
	}
}