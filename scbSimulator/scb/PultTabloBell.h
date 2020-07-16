#pragma once

#include "AbstractSchemeDevice.h"

namespace scb
{
	class PultTabloBell : public AbstractSchemeDevice
	{
		int status; // 0 - исходное положение, 1 - запущенное положение
		int continuouslyElement;
		unsigned long continuouslyMask;
		int impulseElement;
		unsigned long impulseMask;

	public:
		PultTabloBell(AbstractScheme* ownerScheme, int continuouslyBit, int impulseBit);
		virtual ~PultTabloBell() override;

		virtual void initialize() override;
		virtual void changeStatus(const OutputStream& param) override; // Вызывается схемой-хозяином после расчета
		virtual void idleTimer(unsigned long long time) override;
	};
}