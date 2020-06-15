#include "scbPultTabloLampGroup.h"

scbPultTabloLampGroup::scbPultTabloLampGroup ( scbAbstractScheme* ownerScheme ) :
	scbAbstractSchemeDevice ( ownerScheme )
{
	memset ( &( this->m_LampStatus ), 0, sizeof ( this->m_LampStatus ) );
}

scbPultTabloLampGroup::~scbPultTabloLampGroup ()
{

}

void scbPultTabloLampGroup::Init ()
{
	// пустой вызов
}

void scbPultTabloLampGroup::ChangeStatus ( const scbOutputStream& param )
{
	memcpy ( &( this->m_LampStatus ), &param, sizeof ( param ) );
}

void scbPultTabloLampGroup::IdleTimer ( unsigned long long )
{
	// Пустой вызов
}