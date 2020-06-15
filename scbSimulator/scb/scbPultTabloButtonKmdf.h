#pragma once

#include "scbPultTabloAbstractButton.h"

class scbPultTabloButtonKmdf : public scbPultTabloAbstractButton
{
	/*
	m_Status
	0 - ��������
	1 - ���������� �� ��������
	2 - ������ �� ��������
	3 - ����������� �� ��������
	4 - ��������
	5 - ���������� ����� ��������
	6 - ������ ����� ��������
	7 - ����������� ����� ��������
	*/

	/*
	m_ContactStatus
	0 - ��� �������
	1 - ���������� ��� ��������
	2 - ����� �������
	*/

public:
	scbPultTabloButtonKmdf ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit );
	scbPultTabloButtonKmdf ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit );
	virtual ~scbPultTabloButtonKmdf () override;

	virtual void Init () override;

	virtual void Press () override;
	virtual void Release () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
