#include "scbPultTabloBell.h"

scbPultTabloBell::scbPultTabloBell ( scbAbstractScheme* ownerScheme, int continuously_bit, int impulse_bit ) :
	m_Status ( 0 ),
	scbAbstractSchemeDevice ( ownerScheme )
{
	if ( ( continuously_bit >= 0 ) && ( continuously_bit <= 255 ) )
	{
		this->m_ContinuouslyElement = ( continuously_bit & 0xFE00 ) >> 5;
		this->m_ContinuouslyMask = 1 << ( continuously_bit & 0x1FF );
	}
	else
	{
		this->m_ContinuouslyElement = 0;
		this->m_ContinuouslyMask = 0;
	}

	if ( ( impulse_bit >= 0 ) && ( impulse_bit <= 255 ) )
	{
		this->m_ImpulseElement = ( impulse_bit & 0xFE00 ) >> 5;
		this->m_ImpulseMask = 1 << ( impulse_bit & 0x1FF );
	}
	else
	{
		this->m_ImpulseElement = 0;
		this->m_ImpulseMask = 0;
	}
}

scbPultTabloBell::~scbPultTabloBell ()
{

}

void scbPultTabloBell::Init ()
{
	// пустой вызов
}

void scbPultTabloBell::IdleTimer ( unsigned long long time )
{
	// TODO
}

void scbPultTabloBell::ChangeStatus ( const scbOutputStream& param )
{
	/*
	бит 0 - работа звонка
	бит 1 - звонковый импульс // TODO - обработать
	*/
	int new_status = 0;

	if ( ( param.Mask [this->m_ImpulseElement] & this->m_ImpulseMask ) != 0 )
		new_status += 2;
	if ( ( param.Mask [this->m_ContinuouslyElement] & this->m_ContinuouslyMask ) != 0 )
		new_status += 1;

	if ( ( this->m_Status == 0 ) && ( new_status != 0 ) )
	{
		// TODO «апустить проигрывание циклического звука звонка
	}
	else if ( ( this->m_Status != 0 ) && ( new_status == 0 ) )
	{
		// TODO ќстановить проигрывание циклического звука звонка
	}
	this->m_Status = new_status;
}
