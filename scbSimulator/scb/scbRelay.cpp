#include "scbRelay.h"

scbRelay::scbRelay ( scbAbstractScheme* ownerScheme ) :
	scbAbstractSchemeDevice ( ownerScheme ),
	m_CurrentMode ( 0 ),
	m_TargetMode ( 0 ),
	m_TimeStamp ( 0 ),
	m_Status ( 0 ),
	m_Starting ( 0 ),
	m_Shifting ( 0 )
{

}

scbRelay::~scbRelay ()
{
}

void scbRelay::SetSample ( int from_mode, int to_mode, int start, int shift )
{
	this->m_TimeSamples.push_back ( { from_mode, to_mode, start, shift } );
}

void scbRelay::IdleTimer ( unsigned long long time )
{
	// Пустой вызов
}

void scbRelay::ChangeStatus ( const scbOutputStream& param )
{
	unsigned long mode [] = { 0l, 0l, 0l, 0l, 0l, 0l, 0l, 0l };

	for ( auto& conv : this->m_Convertations )
		if ( ( param.Mask [conv.InputElement] & conv.InputMask ) != 0 )
			mode [conv.OutputElement] |= conv.OutputMask;

	this->SetMode ( mode [0] ); // Используется только 32 бита результата
}
