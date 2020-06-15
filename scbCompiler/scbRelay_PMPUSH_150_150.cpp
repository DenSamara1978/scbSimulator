#include "scbRelay_PMPUSH_150_150.h"

scbRelay_PMPUSH_150_150::scbRelay_PMPUSH_150_150 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"ПМПУШ-150/150";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"ПМПУ-150/150";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_PMPUSH_150_150::~scbRelay_PMPUSH_150_150 ()
{

}

int scbRelay_PMPUSH_150_150::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"1-3" ) || ( jumper == L"3-1" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"3-2" ) || ( jumper == L"4-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_PMPUSH_150_150::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
