#pragma once

#include <string>
#include <vector>
#include "SchemeCondition.h"

using std::vector;
using std::wstring;

class SchemeConditionObject
{
public:

	// Добавляет новую группу условий
	void addNewConditionGroup();
	// Добавляет новое условие в текущую группу, возврат - ( 0 - все Ок, 1 - повтор описателя, -1 - неверный описатель ), ( идентификатор описателя, либо -1 )
	pair<int, int> addCondition(int conditionParam, const wstring& name);
	// Проверяет наличие повторного идентичного набора условий
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
