#pragma once

#include "Relay.h"

namespace scb
{
	class PolarRelay : public Relay
	{
	public:
		PolarRelay(AbstractScheme* ownerScheme, int directionalBit, int reverseBit);
		virtual ~PolarRelay() override;

		virtual void initialize() override;
		virtual void timeToWork(int signal, unsigned long long time) override; // Обработка таймера

	protected:
		virtual void setMode(unsigned long mode) override; // Вызывается из метода ChangeStatus

	private:
		int directionalContactBit;
		int reverseContactBit;
	};
}
