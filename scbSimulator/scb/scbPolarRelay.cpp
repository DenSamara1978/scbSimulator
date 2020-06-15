#include "scbPolarRelay.h"
#include "scbAbstractScheme.h"
#include "scbTimer.h"

scbPolarRelay::scbPolarRelay ( scbAbstractScheme* ownerScheme, int dir_bit, int rev_bit ) :
	m_DirectContactBit ( dir_bit ),
	m_ReverseContactBit ( rev_bit ),
	scbRelay ( ownerScheme )
{
}

scbPolarRelay::~scbPolarRelay ()
{
}

void scbPolarRelay::Init ()
{
	this->m_OwnerScheme->SetStatusBit ( this->m_DirectContactBit );
}

void scbPolarRelay::SetMode ( unsigned long mode )
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

	// dir == 1 если движение начинается или онон продолжается в том же направлении
	// dir == -1 если движение меняет направление

	switch ( this->m_Status )
	{
	case 0:
		// Начать процесс трогания в переведенное
		this->m_TimeStamp = time;
		this->m_Status = 1;
		scbTimer::Instance ()->AddTimeToWork ( this, starting, 0 );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	case 1:
		if ( dir == 1 )
		{
			// Продолжаем трогаться в переведенное по другому времени
			new_delay = static_cast< unsigned long long > ( starting * ( 1.0f - ( static_cast < float > ( time - this->m_TimeStamp ) ) / this->m_Starting ) );
			this->m_TimeStamp = time - starting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переходим в прямое положение
			this->m_TimeStamp = 0;
			this->m_Status = 0;
			scbTimer::Instance ()->DeleteTimeToWork ( this );
			this->m_Starting = 0;
			this->m_Shifting = 0;
		}
		break;
	case 2:
		if ( dir == 1 )
		{
			// Продолжаем перелет в переведенное другому времени
			new_delay = static_cast< unsigned long long > ( shifting * ( 1.0f - ( static_cast < float > ( time - this->m_TimeStamp ) ) / this->m_Shifting ) );
			this->m_TimeStamp = time - shifting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переключаемся в состояние перелета в прямое
			new_delay = static_cast< unsigned long long > ( shifting * ( static_cast < float > ( time - this->m_TimeStamp ) / this->m_Shifting ) );
			this->m_TimeStamp = time - shifting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
			this->m_Status = 5;
		}
		break;
	case 3:
		// Начать процесс трогания в прямое
		this->m_TimeStamp = time;
		this->m_Status = 4;
		scbTimer::Instance ()->AddTimeToWork ( this, starting, 0 );
		this->m_Starting = starting;
		this->m_Shifting = shifting;
		break;
	case 4:
		if ( dir == 1 )
		{
			// Продолжаем трогаться в прямое по другому времени
			new_delay = static_cast< unsigned long long > ( starting * ( 1.0f - ( static_cast < float > ( time - this->m_TimeStamp ) ) / this->m_Starting ) );
			this->m_TimeStamp = time - starting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переходим в переведенное положение
			this->m_TimeStamp = 0;
			this->m_Status = 3;
			scbTimer::Instance ()->DeleteTimeToWork ( this );
			this->m_Starting = 0;
			this->m_Shifting = 0;
		}
		break;
	case 5:
		if ( dir == 1 )
		{
			// Продолжаем перелет в прямое по другому времени
			new_delay = static_cast< unsigned long long > ( shifting * ( 1.0f - ( static_cast < float > ( time - this->m_TimeStamp ) ) / this->m_Shifting ) );
			this->m_TimeStamp = time - shifting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
		}
		else
		{
			// Переключаемся в состояние перелета в переведенное
			new_delay = static_cast< unsigned long long > ( shifting * ( static_cast < float > ( time - this->m_TimeStamp ) / this->m_Shifting ) );
			this->m_TimeStamp = time - shifting + new_delay;
			scbTimer::Instance ()->ChangeTimeToWork ( this, new_delay );
			this->m_Starting = starting;
			this->m_Shifting = shifting;
			this->m_Status = 2;
		}
		break;
	}
	this->m_TargetMode = mode;
}

void scbPolarRelay::TimeToWork ( int signal, unsigned long long time )
{
	switch ( this->m_Status )
	{
	case 1:
		if ( this->m_DirectContactBit >= 0 )
			this->m_OwnerScheme->ResetStatusBit ( this->m_DirectContactBit );
		this->m_TimeStamp = time;
		this->m_Status = 2;
		scbTimer::Instance ()->AddTimeToWork ( this, this->m_TimeSamples [this->m_TargetMode].Shifting, 0 );
		break;
	case 2:
		if ( this->m_ReverseContactBit >= 0 )
			this->m_OwnerScheme->SetStatusBit ( this->m_ReverseContactBit );
		this->m_TimeStamp = 0;
		this->m_Status = 3;
		this->m_CurrentMode = this->m_TargetMode;
		this->m_Starting = 0;
		this->m_Shifting = 0;
		break;
	case 4:
		if ( this->m_ReverseContactBit >= 0 )
			this->m_OwnerScheme->ResetStatusBit ( this->m_ReverseContactBit );
		this->m_TimeStamp = time;
		this->m_Status = 5;
		scbTimer::Instance ()->AddTimeToWork ( this, this->m_TimeSamples [this->m_TargetMode].Shifting, 0 );
		break;
	case 5:
		if ( this->m_DirectContactBit >= 0 )
			this->m_OwnerScheme->SetStatusBit ( this->m_DirectContactBit );
		this->m_TimeStamp = 0;
		this->m_Status = 0;
		this->m_CurrentMode = this->m_TargetMode;
		this->m_Starting = 0;
		this->m_Shifting = 0;
		break;
	}
}
