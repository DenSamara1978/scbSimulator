#pragma once

#include "scbPultTabloActiveDevice.h"
#include "scbPultTablo.h"

class scbPultTabloAbstractButton : public scbPultTabloActiveDevice
{
protected:
	int m_OnContactBit;
	int m_OffContactBit;
	float m_Position; // ���������� ��������� ������: 0.0f - ��������, 1.0f - �������
	scbPultTablo::Color m_Color;
	unsigned long long m_TimeStamp;
	int m_Status; // 0 - �������� ���������, ��������� ����������
	int m_ContactStatus; // 0 - �������� ���������, ��������� ����������

	static constexpr float c_OnBorder = 0.7f; // �������� ��������� ���������� ��������� ���������
	static constexpr float c_OffBorder = 0.2f; // �������� ��������� ���������� ������� ���������
	static constexpr float c_FixBorder = 0.8f; // �������� ��������� ��������
	static constexpr float c_PressTime = 300.0f; // ����� �������/�������, ��

public:
	scbPultTabloAbstractButton ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit );
	scbPultTabloAbstractButton ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit );
	virtual ~scbPultTabloAbstractButton () override;

	scbPultTablo::Color GetColor () const;
	float GetPressPosition () const;
};

inline scbPultTablo::Color scbPultTabloAbstractButton::GetColor () const
{
	return this->m_Color;
}

inline float scbPultTabloAbstractButton::GetPressPosition () const
{
	return this->m_Position;
}
