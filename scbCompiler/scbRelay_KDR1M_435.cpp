#include "scbRelay_KDR1M_435.h"

scbRelay_KDR1M_435::scbRelay_KDR1M_435 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"КДР1М-435";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::KDR;
}

scbRelay_KDR1M_435::~scbRelay_KDR1M_435 ()
{

}

int scbRelay_KDR1M_435::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
