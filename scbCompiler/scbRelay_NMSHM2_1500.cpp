#include "scbRelay_NMSHM2_1500.h"

scbRelay_NMSHM2_1500::scbRelay_NMSHM2_1500 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"НМШМ2-1500";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_NMSHM2_1500::~scbRelay_NMSHM2_1500 ()
{

}

int scbRelay_NMSHM2_1500::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
