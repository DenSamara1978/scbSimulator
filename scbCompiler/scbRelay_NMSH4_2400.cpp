#include "scbRelay_NMSH4_2400.h"

scbRelay_NMSH4_2400::scbRelay_NMSH4_2400 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШ4-2400";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НМ4-2400";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSH4_2400::~scbRelay_NMSH4_2400 ()
{

}

int scbRelay_NMSH4_2400::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"1-3" ) || ( jumper == L"3-1" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"2-4" ) || ( jumper == L"4-2" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"1-2" ) || ( jumper == L"2-1" ) )
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

int scbRelay_NMSH4_2400::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
