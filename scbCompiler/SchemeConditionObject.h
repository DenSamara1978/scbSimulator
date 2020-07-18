#pragma once

#include <string>
#include <vector>
#include "SchemeCondition.h"

using std::vector;
using std::wstring;

class SchemeConditionObject
{
public:

	// ��������� ����� ������ �������
	void addNewConditionGroup();
	// ��������� ����� ������� � ������� ������, ������� - ( 0 - ��� ��, 1 - ������ ���������, -1 - �������� ��������� ), ( ������������� ���������, ���� -1 )
	pair<int, int> addCondition(int conditionParam, const wstring& name);
	// ��������� ������� ���������� ����������� ������ �������
	bool checkForEqualConditions() const;

	const vector<tuple<int, int, bool>>& getLastConditions() const;

protected:

	vector<SchemeCondition> conditions;

};

inline void SchemeConditionObject::addNewConditionGroup()
{
	this->conditions.emplace_back();
}

inline pair<int, int> SchemeConditionObject::addCondition(int conditionParam, const wstring& name)
{
	return this->conditions.back().addCondition(conditionParam, name);
}

inline const vector<tuple<int, int, bool>>& SchemeConditionObject::getLastConditions() const
{
	return this->conditions.back().getDescriptionTags();
}
