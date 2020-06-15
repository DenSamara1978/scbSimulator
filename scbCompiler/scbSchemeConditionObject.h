#pragma once

#include <string>
#include <vector>
#include "scbSchemeCondition.h"

using std::vector;
using std::wstring;

class scbSchemeConditionObject
{
protected:

	vector<scbSchemeCondition> m_Conditions;

public:

		// ��������� ����� ������ �������
	void AddNewConditionGroup ();
		// ��������� ����� ������� � ������� ������, ������� - ( 0 - ��� ��, 1 - ������ ���������, -1 - �������� ��������� ), ( ������������� ���������, ���� -1 )
	pair<int, int> AddCondition ( int conditionParam, const wstring& name );
		// ��������� ������� ���������� ����������� ������ �������
	bool CheckForEqualConditions () const;

	const vector<tuple<int, int, bool>>& GetLastConditions () const;
};

inline void scbSchemeConditionObject::AddNewConditionGroup ()
{
	this->m_Conditions.emplace_back ();
}

inline pair<int, int> scbSchemeConditionObject::AddCondition ( int conditionParam, const wstring& name )
{
	return this->m_Conditions.back ().AddCondition ( conditionParam, name );
}

inline const vector<tuple<int, int, bool>>& scbSchemeConditionObject::GetLastConditions () const
{
	return this->m_Conditions.back ().GetDescriptionTags ();
}
