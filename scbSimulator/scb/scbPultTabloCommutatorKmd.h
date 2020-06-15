#pragma once

#include "scbPultTabloAbstractCommutator.h"

class scbPultTabloCommutatorKmd : public scbPultTabloAbstractCommutator
{
	/*
	m_SwitchStatus
	0 - �������� ( ����� )
	1 - �������������� �� �������
	2 - ��������� ( ������ )
	3 - �������������� ������ �������
	*/

	/*
	m_SwitchContactStatus
	0 - ����� ������ ��������� �������, ��� ������� ��������� �������
	1 -								��� ������� ��������� �������
	2 - ��� ������ ��������� �������, ��� ������� ��������� �������
	3 - ��� ������ ��������� �������
	4 - ��� ������ ��������� �������, ����� ������� ��������� ������
	*/

	static constexpr float c_SwitchOnBorder = 0.7f; // �������� ��������� ���������� ��������� ��������� ��� ������������
	static constexpr float c_SwitchOffBorder = 0.2f; // �������� ��������� ���������� ������� ��������� ��� ������������
	static constexpr float c_SwitchTime = 400.0f; // ����� �������� ����� �����������, ��

public:
	scbPultTabloCommutatorKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	scbPultTabloCommutatorKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	virtual ~scbPultTabloCommutatorKmd ();

	virtual void Init () override;

	virtual void TurnCW () override;
	virtual void TurnCCW () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
