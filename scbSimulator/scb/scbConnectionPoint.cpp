#include "scbAbstractScheme.h"
#include "scbConnectionPoint.h"
#include "scbConnectionPointScheme.h"
//#include "..\track\trackSwitch.h"

scbConnectionPoint::scbConnectionPoint ( scbAbstractScheme* ownerScheme, scbConnectionPoint::ConnectionType type ) :
	scbAbstractSchemeDevice ( ownerScheme ),
	m_Type ( type )
{
}

scbConnectionPoint::~scbConnectionPoint ()
{

}

/*void scbMotorDriveDevice::SetSwitch ( trackSwitch* point )
{
	this->m_TrackSwitch = point;
	if ( point != nullptr )
		point->SetDrive ( this );
}*/

void scbConnectionPoint::Init ()
{
}

void scbConnectionPoint::SetSignal ( const scbOutputStream& param )
{
	switch ( this->m_Type )
	{
	case scbConnectionPoint::Reciever_DC:
		dynamic_cast<scbConnectionPointScheme*> ( this->m_OwnerScheme )->SetStatus ( param.Mask [0] & 3 );
		break;
	case scbConnectionPoint::Reciever_25Hz:
		dynamic_cast<scbConnectionPointScheme*> ( this->m_OwnerScheme )->SetStatus ( param.Mask [0] & 0xC );
		break;
	case scbConnectionPoint::Reciever_50Hz:
		dynamic_cast<scbConnectionPointScheme*> ( this->m_OwnerScheme )->SetStatus ( param.Mask [0] & 0x30 );
		break;
	case scbConnectionPoint::Reciever_75Hz:
		dynamic_cast<scbConnectionPointScheme*> ( this->m_OwnerScheme )->SetStatus ( param.Mask [0] & 0xC0 );
		break;
	case scbConnectionPoint::Reciever_ToneFrequency:
		dynamic_cast<scbConnectionPointScheme*> ( this->m_OwnerScheme )->SetStatus ( param.Mask [0] & 0x1FFFB000 );
		break;
	}

}

void scbConnectionPoint::ChangeStatus ( const scbOutputStream& param )
{

}

void scbConnectionPoint::IdleTimer ( unsigned long long time )
{
	// Ïףסעמי גûחמג
}
