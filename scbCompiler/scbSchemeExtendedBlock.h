#pragma once

#include "scbSchemeConditionObject.h"

class scbSchemeExtendedBlock : public scbSchemeConditionObject
{
	int m_DefaultCount;
	wstring m_Name;
	vector<int> m_ComplectCountInCondition;

public:
	scbSchemeExtendedBlock ();
	void SetName ( const wstring& name );
	const wstring GetName () const;
	int SetDefaultCount ( const wstring& name );
	int AddNewConditionCount ( const wstring& name );
};

inline scbSchemeExtendedBlock::scbSchemeExtendedBlock () :
	m_DefaultCount ( -1 )
{
}

inline void scbSchemeExtendedBlock::SetName ( const wstring& name )
{
	this->m_Name = name;
}

inline const wstring scbSchemeExtendedBlock::GetName () const
{
	return this->m_Name;
}
