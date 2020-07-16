#pragma once

namespace scb
{
	class AbstractSchemeDevice;
}

using scb::AbstractSchemeDevice;

namespace time
{

	class TimerRecord
	{
	public:
		TimerRecord(AbstractSchemeDevice* device, unsigned long long time, int signal);

	private:
		friend class Timer;

		AbstractSchemeDevice* device;
		TimerRecord* previous;
		TimerRecord* next;
		unsigned long long timeToWork;
		int signal;

	};

	inline TimerRecord::TimerRecord(AbstractSchemeDevice* device, unsigned long long time, int signal) :
		timeToWork(time),
		device(device),
		signal(signal),
		next(nullptr),
		previous(nullptr)
	{
	}

}