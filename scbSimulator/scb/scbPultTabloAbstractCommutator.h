#pragma once

#include "scbPultTablo.h"
#include "scbPultTabloActiveDevice.h"

class scbPultTabloAbstractCommutator : public scbPultTabloActiveDevice
{
protected:
	int m_SwitchLeftOnContactBit;
	int m_SwitchLeftOffContactBit;
	int m_SwitchRightOnContactBit;
	int m_SwitchRightOffContactBit;
	int m_PressOnContactBit;
	int m_PressOffContactBit;
	float m_PressPosition; // ���������� ��������� �������� ��������: 0.0f - ��������, 1.0f - �������
	float m_SwitchPosition; // ���������� ��������� ����������� �����������: 0.0f - �������, -1.0f - ��������� ������ ������� ( ������), 1.0f - ��������� �� ������� ( ������� )
	scbPultTablo::Color m_Color;
	bool m_Pressable; // ������� �������� ��������
	unsigned long long m_TimeStamp;
	/*
	0 - ��������
	1 - ����������
	2 - ������
	3 - �����������
	*/
	int m_PressStatus;
	/*
	0 - ��� �������
	1 - ���������� ��� ��������
	2 - ����� �������
	*/
	int m_PressContactStatus;
	int m_SwitchStatus; // 0 - ��������, ��������� ����������
	int m_SwitchContactStatus; // 0 - ��������, ��������� ����������

	static constexpr float c_PressOnBorder = 0.7f; // �������� ��������� ���������� ��������� ���������
	static constexpr float c_PressOffBorder = 0.2f; // �������� ��������� ���������� ������� ���������
	static constexpr float c_PressTime = 300.0f; // ����� �������/�������, ��

public:
	scbPultTabloAbstractCommutator ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	scbPultTabloAbstractCommutator ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	virtual ~scbPultTabloAbstractCommutator () override;

	virtual void Press () override;
	virtual void Release () override;

	scbPultTablo::Color GetColor () const;
	float GetPressPosition () const;
	float GetSwitchPosition () const;
};

inline scbPultTablo::Color scbPultTabloAbstractCommutator::GetColor () const
{
	return this->m_Color;
}

inline float scbPultTabloAbstractCommutator::GetPressPosition () const
{
	return this->m_PressPosition;
}

inline float scbPultTabloAbstractCommutator::GetSwitchPosition () const
{
	return this->m_SwitchPosition;
}
