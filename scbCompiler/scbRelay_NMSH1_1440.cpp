#include "scbRelay_NMSH1_1440.h"

scbRelay_NMSH1_1440::scbRelay_NMSH1_1440 ( const wstring& name, bool plugable ) :
    m_RequirementFrom ( -1 ),
    m_RequirementTo ( -1 ),
    m_RequirementId ( -1 ),
    scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"НМШ1-1440";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"НМ1-1440";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSH1_1440::~scbRelay_NMSH1_1440 ()
{

}

int scbRelay_NMSH1_1440::SetJumper ( const wstring& jumper )
{
	if ( ( jumper == L"1-3" ) || ( jumper == L"3-1" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"2-4" ) || ( jumper == L"4-2" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"1-2" ) || ( jumper == L"2-1" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"3-4" ) || ( jumper == L"4-3" ) )
	{
		// TODO 
		return 0;
	}
	else if ( ( jumper == L"2-3" ) || ( jumper == L"3-2" ) )
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int scbRelay_NMSH1_1440::SetRequirement ( int req )
{
    this->m_RequirementId = req;
    return 0;
}

int scbRelay_NMSH1_1440::SetRequirementFrom ( int from )
{
    this->m_RequirementFrom = from;
    return 0;
}

int scbRelay_NMSH1_1440::SetRequirementTo ( int to )
{
    this->m_RequirementTo = to;
    return ( this->m_RequirementTo - this->m_RequirementFrom >= 0 ) ? 0 : 1;
}

int scbRelay_NMSH1_1440::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
