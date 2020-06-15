#include "scbRelay_ANVSH2_2400.h"

scbRelay_ANVSH2_2400::scbRelay_ANVSH2_2400 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"АНВШ2-2400";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_ANVSH2_2400::~scbRelay_ANVSH2_2400 ()
{

}

int scbRelay_ANVSH2_2400::SetJumper ( const wstring& jumper )
{
	if ((jumper == L"21-41") || (jumper == L"41-21"))
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"21-42" ) || ( jumper == L"42-21" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"41-42" ) || ( jumper == L"42-41" ) )
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"41-61") || (jumper == L"61-41"))
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"61-62" ) || ( jumper == L"62-61" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"61-81" ) || ( jumper == L"81-61" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"62-81" ) || ( jumper == L"81-62" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_ANVSH2_2400::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
