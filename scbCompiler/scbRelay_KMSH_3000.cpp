#include "scbRelay_KMSH_3000.h"

scbRelay_KMSH_3000::scbRelay_KMSH_3000 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"КМШ-3000";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"КМ-3000";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_KMSH_3000::~scbRelay_KMSH_3000 ()
{

}

int scbRelay_KMSH_3000::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_KMSH_3000::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
