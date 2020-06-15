#include "scbPultTabloAbstractCommutator.h"

scbPultTabloAbstractCommutator::scbPultTabloAbstractCommutator ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit ) :
	scbPultTabloActiveDevice ( ownerScheme ),
	m_Pressable ( false ),
	m_PressOnContactBit ( -1 ),
	m_PressOffContactBit ( -1 ),
	m_SwitchLeftOnContactBit ( leftPos_onBit ),
	m_SwitchLeftOffContactBit ( leftPos_offBit ),
	m_SwitchRightOnContactBit ( rightPos_onBit ),
	m_SwitchRightOffContactBit ( rightPos_offBit ),
	m_PressStatus ( 0 ),
	m_PressContactStatus ( 0 ),
	m_SwitchStatus ( 0 ),
	m_SwitchContactStatus ( 0 ),
	m_PressPosition ( 0.0f ),
	m_SwitchPosition ( 0.0f ),
	m_Color ( color ),
	m_TimeStamp ( 0 )
{

}

scbPultTabloAbstractCommutator::scbPultTabloAbstractCommutator ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit ) :
	scbPultTabloActiveDevice ( ownerScheme ),
	m_Pressable ( true ),
	m_PressOnContactBit ( on_bit ),
	m_PressOffContactBit ( off_bit ),
	m_SwitchLeftOnContactBit ( leftPos_onBit ),
	m_SwitchLeftOffContactBit ( leftPos_offBit ),
	m_SwitchRightOnContactBit ( rightPos_onBit ),
	m_SwitchRightOffContactBit ( rightPos_offBit ),
	m_PressStatus ( 0 ),
	m_PressContactStatus ( 0 ),
	m_SwitchStatus ( 0 ),
	m_SwitchContactStatus ( 0 ),
	m_PressPosition ( 0.0f ),
	m_SwitchPosition ( 0.0f ),
	m_Color ( color ),
	m_TimeStamp ( 0 )
{

}

scbPultTabloAbstractCommutator::~scbPultTabloAbstractCommutator ()
{

}

void scbPultTabloAbstractCommutator::Press ()
{
	if ( !this->m_Pressable ) return;
	switch ( this->m_PressStatus )
	{
	case 0:
		// инициировать нажатие
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_PressStatus = 1;
		this->AddIdleTimer ();
		break;
	case 3:
		// прекратить отпускание и с этого места начать нажатие
		this->m_PressStatus = 1;
		break;
	}
}

void scbPultTabloAbstractCommutator::Release ()
{
	if ( !this->m_Pressable ) return;
	switch ( this->m_PressStatus )
	{
	case 1:
		// прекратить нажатие и с этого места начать отпускание
		this->m_PressStatus = 3;
		break;
	case 2:
		// инициировать отпускание
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_PressStatus = 3;
		this->AddIdleTimer ();
		break;
	}
}
