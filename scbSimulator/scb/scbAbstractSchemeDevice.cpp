#include "scbAbstractSchemeDevice.h"
#include "scbAbstractScheme.h"

scbAbstractSchemeDevice::scbAbstractSchemeDevice ( scbAbstractScheme* ownerScheme ) :
	m_OwnerScheme ( ownerScheme ),
	m_HasIdleTimer ( false )
{
}

scbAbstractSchemeDevice::~scbAbstractSchemeDevice ()
{
	auto timer = scbTimer::Instance ();
	timer->DeleteIdleTimer ( this );
	timer->DeleteTimeToWork ( this );
	this->m_OwnerScheme = nullptr;
}

void scbAbstractSchemeDevice::MapInputOutput ( int in_bit, int out_bit )
{
	if ( ( in_bit > 255 ) || ( in_bit < 0 ) || ( out_bit > 255 ) || ( out_bit < 0 ) ) return;
	Convertation conv;
	conv.InputElement = ( in_bit & 0xFFE0 ) >> 5;
	conv.InputMask = 1 << ( in_bit & 0x1F );
	conv.OutputElement = ( out_bit & 0xFFE0 ) >> 5;
	conv.OutputMask = 1 << ( out_bit & 0x1F );
	this->m_Convertations.push_back ( conv );
}

void scbAbstractSchemeDevice::TimeToWork ( int signal, unsigned long long time )
{
	// Ïףסעמי גûחמג
}