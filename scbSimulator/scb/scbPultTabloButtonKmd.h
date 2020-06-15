#pragma once

#include "scbPultTabloAbstractButton.h"

class scbPultTabloButtonKmd : public scbPultTabloAbstractButton
{
	/*
	m_Status
	0 - исходное
	1 - нажимается
	2 - нажата
	3 - отпускается
	*/

	/*
	m_ContactStatus
	0 - тыл замкнут
	1 - размокнуты все контакты
	2 - фронт замкнут
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
