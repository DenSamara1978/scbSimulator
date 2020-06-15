#pragma once

#include "scbAbstractScheme.h"
#include "scbAbstractSchemeDevice.h"

class scbPultTabloLampGroup : public scbAbstractSchemeDevice
{
	scbOutputStream m_LampStatus; // Побитно содержит состояния ламп

public:
	scbPultTabloLampGroup ( scbAbstractScheme* ownerScheme );
	virtual ~scbPultTabloLampGroup () override;

	bool GetLampStatus ( int bit ) const;

	virtual void Init () override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается схемой-хозяином после расчета
	virtual void IdleTimer ( unsigned long long time ) override;
};

inline bool scbPultTabloLampGroup::GetLampStatus ( int bit ) const
{
	return ((( this->m_LampStatus.Mask [( bit & 0xE0 ) >> 5] ) & ( 1 << ( bit & 31 ))) != 0 );
}
