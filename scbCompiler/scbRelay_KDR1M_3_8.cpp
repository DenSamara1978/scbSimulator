#include "scbRelay_KDR1M_3_8.h"

scbRelay_KDR1M_3_8::scbRelay_KDR1M_3_8 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"КДР1М-3,8";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::KDR;
}

scbRelay_KDR1M_3_8::~scbRelay_KDR1M_3_8 ()
{

}

int scbRelay_KDR1M_3_8::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
