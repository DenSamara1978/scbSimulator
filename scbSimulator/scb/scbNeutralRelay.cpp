#include "scbNeutralRelay.h"
#include "scbAbstractScheme.h"
#include "scbTimer.h"

scbNeutralRelay::scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit ) :
	m_OffContactBit ( 0 ),
	m_OnContactBit ( on_bit ),
	m_OffBridgeContactBit ( 0 ),
	m_OnBridgeContactBit ( 0 ),
	m_HasOffContact ( false ),
	m_HasBridgeContact ( false ),
	scbRelay ( ownerScheme )
{
}

scbNeutralRelay::scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit, int off_bit ) :
	m_OffContactBit ( off_bit ),
	m_OnContactBit ( on_bit ),
	m_OffBridgeContactBit ( 0 ),
	m_OnBridgeContactBit ( 0 ),
	m_HasOffContact ( true ),
	m_HasBridgeContact ( false ),
	scbRelay ( ownerScheme )
{
}

scbNeutralRelay::scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit, int off_bit, int on_bridge_bit, int off_bridge_bit ) :
	m_OffContactBit ( off_bit ),
	m_OnContactBit ( on_bit ),
	m_OffBridgeContactBit ( off_bridge_bit ),
	m_OnBridgeContactBit ( on_bridge_bit ),
	m_HasOffContact ( true ),
	m_HasBridgeContact ( true ),
	scbRelay ( ownerScheme )
{
}

scbNeutralRelay::~scbNeutralRelay ()
{
}

void scbNeutralRelay::Init ()
{
	if ( this->m_HasOffContact )
		this->m_OwnerScheme->SetStatusBit ( this->m_OffContactBit );
	if ( this->m_HasBridgeContact )
		this->m_OwnerScheme->SetStatusBit ( this->m_OffBridgeContactBit );
}

void scbNeutralRelay::SetMode ( unsigned long mode )
{
	if ( this->m_TargetMode == mode )
	{
		// Целевой режим соответствует вычисленному, ничего не менять
		return;
	}
	unsigned long long new_delay, time;
	time = scbTimer::Instance ()->GetWorkingTime ();

	int starting = -1;
	int shifting = -1;
	int dir = 0;

	for ( const auto& sample : this->m_TimeSamples )
	{
		if ( ( sample.ModeFrom == this->m_CurrentMode ) && ( sample.ModeTo == mode ) )
		{
			starting = sample.Starting;
			shifting = sample.Shifting;
			dir = 1;
			break;
		}
	}
	if ( dir == 0 )
	{
		for ( const auto& sample : this->m_TimeSamples )
		{
			if ( ( sample.ModeFrom == this->m_TargetMode ) && ( sample.ModeTo == mode ) )
			{
				starting = sample.Starting;
				shifting = sample.Shifting;
				dir = -1;
				break;
			}
		}
	}
	if ( starting == -1 )
	{
		// Указанная смена режима не изменит положения реле
		this->m_CurrentMode = mode;
		return;
	}

	// dir == 1 если движение начинается или оно продолжается в том же направлении
	// dir == -1 если движение меняет направление

	float diff_time = static_cast<float> ( time - this->m_TimeStamp );
	float interval;

	switch ( this->m_Status )
	{
	case 0:
		// Начать процесс трогания на подъем
		this->m_TimeStamp = time;
		this->m_Status = 1;
		scbTimer::Instance ()->AddTimeToWork ( this, starting, 0 );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	case 1:
		if ( dir == 1 )
		{
			// Продолжаем трогаться на подъем по другому времени
			new_delay = static_cast< unsigned long long > ( starting * ( 1.0f - diff_time / this->m_Starting ) );
			this->m_TimeStamp = time - starting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переходим в положение без тока
			this->m_TimeStamp = 0;
			this->m_Status = 0;
			scbTimer::Instance ()->DeleteTimeToWork ( this );
			this->m_Starting = 0;
			this->m_Shifting = 0;
		}
		break;
	case 2:
		interval = shifting * diff_time / this->m_Shifting;
		new_delay = static_cast< unsigned long long > (( dir == 1 ) ? shifting - interval : interval );
		if ( dir != 1 )
			this->m_Status = 5;
		this->m_TimeStamp = time - shifting + new_delay;
		scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	case 3:
		// Начать процесс трогания на отпускание
		this->m_TimeStamp = time;
		this->m_Status = 4;
		scbTimer::Instance ()->AddTimeToWork ( this, starting, 0 );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	case 4:
		if ( dir == 1 )
		{
			// Продолжаем трогаться на отпадание по другому времени
			new_delay = static_cast< unsigned long long > ( starting * ( 1.0f - diff_time / this->m_Starting ) );
			this->m_TimeStamp = time - starting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переходим в положение под током
			this->m_TimeStamp = 0;
			this->m_Status = 3;
			scbTimer::Instance ()->DeleteTimeToWork ( this );
			this->m_Starting = 0;
			this->m_Shifting = 0;
		}
		break;
	case 5:
		interval = shifting * diff_time / this->m_Shifting;
		new_delay = static_cast< unsigned long long > ( ( dir == 1 ) ? shifting - interval : interval );
		if ( dir != 1 )
			this->m_Status = 2;
		this->m_TimeStamp = time - shifting + new_delay;
		scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	}
	this->m_TargetMode = mode;
}

void scbNeutralRelay::TimeToWork ( int signal, unsigned long long time )
{
	switch ( this->m_Status )
	{
	case 1:
		if ( this->m_HasOffContact && ( this->m_OffContactBit >= 0 ))
			this->m_OwnerScheme->ResetStatusBit ( this->m_OffContactBit );
		if ( this->m_HasBridgeContact && ( this->m_OnBridgeContactBit >= 0 ))
			this->m_OwnerScheme->SetStatusBit ( this->m_OnBridgeContactBit );
		this->m_TimeStamp = time;
		this->m_Status = 2;
		scbTimer::Instance ()->AddTimeToWork ( this, this->m_Shifting, 0 );
		break;
	case 2:
		if ( this->m_OnContactBit >= 0 )
			this->m_OwnerScheme->SetStatusBit ( this->m_OnContactBit );
		if ( this->m_HasBridgeContact && ( this->m_OffBridgeContactBit >= 0 ) )
			this->m_OwnerScheme->ResetStatusBit ( this->m_OffBridgeContactBit );
		this->m_TimeStamp = 0;
		this->m_Status = 3;
		this->m_CurrentMode = this->m_TargetMode;
		this->m_Starting = 0;
		this->m_Shifting = 0;
		break;
	case 4:
		if ( this->m_OnContactBit >= 0 )
			this->m_OwnerScheme->ResetStatusBit ( this->m_OnContactBit );
		if ( this->m_HasBridgeContact && ( this->m_OffBridgeContactBit >= 0 ) )
			this->m_OwnerScheme->SetStatusBit ( this->m_OffBridgeContactBit );
		this->m_TimeStamp = time;
		this->m_Status = 5;
		scbTimer::Instance ()->AddTimeToWork ( this, this->m_Shifting, 0 );
		break;
	case 5:
		if ( this->m_HasOffContact && ( this->m_OffContactBit >= 0 ) )
			this->m_OwnerScheme->SetStatusBit ( this->m_OffContactBit );
		if ( this->m_HasBridgeContact && ( this->m_OnBridgeContactBit >= 0 ) )
			this->m_OwnerScheme->ResetStatusBit ( this->m_OnBridgeContactBit );
		this->m_TimeStamp = 0;
		this->m_Status = 0;
		this->m_CurrentMode = this->m_TargetMode;
		this->m_Starting = 0;
		this->m_Shifting = 0;
		break;
	}
}
