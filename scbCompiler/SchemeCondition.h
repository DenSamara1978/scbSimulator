#pragma once

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::tuple;
using std::wstring;

class SchemeCondition
{
public:
	// ��������� ����� �������, ������� - ( 0 - ��� ��, 1 - ������ ���������, -1 - �������� ��������� ), ( ������������� ���������, ���� -1 )
	pair<int, int> addCondition(int conditionParam, const wstring& name);
	// ����������� ������� ��������� � ����������������� ��������
	bool checkPresence(int id) const;
	// ��������� ���������� ��������
	bool checkForEqual(const SchemeCondition& cond) const;

	const vector<tuple<int, int, bool>>& getDescriptionTags() const;

private:
	vector<tuple<int, int, bool>> conditions; // ��������, ���������, ���������

};

inline const vector<tuple<int, int, bool>>& SchemeCondition::getDescriptionTags() const
{
	return this->conditions;
}
