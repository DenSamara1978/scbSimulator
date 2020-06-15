#include "scbRelay_NMPSH3M_02_250.h"

scbRelay_NMPSH3M_02_250::scbRelay_NMPSH3M_02_250 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМПШ3М-0,2/250";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НМП3М-0,2/250";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMPSH3M_02_250::~scbRelay_NMPSH3M_02_250 ()
{

}

int scbRelay_NMPSH3M_02_250::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMPSH3M_02_250::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
