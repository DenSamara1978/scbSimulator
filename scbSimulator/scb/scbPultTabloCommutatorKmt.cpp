#include "scbPultTabloCommutatorKmt.h"

scbPultTabloCommutatorKmt::scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit ) :
	scbPultTabloAbstractCommutator ( ownerScheme, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit )
{

}

scbPultTabloCommutatorKmt::scbPultTabloCommutatorKmt ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit ) :
	scbPultTabloAbstractCommutator ( ownerScheme, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit, on_bit, off_bit )
{

}

scbPultTabloCommutatorKmt::~scbPultTabloCommutatorKmt ()
{

}

void scbPultTabloCommutatorKmt::Init ()
{
	if ( this->m_SwitchRightOffContactBit >= 0 )
		this->m_OwnerScheme->SetStatusBit ( this->m_SwitchRightOffContactBit );
	if ( this->m_SwitchLeftOffContactBit >= 0 )
		this->m_OwnerScheme->SetStatusBit ( this->m_SwitchLeftOffContactBit );
	if ( this->m_PressOffContactBit >= 0 )
		this->m_OwnerScheme->SetStatusBit ( this->m_PressOffContactBit );
}

void scbPultTabloCommutatorKmt::TurnCW ()
{
	switch ( this->m_SwitchStatus )
	{
	case 0:
		// Ќачать поворот направо от центра
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_SwitchStatus = 4;
		this->AddIdleTimer ();
		break;
	case 1:
		// ѕрекратить поворот налево и начать с этого места поворот направо
		this->m_SwitchStatus = 3;
		break;
	case 2:
		// Ќачать поворот направо от левого
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_SwitchStatus = 3;
		this->AddIdleTimer ();
		break;
	case 6:
		// ѕрекратить поворот налево и начать с этого места поворот направо
		this->m_SwitchStatus = 4;
		break;
	}
}

void scbPultTabloCommutatorKmt::TurnCCW ()
{
	switch ( this->m_SwitchStatus )
	{
	case 0:
		// Ќачать поворот налево от центра
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_SwitchStatus = 1;
		this->AddIdleTimer ();
		break;
	case 3:
		// ѕрекратить поворот направо и начать с этого места поворот налево
		this->m_SwitchStatus = 1;
		break;
	case 4:
		// ѕрекратить поворот направо и начать с этого места поворот налево
		this->m_SwitchStatus = 6;
		break;
	case 5:
		// Ќачать поворот налево от правого
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_SwitchStatus = 6;
		this->AddIdleTimer ();
		break;
	}
}

void scbPultTabloCommutatorKmt::IdleTimer ( unsigned long long time )
{
	int markToDelete = 0xFF;
	float delta = static_cast < float > ( time - this->m_TimeStamp );

	// —начала изучаетс€ режим нажати€
	if ( this->m_PressStatus == 1 )
	{
		this->m_PressPosition += delta / this->c_PressTime;
		if ( ( this->m_PressContactStatus == 0 ) && ( this->m_PressPosition > this->c_PressOffBorder ) )
		{
			if ( this->m_PressOffContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_PressOffContactBit );
			this->m_PressContactStatus = 1;
		}
		if ( ( this->m_PressContactStatus == 1 ) && ( this->m_PressPosition > this->c_PressOnBorder ) )
		{
			if ( this->m_PressOnContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_PressOnContactBit );
			this->m_PressContactStatus = 2;
		}
		if ( this->m_PressPosition >= 1.0f )
		{
			this->m_PressPosition = 1.0f;
			this->m_PressStatus = 2;
		}
		else
			markToDelete &= 0xFE;
	}
	else if ( this->m_PressStatus == 3 )
	{
		this->m_PressPosition -= delta / this->c_PressTime;
		if ( ( this->m_PressContactStatus == 2 ) && ( this->m_PressPosition < this->c_PressOnBorder ) )
		{
			if ( this->m_PressOnContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_PressOnContactBit );
			this->m_PressContactStatus = 1;
		}
		if ( ( this->m_PressContactStatus == 1 ) && ( this->m_PressPosition < this->c_PressOffBorder ) )
		{
			if ( this->m_PressOffContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_PressOffContactBit );
			this->m_PressContactStatus = 0;
		}
		if ( this->m_PressPosition <= 0.0f )
		{
			this->m_PressPosition = 0.0f;
			this->m_PressStatus = 0;
		}
		else
			markToDelete &= 0xFE;
	}

	// «атем изучаетс€ режим поворота
	if ( this->m_SwitchStatus == 3 )
	{
		this->m_SwitchPosition += delta / this->c_SwitchTime;
		if ( ( this->m_SwitchContactStatus == 2 ) && ( this->m_SwitchPosition > -this->c_SwitchOnBorder ) )
		{
			if ( this->m_SwitchLeftOnContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_SwitchLeftOnContactBit );
			this->m_SwitchContactStatus = 1;
		}
		if ( ( this->m_SwitchContactStatus == 1 ) && ( this->m_SwitchPosition > -this->c_SwitchOffBorder ) )
		{
			if ( this->m_SwitchLeftOffContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_SwitchLeftOffContactBit );
			this->m_SwitchContactStatus = 0;
		}
		if ( this->m_SwitchPosition >= 0.0f )
		{
			this->m_SwitchPosition = 0.0f;
			this->m_SwitchStatus = 0;
		}
		else
			markToDelete &= 0xFD;
	}
	else if ( this->m_SwitchStatus == 4 )
	{
		this->m_SwitchPosition += delta / this->c_SwitchTime;
		if ( ( this->m_SwitchContactStatus == 0 ) && ( this->m_SwitchPosition > this->c_SwitchOffBorder ) )
		{
			if ( this->m_SwitchRightOffContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_SwitchRightOffContactBit );
			this->m_SwitchContactStatus = 3;
		}
		if ( ( this->m_SwitchContactStatus == 3 ) && ( this->m_SwitchPosition > this->c_SwitchOnBorder ) )
		{
			if ( this->m_SwitchRightOnContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_SwitchRightOnContactBit );
			this->m_SwitchContactStatus = 4;
		}
		if ( this->m_SwitchPosition >= 1.0f )
		{
			this->m_SwitchPosition = 1.0f;
			this->m_SwitchStatus = 5;
		}
		else
			markToDelete &= 0xFD;
	}
	else if ( this->m_SwitchStatus == 6 )
	{
		this->m_SwitchPosition -= delta / this->c_SwitchTime;
		if ( ( this->m_SwitchContactStatus == 4 ) && ( this->m_SwitchPosition < this->c_SwitchOnBorder ) )
		{
			if ( this->m_SwitchRightOnContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_SwitchRightOnContactBit );
			this->m_SwitchContactStatus = 3;
		}
		if ( ( this->m_SwitchContactStatus == 3 ) && ( this->m_SwitchPosition < this->c_SwitchOffBorder ) )
		{
			if ( this->m_SwitchRightOffContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_SwitchRightOffContactBit );
			this->m_SwitchContactStatus = 0;
		}
		if ( this->m_SwitchPosition <= 0.0f )
		{
			this->m_SwitchPosition = 0.0f;
			this->m_SwitchStatus = 0;
		}
		else
			markToDelete &= 0xFD;
	}
	else if ( this->m_SwitchStatus == 1 )
	{
		this->m_SwitchPosition -= delta / this->c_SwitchTime;
		if ( ( this->m_SwitchContactStatus == 0 ) && ( this->m_SwitchPosition < -this->c_SwitchOffBorder ) )
		{
			if ( this->m_SwitchLeftOffContactBit >= 0 )
				this->m_OwnerScheme->ResetStatusBit ( this->m_SwitchLeftOffContactBit );
			this->m_SwitchContactStatus = 1;
		}
		if ( ( this->m_SwitchContactStatus == 1 ) && ( this->m_SwitchPosition < -this->c_SwitchOnBorder ) )
		{
			if ( this->m_SwitchLeftOnContactBit >= 0 )
				this->m_OwnerScheme->SetStatusBit ( this->m_SwitchLeftOnContactBit );
			this->m_SwitchContactStatus = 2;
		}
		if ( this->m_SwitchPosition <= -1.0f )
		{
			this->m_SwitchPosition = -1.0f;
			this->m_SwitchStatus = 2;
		}
		else
			markToDelete &= 0xFD;
	}

	// удалить себ€ из списка пассивных таймеров
	if ( markToDelete == 0xFF )
	{
		this->DeleteIdleTimer ();
		this->m_TimeStamp = 0;
	}
	else
		this->m_TimeStamp = time;
}
