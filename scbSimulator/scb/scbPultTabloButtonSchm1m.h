#pragma once

#include "scbPultTabloButtonKmd.h"


// TODO Добавить функционал счетчика

class scbPultTabloButtonSchm1m : public scbPultTabloButtonKmd
{
public:
	scbPultTabloButtonSchm1m ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit );
	virtual ~scbPultTabloButtonSchm1m () override;

	virtual void Press () override;
	virtual void Release () override;

	virtual void IdleTimer ( unsigned long long time ) override;
};
