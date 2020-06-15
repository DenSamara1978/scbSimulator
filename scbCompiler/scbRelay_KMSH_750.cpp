#include "scbRelay_KMSH_750.h"

scbRelay_KMSH_750::scbRelay_KMSH_750 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"КМШ-750";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_KMSH_750::~scbRelay_KMSH_750 ()
{

}

int scbRelay_KMSH_750::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"1-2" ) || ( jumper == L"2-1" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"3-4" ) || ( jumper == L"4-3" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_KMSH_750::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
