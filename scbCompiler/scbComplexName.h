#pragma once

#include <string>
#include <vector>

using std::wstring;
using std::vector;

class scbComplexName
{
public:
	enum class ComplexNameType { Empty, Incorrect, Short, Full };

private:

	int m_FirstTagId;
	int m_SecondTagId;
	int m_ThirdTagId;
	wstring m_FourthTagName;

	ComplexNameType m_Type;

public:
	scbComplexName ();
	void Clear ();

	int AddTagName ( const wstring& name );
	int AddParamTagId ( int id );
	int AddGroupTagName ( const wstring& name );

	void SetSecondTag ( int tag );
	int ExtractParamTag () const;
    bool ReplaceFourthTag ( const wstring& name );

	ComplexNameType GetType () const;
	bool IsValid () const;
    bool IsGroupDescriptor () const;
	bool IsEqualForDescription ( const scbComplexName& name ) const;
	bool IsEqual ( const scbComplexName& name ) const;
    bool IsInclude ( const scbComplexName& name ) const;
    bool IsFullyEqual ( const scbComplexName& name ) const;
};

inline scbComplexName::ComplexNameType scbComplexName::GetType () const
{
	return this->m_Type;
}

inline bool scbComplexName::IsValid () const
{
	return (( this->m_Type != ComplexNameType::Incorrect ) and ( this->m_Type != ComplexNameType::Empty ));
}

inline bool scbComplexName::IsEqualForDescription ( const scbComplexName& name ) const
{
	return ( ( this->m_FirstTagId == name.m_FirstTagId ) and ( this->m_SecondTagId == name.m_SecondTagId ) and
		( this->m_Type == ComplexNameType::Short ) and 
        (( name.m_Type == ComplexNameType::Short ) or ( name.m_Type == ComplexNameType::Full )) );
}

inline bool scbComplexName::IsGroupDescriptor () const
{
    return ( this->m_ThirdTagId >= 200'000 );
}

inline void scbComplexName::SetSecondTag ( int tag )
{
	this->m_SecondTagId = tag;
}
