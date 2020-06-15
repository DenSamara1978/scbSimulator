#include "scbComplexName.h"
#include "scbDescription.h"
#include "scbManager.h"

scbComplexName::scbComplexName () :
	m_FirstTagId ( -1 ),
	m_SecondTagId ( -1 ),
	m_ThirdTagId ( -1 ),
	m_Type ( ComplexNameType::Empty )
{
}

void scbComplexName::Clear ()
{
	this->m_FirstTagId = -1;
	this->m_SecondTagId = -1;
	this->m_ThirdTagId = -1;
	this->m_FourthTagName.clear ();
	this->m_Type = ComplexNameType::Empty;
}

int scbComplexName::AddTagName ( const wstring& name )
{
	int id;
	if ( this->m_FirstTagId == -1 )
	{
		this->m_Type = ComplexNameType::Incorrect;
		if ( ( id = scbDescription::GetTagIdByName ( name ) ) == -1 )
			return 1;
		else
		{
			this->m_FirstTagId = id;
			return 0;
		}
	}
	else if ( this->m_SecondTagId == -1 )
	{
		this->m_Type = ComplexNameType::Incorrect;
		if ( ( id = scbDescription::GetTagIdByName ( name ) ) == -1 )
			return 1;
		else
		{
			this->m_SecondTagId = id;
			return 0;
		}
	}
	else if ( this->m_ThirdTagId == -1 )
	{
		if ( ( id = scbDescription::GetTagIdByName ( name ) ) == -1 )
		{
			this->m_Type = ComplexNameType::Incorrect;
			return 1;
		}
		else
		{
			this->m_Type = ComplexNameType::Short;
			this->m_ThirdTagId = id;
			return 0;
		}
	}
	else if ( this->m_FourthTagName.empty () )
	{
		this->m_FourthTagName = name;
		this->m_Type = ComplexNameType::Full;
		return 0;
	}
	else
		return -1;
}

int scbComplexName::AddGroupTagName ( const wstring& name )
{
	if ( ( this->m_FirstTagId == -1 ) || ( this->m_SecondTagId == -1 ) )
		return -1;
	else if ( this->m_ThirdTagId == -1 )
	{
		this->m_ThirdTagId = scbDescription::GetGroupTag ( name );
		if ( this->m_ThirdTagId == -1 )
			return 1; // Неверное групповое имя
		else
			this->m_ThirdTagId += 200'000;
		this->m_Type = ComplexNameType::Short;
		return 0;
	}
	else
		return -1;
}

int scbComplexName::AddParamTagId ( int id )
{
	if ( this->m_FirstTagId == -1 )
		return -1;
	else if ( this->m_SecondTagId == -1 )
	{
		this->m_SecondTagId = id;
		this->m_Type = ComplexNameType::Incorrect;
		return 0;
	}
	else if ( this->m_ThirdTagId == -1 )
	{
		this->m_ThirdTagId = id;
		this->m_Type = ComplexNameType::Short;
		return 0;
	}
	else
		return -1;
}

int scbComplexName::ExtractParamTag () const
{
	if ( ( this->m_SecondTagId >= 0 ) and ( this->m_SecondTagId >= scbManager::ParameterNameShift ) )
		return this->m_SecondTagId - scbManager::ParameterNameShift;
	else if ( ( this->m_ThirdTagId >= 0 ) and ( this->m_ThirdTagId >= scbManager::ParameterNameShift ) )
		return this->m_ThirdTagId - scbManager::ParameterNameShift;
	else return -1;
}

bool scbComplexName::ReplaceFourthTag ( const wstring& name )
{
    if (( this->m_Type == ComplexNameType::Full ) or ( this->m_Type == ComplexNameType::Short ))
    {
        this->m_FourthTagName = name;
        this->m_Type = ComplexNameType::Full;
        return true;
    }
    return false;
}

bool scbComplexName::IsEqual ( const scbComplexName& name ) const
{
	return (( ( this->m_FirstTagId == name.m_FirstTagId ) and ( this->m_SecondTagId == name.m_SecondTagId ) and ( this->m_ThirdTagId == name.m_ThirdTagId ) and
		( this->m_Type == ComplexNameType::Short ) and ( name.m_Type == ComplexNameType::Short ) ) or
		(( this->m_Type == ComplexNameType::Empty ) and ( name.m_Type == ComplexNameType::Empty )));
}

bool scbComplexName::IsInclude ( const scbComplexName& name ) const
{
    return  ( ( this->m_FirstTagId == name.m_FirstTagId ) and ( this->m_SecondTagId == name.m_SecondTagId ) and ( this->m_ThirdTagId == name.m_ThirdTagId ) and
        ( this->m_Type == ComplexNameType::Short ) and ( name.m_Type == ComplexNameType::Full ) );
}

bool scbComplexName::IsFullyEqual ( const scbComplexName& name ) const
{
    return ( ( this->m_FirstTagId == name.m_FirstTagId ) and ( this->m_SecondTagId == name.m_SecondTagId ) and 
        ( this->m_ThirdTagId == name.m_ThirdTagId ) and ( this->m_FourthTagName == name.m_FourthTagName ) and
        ( this->m_Type == ComplexNameType::Full ) and ( name.m_Type == ComplexNameType::Full ) );
}
