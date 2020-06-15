#include "scbPultTabloAbstractButton.h"
#include "scbAbstractScheme.h"

scbPultTabloAbstractButton::scbPultTabloAbstractButton ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit ) :
	m_Position ( 0.0f ),
	m_Color ( color ),
	m_TimeStamp ( 0 ),
	m_Status ( 0 ),
	m_ContactStatus ( 0 ),
	m_OffContactBit ( -1 ),
	m_OnContactBit ( on_bit ),
	scbPultTabloActiveDevice ( ownerScheme )
{

}

scbPultTabloAbstractButton::scbPultTabloAbstractButton ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit ) :
	m_Position ( 0.0f ),
	m_Color ( color ),
	m_TimeStamp ( 0 ),
	m_Status ( 0 ),
	m_ContactStatus ( 0 ),
	m_OffContactBit ( off_bit ),
	m_OnContactBit ( on_bit ),
	scbPultTabloActiveDevice ( ownerScheme )
{

}

scbPultTabloAbstractButton::~scbPultTabloAbstractButton ()
{

}
