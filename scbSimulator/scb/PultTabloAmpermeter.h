#pragma once

#include "AbstractScheme.h"
#include "AbstractSchemeDevice.h"

namespace scb
{

	class PultTabloAmpermeter : public AbstractSchemeDevice
	{
	public:
		PultTabloAmpermeter(AbstractScheme* ownerScheme, int startBit);
		virtual ~PultTabloAmpermeter() override;

		virtual void initialize() override;
		virtual void changeStatus(const OutputStream& param) override;
		virtual void idleTimer(unsigned long long time) override;
	};
}