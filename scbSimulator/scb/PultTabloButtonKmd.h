#pragma once

#include "PultTabloAbstractButton.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{

	class PultTabloButtonKmd : public PultTabloAbstractButton
	{
		/*
		m_Status
		0 - исходное
		1 - нажимается
		2 - нажата
		3 - отпускается
		*/

		/*
		m_ContactStatus
		0 - тыл замкнут
		1 - размокнуты все контакты
		2 - фронт замкнут
		*/

	public:
		PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit);
		PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloButtonKmd() override;

		virtual void initialize() override;

		virtual void press() override;
		virtual void release() override;

		virtual void idleTimer(unsigned long long time) override;
	};
}