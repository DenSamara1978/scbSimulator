#pragma once

#include "scbPultTabloAbstractCommutator.h"

class scbPultTabloCommutatorKmt : public scbPultTabloAbstractCommutator
{
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

	static constexpr float c_SwitchOnBorder = 0.7f; // значение положения коммутации фронтовых контактов при переключении
	static constexpr float c_SwitchOffBorder = 0.2f; // Значение положения коммутации тыловых контактов при переключении
	static constexpr float c_SwitchTime = 300.0f; // Время перевода между положениями, мс

public:
	scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	virtual ~scbPultTabloCommutatorKmt ();

	virtual void Init () override;

	virtual void TurnCW () override;
	virtual void TurnCCW () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
