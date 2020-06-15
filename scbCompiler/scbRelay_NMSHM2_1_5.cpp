#include "scbRelay_NMSHM2_1_5.h"

scbRelay_NMSHM2_1_5::scbRelay_NMSHM2_1_5 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШМ2-1,5";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НММ2-1,5";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSHM2_1_5::~scbRelay_NMSHM2_1_5 ()
{

}

int scbRelay_NMSHM2_1_5::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
