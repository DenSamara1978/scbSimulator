#pragma once

namespace time
{
	class TimeSensable;

	class TimerRecord
	{
	public:
		TimerRecord(TimeSensable* object, unsigned long long time, int signal);

	private:
		friend class TimeServer;

		TimeSensable* object;
		TimerRecord* previous;
		TimerRecord* next;
		unsigned long long timeToWork;
		int signal;

	};

	inline TimerRecord::TimerRecord(TimeSensable* object, unsigned long long time, int signal) :
		timeToWork(time),
		object(object),
		signal(signal),
		next(nullptr),
		previous(nullptr)
	{
	}

}