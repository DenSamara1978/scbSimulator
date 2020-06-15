#pragma once

#include "scbAbstractSchemeDevice.h"

class scbPultTabloBell : public scbAbstractSchemeDevice
{
	int m_Status; // 0 - �������� ���������, 1 - ���������� ���������
	int m_ContinuouslyElement;
	unsigned long m_ContinuouslyMask;
	int m_ImpulseElement;
	unsigned long m_ImpulseMask;

public:
	scbPultTabloBell ( scbAbstractScheme* ownerScheme, int continuously_bit, int impulse_bit );
	virtual ~scbPultTabloBell () override;

	virtual void Init () override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ������-�������� ����� �������
	virtual void IdleTimer ( unsigned long long time ) override;
};
