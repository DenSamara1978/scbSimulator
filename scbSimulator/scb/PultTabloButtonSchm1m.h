#pragma once

#include "PultTabloButtonKmd.h"
#include "..\util\Color.h"

using util::Color;


// TODO Добавить функционал счетчика
namespace scb
{
	class PultTabloButtonSchm1m : public PultTabloButtonKmd
	{
	public:
		PultTabloButtonSchm1m(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloButtonSchm1m() override;

		virtual void press() override;
		virtual void release() override;

		virtual void idleTimer(unsigned long long time) override;
	};
}