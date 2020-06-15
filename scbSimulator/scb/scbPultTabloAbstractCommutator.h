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
	float m_PressPosition; // Физическое положение нажимной рукоятки: 0.0f - исходное, 1.0f - нажатое
	float m_SwitchPosition; // Физическое положение поворотного коммутатора: 0.0f - среднее, -1.0f - положение против часовой ( налево), 1.0f - положение по часовой ( направо )
	scbPultTablo::Color m_Color;
	bool m_Pressable; // Имеется нажимная рукоятка
	unsigned long long m_TimeStamp;
	/*
	0 - исходное
	1 - нажимается
	2 - нажата
	3 - отпускается
	*/
	int m_PressStatus;
	/*
	0 - тыл замкнут
	1 - размокнуты все контакты
	2 - фронт замкнут
	*/
	int m_PressContactStatus;
	int m_SwitchStatus; // 0 - исходное, остальное специфично
	int m_SwitchContactStatus; // 0 - исходное, остальное специфично

	static constexpr float c_PressOnBorder = 0.7f; // значение положения коммутации фронтовых контактов
	static constexpr float c_PressOffBorder = 0.2f; // Значение положения коммутации тыловых контактов
	static constexpr float c_PressTime = 300.0f; // Время нажатия/отпуска, мс

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
