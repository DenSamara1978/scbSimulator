#include "AbstractScheme.h"
#include "ConnectionPoint.h"
#include "ConnectionPointScheme.h"
//#include "..\track\Switch.h"

using namespace scb;

ConnectionPoint::ConnectionPoint(AbstractScheme* ownerScheme, ConnectionPoint::ConnectionType type) :
	AbstractSchemeDevice(ownerScheme),
	type(type)
{
}

ConnectionPoint::~ConnectionPoint()
{

}

/*void scbMotorDriveDevice::SetSwitch ( trackSwitch* point )
{
	this->m_TrackSwitch = point;
	if ( point != nullptr )
		point->SetDrive ( this );
}*/

void ConnectionPoint::initialize()
{
}

void ConnectionPoint::setSignal(const OutputStream& param)
{
	unsigned long parameter = 0;
	switch (this->type)
	{
		case ConnectionType::RecieverDC:
			parameter = param.mask[0] & 3;
			break;
		case ConnectionType::Reciever25Hz:
			parameter = param.mask[0] & 0xC;
			break;
		case ConnectionType::Reciever50Hz:
			parameter = param.mask[0] & 0x30;
			break;
		case ConnectionType::Reciever75Hz:
			parameter = param.mask[0] & 0xC0;
			break;
		case ConnectionType::RecieverToneFrequency:
			parameter = param.mask[0] & 0x1FFFB000;
			break;
	}
	dynamic_cast<ConnectionPointScheme*>(this->ownerScheme)->setStatus(parameter);
}

void ConnectionPoint::changeStatus(const OutputStream& param)
{

}

void ConnectionPoint::idleTimer(unsigned long long time)
{
	// Ïףסעמי גûחמג
}
