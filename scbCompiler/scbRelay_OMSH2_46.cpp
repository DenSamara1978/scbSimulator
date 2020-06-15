#include "scbRelay_OMSH2_46.h"

scbRelay_OMSH2_46::scbRelay_OMSH2_46 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"ОМШ2-46";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"ОМ2-46";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_OMSH2_46::~scbRelay_OMSH2_46 ()
{

}

int scbRelay_OMSH2_46::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
