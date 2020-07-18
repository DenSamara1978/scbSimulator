#include <algorithm>
#include "SchemeCondition.h"
#include "Description.h"

using std::get;

pair<int, int> SchemeCondition::addCondition(int conditionParam, const wstring& name)
{
	bool negative = false;
	wstring new_name;
	if (name.find(L"не ") == 0)
	{
		negative = true;
		new_name = name.substr(3);
	}
	else
		new_name = name;

	const auto desc = Description::getDescriptionIdByName(new_name);
	if (desc == -1)
		return pair {-1, -1}; // Тэг описания некорректный

	const auto cbegin = this->conditions.cbegin();
	const auto cend = this->conditions.cend();
	if (cend != find_if(cbegin, cend, [conditionParam, desc] (const auto& val) { return ((get<1>(val) == desc) and (get<0>(val) == conditionParam)); }))
		return pair {1, desc}; // Обнаружено повторение тэга в группе описаний

	this->conditions.push_back(tuple {conditionParam, desc, negative});
	return pair {0, desc};
}

bool SchemeCondition::checkPresence(int id) const
{
	const auto cbegin = this->conditions.cbegin();
	const auto cend = this->conditions.cend();
	return (cend != find_if(cbegin, cend, [id] (const auto& val) { return ((get<1>(val) == id) and (get<0>(val) == -1)); }));
}

bool SchemeCondition::checkForEqual(const SchemeCondition& cond) const
{
	if (this->conditions.size() != cond.conditions.size())
		return false;
	int counter = 0;
	for (const auto& point1 : this->conditions)
	{
		for (const auto& point2 : cond.conditions)
			if (point1 == point2)
				++counter;
	}
	return (counter == this->conditions.size());
}
