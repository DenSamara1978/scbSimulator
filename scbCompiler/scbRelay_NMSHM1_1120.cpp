#include "scbRelay_NMSHM1_1120.h"

scbRelay_NMSHM1_1120::scbRelay_NMSHM1_1120 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШМ1-1120";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НММ1-1120";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSHM1_1120::~scbRelay_NMSHM1_1120 ()
{

}

int scbRelay_NMSHM1_1120::SetJumper ( const wstring& jumper )
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

int scbRelay_NMSHM1_1120::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
