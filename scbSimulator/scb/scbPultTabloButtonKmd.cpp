#include "scbPultTabloButtonKmd.h"
#include "scbAbstractScheme.h"

scbPultTabloButtonKmd::scbPultTabloButtonKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit ) :
	scbPultTabloAbstractButton ( ownerScheme, color, on_bit )
{
}

scbPultTabloButtonKmd::scbPultTabloButtonKmd ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit ) :
	scbPultTabloAbstractButton ( ownerScheme, color, on_bit, off_bit )
{
}

scbPultTabloButtonKmd::~scbPultTabloButtonKmd ()
{

}

void scbPultTabloButtonKmd::Init ()
{
	if ( this->m_OffContactBit >= 0 )
		this->m_OwnerScheme->SetStatusBit ( this->m_OffContactBit );
}

void scbPultTabloButtonKmd::Press ()
{
	switch ( this->m_Status )
	{
	case 0:
		// инициировать нажатие
		this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_Status = 1;
		this->AddIdleTimer ();
		break;
	case 3:
		// прекратить отпускание и с этого места начать нажатие
		this->m_Status = 1;
		break;
	}
}

void scbPultTabloButtonKmd::Release ()
{
	switch ( this->m_Status )
	{
	case 1:
		// прекратить нажатие и с этого места начать отпускание
		this->m_Status = 3;
		break;
	case 2:
		// инициировать отпускание
		this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_Status = 3;
		this->AddIdleTimer ();
		break;
	}
}

void scbPultTabloButtonKmd::IdleTimer ( unsigned long long time )
{
	float delta = static_cast < float > ( time - this->m_TimeStamp );
	this->m_TimeStamp = time;
	if ( this->m_Status == 1 )
	{
		this->m_Position += delta / this->c_PressTime;
		if ( ( this->m_ContactStatus == 0 ) && ( this->m_Position > this->c_OffBorder ))
		{
			if ( this->m_OffContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_OffContactBit );
			this->m_ContactStatus = 1;
		}
		if (( this->m_ContactStatus == 1 ) && ( this->m_Position > this->c_OnBorder ))
		{
			if ( this->m_OnContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_OnContactBit );
			this->m_ContactStatus = 2;
		}
		if ( this->m_Position < 1.0f )
			return;
		else
		{
			this->m_Position = 1.0f;
			this->m_Status = 2;
			this->m_TimeStamp = 0;
		}
	}
	else if ( this->m_Status == 3 )
	{
		this->m_Position -= delta / this->c_PressTime;
		if ( ( this->m_ContactStatus == 2 ) && ( this->m_Position < this->c_OnBorder ) )
		{
			if ( this->m_OnContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_OnContactBit );
			this->m_ContactStatus = 1;
		}
		if ( ( this->m_ContactStatus == 1 ) && ( this->m_Position < this->c_OffBorder ))
		{
			if ( this->m_OffContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_OffContactBit );
			this->m_ContactStatus = 0;
		}
		if ( this->m_Position > 0.0f )
			return;
		else
		{
			this->m_Position = 0.0f;
			this->m_Status = 0;
			this->m_TimeStamp = 0;
		}
	}
	// удалить себя из списка пассивных таймеров
	this->DeleteIdleTimer ();
}
