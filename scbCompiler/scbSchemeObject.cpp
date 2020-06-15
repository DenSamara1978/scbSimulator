#include "scbSchemeObject.h"

scbSchemeObject::scbSchemeObject ( const wstring& name ) :
	m_Name ( name ),
	m_Block ( -1 ),
	m_Placement ( -1 ),
	m_Case ( scbDescription::DeviceCase::No )
{

}

scbSchemeObject::~scbSchemeObject ()
{

}

int scbSchemeObject::SetDescriptor ( const scbComplexName& descriptor )
{
    return -1;
}

int scbSchemeObject::SetBlock ( int id )
{
	return -1;
}

int scbSchemeObject::SetLocation ( const wstring& location )
{
	return -1;
}

int scbSchemeObject::SetPlacement ( int id, scbDescription::PlacementType pl_type )
{
	return -1;
}

int scbSchemeObject::SetJumper ( const wstring& jumper )
{
	return -1;
}

int scbSchemeObject::SetOrder ( int order )
{
    return -1;
}

int scbSchemeObject::SetCable ( const wstring& cable )
{
    return -1;
}

int scbSchemeObject::SetContact ( const wstring& contact )
{
    return -1;
}

int scbSchemeObject::SetCount ( int count )
{
    return -1;
}

int scbSchemeObject::SetNominal ( const wstring& nominal )
{
    return -1;
}

int scbSchemeObject::SetUnitOfNominal ( const wstring& unit )
{
    return -1;
}

int scbSchemeObject::SetPowerClass ( const wstring& power_class )
{
    return -1;
}

int scbSchemeObject::SetRequirement ( int req )
{
    return -1;
}

int scbSchemeObject::SetRequirementFrom ( int from )
{
	return -1;
}

int scbSchemeObject::SetRequirementTo ( int to )
{
	return -1;
}

int scbSchemeObject::DefaultSettingStatus ()
{
	return -1;
}

int scbSchemeObject::SetTypeName ( const wstring& name )
{
	return -1;
}

const wstring scbSchemeObject::GetTypeName () const
{
	return L"";
}

bool scbSchemeObject::CheckLocation ( int block, int placement, const wstring& locaation ) const
{
	return true;
}
