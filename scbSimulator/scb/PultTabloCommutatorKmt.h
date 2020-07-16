#pragma once

#include "PultTabloAbstractCommutator.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloCommutatorKmt : public PultTabloAbstractCommutator
	{
	public:
		PultTabloCommutatorKmt(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		PultTabloCommutatorKmt(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);
		virtual ~PultTabloCommutatorKmt();

		virtual void initialize() override;

		virtual void turnCw() override;
		virtual void turnCcw() override;

		virtual void idleTimer(unsigned long long time) override;

	private:
		/*
		m_SwitchStatus
		0 - исходное ( по центру )
		1 - поворачивается против часовой от центра
		2 - повернута ( налево )
		3 - поворачивается по часовой к центру
		4 - поворачивается по часовой от центра
		5 - повернута ( направо )
		6 - поворачивается против часовой к центру
		*/

		/*
		m_SwitchContactStatus
		0 - тыл левого положения замкнут, тыл правого положения замкнут
		1 -								тыл правого положения замкнут
		2 - фронт левого положения замкнут, тыл правого положения замкнут
		3 - тыл левого положения замкнут
		4 - тыл левого положения замкнут, фронт правого положения замнут
		*/

		static constexpr float switchOnBorder = 0.7f; // значение положения коммутации фронтовых контактов при переключении
		static constexpr float switchOffBorder = 0.2f; // Значение положения коммутации тыловых контактов при переключении
		static constexpr float switchTime = 300.0f; // Время перевода между положениями, мс

	};
}