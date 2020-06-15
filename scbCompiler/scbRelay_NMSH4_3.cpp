#include "scbRelay_NMSH4_3.h"

scbRelay_NMSH4_3::scbRelay_NMSH4_3 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШ4-3";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НМ4-3";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSH4_3::~scbRelay_NMSH4_3 ()
{

}

int scbRelay_NMSH4_3::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMSH4_3::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
