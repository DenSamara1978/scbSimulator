#pragma once

#include "scbAbstractScheme.h"
#include "scbAbstractSchemeDevice.h"

class scbPultTabloAmpermeter : public scbAbstractSchemeDevice
{
public:
	scbPultTabloAmpermeter ( scbAbstractScheme* ownerScheme, int start_bit );
	virtual ~scbPultTabloAmpermeter () override;

	virtual void Init () override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override;
	virtual void IdleTimer ( unsigned long long time ) override;
};
