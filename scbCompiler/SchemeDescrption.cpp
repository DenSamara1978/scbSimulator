#include <algorithm>
#include <utility>
#include <stdexcept>
#include "Description.h"
#include "SchemeDescription.h"

using std::get;

SchemeDescription::SchemeDescription() :
	multiplicator(-1)
{
}

int SchemeDescription::setMultiplicator(const wstring& mult)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		this->multiplicator = std::stoi(mult, &pos);
		if ((pos < mult.length()) or (this->multiplicator <= 1))
		{
			this->multiplicator = 0;
			res = -1;
		}
	}
	catch (std::invalid_argument)
	{
		this->multiplicator = 0;
		res = -1;
	}
	if (res == -1)
		return -1;
	else
		return this->multiplicator;
}

int SchemeDescription::addNewPlacement(int placement_id)
{
	const auto cbegin = this->placements.cbegin();
	const auto cend = this->placements.cend();
	const auto cres = find_if(cbegin, cend, [placement_id] (const auto& val) { return val.first == placement_id; });
	this->placements.emplace_back(placement_id, Description::PlacementType::No);
	if (cres != cend)
		return -1; // Обнаружено дублирование имени размещения
	else
		return 0;
}

pair<int, Description::PlacementType> SchemeDescription::setPlacementType(const wstring& type)
{
	const auto pl_type = Description::getPlacementType(type);
	if (pl_type != Description::PlacementType::No)
	{
		auto cbegin = this->placements.cbegin();
		auto cend = this->placements.cend();
		if (cend != find_if(cbegin, cend, [pl_type] (const auto& val) { return val.second == pl_type; }))
			return pair {1, Description::PlacementType::No}; // Обнаружено дублирование типа размещения
		else
		{
			this->placements.back().second = pl_type;
			return pair {0, pl_type};
		}
	}
	else
		return pair {-1, Description::PlacementType::No}; // Неверный тип размещения
}

Description::PlacementType SchemeDescription::getPlacementType(int placement_id) const
{
	const auto cbegin = this->placements.cbegin();
	const auto cend = this->placements.cend();
	const auto res = find_if(cbegin, cend, [placement_id] (const auto& val) { return val.first == placement_id; });
	if (res != cend)
		return (*res).second;
	else
		return Description::PlacementType::No;
}

bool SchemeDescription::canExistAnotherPlacement(int placement_id, Description::PlacementType placement_type) const
{
	for (const auto& pl : this->placements)
	{
		if ((pl.first == placement_id) and (pl.second != placement_type))
			return false;
	}
	return true;
}

void SchemeDescription::addNewDescriptionGroup()
{
	this->descriptions.emplace_back();
}

int SchemeDescription::addNewDescription(const wstring& name)
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

	auto desc = Description::getDescriptionIdByName(new_name);
	if (desc == -1)
		return -1; // Тэг описания некорректный

	const auto group = this->descriptions.size() - 1;
	const auto cbegin = this->descriptions[group].cbegin();
	const auto cend = this->descriptions[group].cend();
	if (cend != find_if(cbegin, cend, [desc] (const auto& val) { return val.first == desc; }))
		return 1; // Обнаружено повторение тэга в группе описаний

	this->descriptions[group].push_back(pair {desc, negative});
	return 0;
}

bool SchemeDescription::checkDescriptionGroups() const
{
	const auto groupCount = this->descriptions.size();
	size_t anyCount;
	const auto thisCount = this->descriptions.back().size();
	int counter;
	for (size_t group = 0; group < groupCount - 1; ++group)
	{
		anyCount = this->descriptions[group].size();
		counter = 0;
		for (size_t anyDesc = 0; anyDesc < anyCount; ++anyDesc)
		{
			for (size_t thisDesc = 0; thisDesc < thisCount; ++thisDesc)
			{
				if (this->descriptions[group][anyDesc] == this->descriptions[groupCount - 1][thisDesc])
					++counter;
			}
		}
		if (counter == std::min(anyCount, thisCount))
			return false;
	}
	return true;
}

bool SchemeDescription::checkForTuning(const vector<int>& tunings) const
{
	const size_t groupCount = this->descriptions.size();
	for (size_t group = 0; group < groupCount; ++group)
	{
		size_t pos_res = 0, neg_res = 0;
		const size_t descCount = this->descriptions[group].size();
		for (const auto tuning : tunings)
		{
			for (size_t desc = 0; desc < descCount; ++desc)
			{
				auto description = this->descriptions[group][desc];
				if ((description.first == tuning) and (description.second == true))
					pos_res++;
				if ((description.first == tuning) and (description.second == false))
					neg_res++;
			}
		}
		if (((pos_res > 1) or (neg_res == tunings.size())) and (tunings.size() > 1))
			return false;
	}
	return true;
}

bool SchemeDescription::checkForExternalLinkDescription(int tag) const
{
	for (const auto& descGroup : this->descriptions)
	{
		for (const auto& desc : descGroup)
			if (desc.first == tag)
				return false;
	}
	return true;
}

bool SchemeDescription::checkConditionsForAchievable(const vector<tuple<int, int, bool>>& conditions) const
{
	int counter, condParam, condTag;
	bool condNeg, mark;
	const auto param = this->descriptor.extractParamTag();
	for (const auto& desc : this->descriptions)
	{
		counter = 0;
		for (const auto cond : conditions)
		{
			condParam = get<0>(cond);
			condTag = get<1>(cond);
			condNeg = get<2>(cond);
			if ((condParam != param) and (condParam != -1))
				++counter;
			else
			{
				mark = false;
				for (const auto tag : desc)
				{
					if (condTag == tag.first)
					{
						mark = true;
						if (condNeg == tag.second)
							++counter;
						break;
					}
				}
				if (!mark)
					++counter;
			}
		}
		if (counter == conditions.size())
			return true;
	}
	return false;
}
