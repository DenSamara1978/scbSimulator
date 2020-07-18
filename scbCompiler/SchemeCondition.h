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
	// Добавляет новое условие, возврат - ( 0 - все Ок, 1 - повтор описателя, -1 - неверный описатель ), ( идентификатор описателя, либо -1 )
	pair<int, int> addCondition(int conditionParam, const wstring& name);
	// Проверяется наличие описателя в непараметрических условиях
	bool checkPresence(int id) const;
	// Проверяет повторение описаний
	bool checkForEqual(const SchemeCondition& cond) const;

	const vector<tuple<int, int, bool>>& getDescriptionTags() const;

private:
	vector<tuple<int, int, bool>> conditions; // Параметр, Описатель, Отрицание

};

inline const vector<tuple<int, int, bool>>& SchemeCondition::getDescriptionTags() const
{
	return this->conditions;
}
