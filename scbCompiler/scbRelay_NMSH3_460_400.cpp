#include "scbRelay_NMSH3_460_400.h"

scbRelay_NMSH3_460_400::scbRelay_NMSH3_460_400 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"НМШ3-460/400";
	this->m_IsPlugable = true;
	this->m_Case = scbDescription::DeviceCase::NMSH;
}

scbRelay_NMSH3_460_400::~scbRelay_NMSH3_460_400 ()
{

}

int scbRelay_NMSH3_460_400::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMSH3_460_400::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
