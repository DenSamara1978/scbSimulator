#include "scbRelay_NMSHM2_3000.h"

scbRelay_NMSHM2_3000::scbRelay_NMSHM2_3000 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"НМШМ2-3000";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_NMSHM2_3000::~scbRelay_NMSHM2_3000 ()
{

}

int scbRelay_NMSHM2_3000::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMSHM2_3000::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
