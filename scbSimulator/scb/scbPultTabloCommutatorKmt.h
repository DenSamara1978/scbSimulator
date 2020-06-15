#pragma once

#include "scbPultTabloAbstractCommutator.h"

class scbPultTabloCommutatorKmt : public scbPultTabloAbstractCommutator
{
	/*
	m_SwitchStatus
	0 - �������� ( �� ������ )
	1 - �������������� ������ ������� �� ������
	2 - ��������� ( ������ )
	3 - �������������� �� ������� � ������
	4 - �������������� �� ������� �� ������
	5 - ��������� ( ������� )
	6 - �������������� ������ ������� � ������
	*/

	/*
	m_SwitchContactStatus
	0 - ��� ������ ��������� �������, ��� ������� ��������� �������
	1 -								��� ������� ��������� �������
	2 - ����� ������ ��������� �������, ��� ������� ��������� �������
	3 - ��� ������ ��������� �������
	4 - ��� ������ ��������� �������, ����� ������� ��������� ������
	*/

	static constexpr float c_SwitchOnBorder = 0.7f; // �������� ��������� ���������� ��������� ��������� ��� ������������
	static constexpr float c_SwitchOffBorder = 0.2f; // �������� ��������� ���������� ������� ��������� ��� ������������
	static constexpr float c_SwitchTime = 300.0f; // ����� �������� ����� �����������, ��

public:
	scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	virtual ~scbPultTabloCommutatorKmt ();

	virtual void Init () override;

	virtual void TurnCW () override;
	virtual void TurnCCW () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
