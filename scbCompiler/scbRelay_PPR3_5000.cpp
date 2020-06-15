#include "scbRelay_PPR3_5000.h"

scbRelay_PPR3_5000::scbRelay_PPR3_5000 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"ППР3-5000";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::NR;
}

scbRelay_PPR3_5000::~scbRelay_PPR3_5000 ()
{

}

int scbRelay_PPR3_5000::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
