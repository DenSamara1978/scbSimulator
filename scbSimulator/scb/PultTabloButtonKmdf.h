#pragma once

#include "PultTabloAbstractButton.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloButtonKmdf : public PultTabloAbstractButton
	{
		/*
		m_Status
		0 - исходное
		1 - нажимается до фиксации
		2 - нажата до фиксации
		3 - отпускается до фиксации
		4 - фиксация
		5 - нажимается после фиксации
		6 - нажата после фиксации
		7 - отпускается после фиксации
		*/

		/*
		m_ContactStatus
		0 - тыл замкнут
		1 - размокнуты все контакты
		2 - фронт замкнут
		*/

	public:
		PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit);
		PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloButtonKmdf() override;

		virtual void initialize() override;

		virtual void press() override;
		virtual void release() override;

		virtual void idleTimer(unsigned long long time) override;
	};
}