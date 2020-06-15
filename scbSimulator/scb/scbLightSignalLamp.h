#pragma once

#include "scbAbstractSchemeDevice.h"

class scbLightSignalLamp : public scbAbstractSchemeDevice
{
public:
	enum class LampColor
	{
		Red = 0,
		Yellow,
		Green,
		Blue,
		White,
		Milk,
	};

private:
	static constexpr float cLampOnVelocity = 5.0f;
	static constexpr float cLampOffVelocity = -3.0f;

	inline static float m_TargetBright [] = { 0.0f, 0.5f, 0.8f, 1.0f, 0.5f, 0.8f, 1.0f };

	LampColor m_Color;
	/*
	0 - ����� ��������
	1 - ��� 15 ��
	2 - ���� 15 ��
	3 - ���� 15 ��
	4 - ��� 25 ��
	5 - ���� 25 ��
	6 - ���� 25 ��
	*/
	char m_Status;
	float m_Bright; // 0.0f - 1.0f �������
	float m_Velocity; // �������� ��������� �������, ��.���./���.
	unsigned long long m_TimeStamp;

public:
	scbLightSignalLamp ( scbAbstractScheme* ownerScheme );
	virtual ~scbLightSignalLamp () ;

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ����������-��������

	void SetColor ( LampColor color );
	LampColor GetColor () const;
	float GetBright () const;
};

inline void scbLightSignalLamp::SetColor ( LampColor color )
{
	this->m_Color = color;
}

inline scbLightSignalLamp::LampColor scbLightSignalLamp::GetColor () const
{
	return this->m_Color;
}

inline float scbLightSignalLamp::GetBright () const
{
	return this->m_Bright;
}
