#pragma once

#include "scbPultTabloActiveDevice.h"
#include "scbPultTablo.h"

class scbPultTabloAbstractButton : public scbPultTabloActiveDevice
{
protected:
	int m_OnContactBit;
	int m_OffContactBit;
	float m_Position; // Физическое положение кнопки: 0.0f - исходное, 1.0f - нажатое
	scbPultTablo::Color m_Color;
	unsigned long long m_TimeStamp;
	int m_Status; // 0 - исходное положение, остальное специфично
	int m_ContactStatus; // 0 - исходное положение, остальное специфично

	static constexpr float c_OnBorder = 0.7f; // значение положения коммутации фронтовых контактов
	static constexpr float c_OffBorder = 0.2f; // Значение положения коммутации тыловых контактов
	static constexpr float c_FixBorder = 0.8f; // Значение положения фиксации
	static constexpr float c_PressTime = 300.0f; // Время нажатия/отпуска, мс

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
