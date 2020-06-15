#pragma once

#include "scbPultTabloAbstractButton.h"

class scbPultTabloButtonKmdf : public scbPultTabloAbstractButton
{
	/*
	m_Status
	0 - исходное
	1 - нажимается до фиксации
	2 - нажата до фиксации
	3 - отпускается до фиксации
	4 - фиксация
	5 - нажимается после фиксации
	6 - нажата после фиксации
	7 - отпускается после фиксации
	*/

	/*
	m_ContactStatus
	0 - тыл замкнут
	1 - размокнуты все контакты
	2 - фронт замкнут
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
