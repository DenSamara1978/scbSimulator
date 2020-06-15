#include "scbRelay_NMPSH_900.h"

scbRelay_NMPSH_900::scbRelay_NMPSH_900 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"НМПШ-900";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_NMPSH_900::~scbRelay_NMPSH_900 ()
{

}

int scbRelay_NMPSH_900::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMPSH_900::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
