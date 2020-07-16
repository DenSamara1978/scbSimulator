#pragma once

#include "PultTabloAbstractCommutator.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloCommutatorKmd : public PultTabloAbstractCommutator
	{
	public:
		PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);
		virtual ~PultTabloCommutatorKmd();

		virtual void initialize() override;

		virtual void turnCw() override;
		virtual void turnCcw() override;

		virtual void idleTimer(unsigned long long time) override;

	private:
		/*
		m_SwitchStatus
		0 - исходное ( слева )
		1 - поворачивается по часовой
		2 - повернута ( справа )
		3 - поворачивается против часовой
		*/

		/*
		m_SwitchContactStatus
		0 - фронт левого положения замкнут, тыл правого положения замкнут
		1 -								тыл правого положения замкнут
		2 - тыл левого положения замкнут, тыл правого положения замкнут
		3 - тыл левого положения замкнут
		4 - тыл левого положения замкнут, фронт правого положения замнут
		*/

		static constexpr float switchOnBorder = 0.7f; // значение положения коммутации фронтовых контактов при переключении
		static constexpr float switchOffBorder = 0.2f; // Значение положения коммутации тыловых контактов при переключении
		static constexpr float switchTime = 400.0f; // Время перевода между положениями, мс

	};
}