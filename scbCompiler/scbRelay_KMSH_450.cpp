#include "scbRelay_KMSH_450.h"

scbRelay_KMSH_450::scbRelay_KMSH_450 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"КМШ-450";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"КМ-450";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_KMSH_450::~scbRelay_KMSH_450 ()
{

}

int scbRelay_KMSH_450::SetJumper ( const wstring& jumper )
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

int scbRelay_KMSH_450::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
