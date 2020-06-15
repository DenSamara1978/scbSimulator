#pragma once

#include "scbPultTabloAbstractButton.h"

class scbPultTabloButtonKmd : public scbPultTabloAbstractButton
{
	/*
	m_Status
	0 - ��������
	1 - ����������
	2 - ������
	3 - �����������
	*/

	/*
	m_ContactStatus
	0 - ��� �������
	1 - ���������� ��� ��������
	2 - ����� �������
	*/

public:
	scbPultTabloButtonKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit );
	scbPultTabloButtonKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit );
	virtual ~scbPultTabloButtonKmd () override;

	virtual void Init () override;

	virtual void Press () override;
	virtual void Release () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
