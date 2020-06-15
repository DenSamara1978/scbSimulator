#include "scbRelay_NMSHM1_560.h"

scbRelay_NMSHM1_560::scbRelay_NMSHM1_560 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШМ1-560";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НММ1-560";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSHM1_560::~scbRelay_NMSHM1_560 ()
{

}

int scbRelay_NMSHM1_560::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
