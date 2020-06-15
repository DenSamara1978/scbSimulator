#pragma once

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::tuple;
using std::wstring;

class scbSchemeCondition
{
	vector<tuple<int, int, bool>> m_Conditions; // ��������, ���������, ���������

public:
		// ��������� ����� �������, ������� - ( 0 - ��� ��, 1 - ������ ���������, -1 - �������� ��������� ), ( ������������� ���������, ���� -1 )
	pair<int, int> AddCondition ( int conditionParam, const wstring& name );
		// ����������� ������� ��������� � ����������������� ��������
	bool CheckPresence ( int id ) const;
		// ��������� ���������� ��������
	bool CheckForEqual ( const scbSchemeCondition& cond ) const;

	const vector<tuple<int, int, bool>>& GetDescriptionTags () const;
};

inline const vector<tuple<int, int, bool>>& scbSchemeCondition::GetDescriptionTags () const
{
	return this->m_Conditions;
}
