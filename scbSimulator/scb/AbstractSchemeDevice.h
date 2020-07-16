#pragma once

#include <vector>
#include "AbstractScheme.h"
#include "..\time\Timer.h"

using std::vector;

namespace scb
{

	class AbstractSchemeDevice
	{
	public:
		AbstractSchemeDevice(AbstractScheme* owner);
		virtual ~AbstractSchemeDevice();

		void mapInputOutput(int inputBit, int outputBit);

		virtual void timeToWork (int signal, unsigned long long time); // Обработка таймера

		virtual void initialize() abstract;
		virtual void changeStatus(const OutputStream& param) abstract; // Вызывается схемой-хозяином после собственного расчета

		virtual void idleTimer(unsigned long long time) abstract;

	protected:
		struct Convertation
		{
			int outputElement;
			unsigned long outputMask;
			int inputElement;
			unsigned long inputMask;
		};

		vector<Convertation> convertations;

		AbstractScheme* ownerScheme;

		void addIdleTimer();
		void deleteIdleTimer();

	private:
		bool hasIdleTimer;
	};


	inline void AbstractSchemeDevice::addIdleTimer()
	{
		if (!this->hasIdleTimer)
		{
			this->hasIdleTimer = true;
			time::Timer::getInstance()->addIdleTimer(this);
		}
	}

	inline void AbstractSchemeDevice::deleteIdleTimer()
	{
		if (this->hasIdleTimer)
		{
			this->hasIdleTimer = false;
			time::Timer::getInstance()->deleteIdleTimer(this);
		}
	}
}