#pragma once

#include "scbPultTabloAbstractCommutator.h"

class scbPultTabloCommutatorKmd : public scbPultTabloAbstractCommutator
{
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

	static constexpr float c_SwitchOnBorder = 0.7f; // значение положения коммутации фронтовых контактов при переключении
	static constexpr float c_SwitchOffBorder = 0.2f; // Значение положения коммутации тыловых контактов при переключении
	static constexpr float c_SwitchTime = 400.0f; // Время перевода между положениями, мс

public:
	scbPultTabloCommutatorKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	scbPultTabloCommutatorKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	virtual ~scbPultTabloCommutatorKmd ();

	virtual void Init () override;

	virtual void TurnCW () override;
	virtual void TurnCCW () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
