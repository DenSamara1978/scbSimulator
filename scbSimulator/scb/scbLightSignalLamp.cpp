#include "scbAbstractScheme.h"
#include "scbLightSignalLamp.h"

scbLightSignalLamp::scbLightSignalLamp ( scbAbstractScheme* ownerScheme ) :
	scbAbstractSchemeDevice ( ownerScheme ),
	m_Status ( 0 ),
	m_Bright ( 0.0f ),
	m_TimeStamp ( 0 ),
	m_Velocity ( 0.0f )
{
}

scbLightSignalLamp::~scbLightSignalLamp ()
{
}

void scbLightSignalLamp::Init ()
{
	// пустой вызов
}

void scbLightSignalLamp::ChangeStatus ( const scbOutputStream& param )
{
	static char targetStatus [] = { 0, 1, 2, 2, 3, 3, 3, 3, 0, 4, 5, 5, 6, 6, 6, 6 };

	int old_status = this->m_Status;
	this->m_Status = targetStatus [param.Mask [0] & 0xF];
	if ( old_status != this->m_Status )
	{
		this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		if ( m_TargetBright [this->m_Status] > this->m_Bright )
			this->m_Velocity = cLampOnVelocity;
		else
			this->m_Velocity = cLampOffVelocity;
		this->AddIdleTimer ();
	}
}

void scbLightSignalLamp::IdleTimer ( unsigned long long time )
{
	float bright = this->m_Bright + this->m_Velocity * ( time - this->m_TimeStamp ) / 1000.0f;
	this->m_TimeStamp = time;
	if ((( bright <= m_TargetBright [this->m_Status] ) && ( this->m_Bright >= m_TargetBright [this->m_Status] )) ||
		(( bright >= m_TargetBright [this->m_Status] ) && ( this->m_Bright <= m_TargetBright [this->m_Status] )))
	{
		this->m_Bright = m_TargetBright [this->m_Status];
		this->m_Velocity = 0.0f;
		this->DeleteIdleTimer ();
	}
	else
		this->m_Bright = bright;
}
