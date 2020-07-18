#include <algorithm>
#include "Description.h"
#include "SchemeTuning.h"

using std::min;
using std::get;

int SchemeTuning::addNewDescription(const wstring& name)
{
	const auto desc = Description::getDescriptionIdByName(name);
	if (desc == -1)
		return -1; // Тэг описания некорректный

	const auto cbegin = this->descriptionTags.cbegin();
	const auto cend = this->descriptionTags.cend();
	if (cend != find(cbegin, cend, desc))
		return 1; // Обнаружено повторение тэга в группе описаний

	this->descriptionTags.push_back(desc);
	return 0;
}

bool SchemeTuning::checkForExternalLinkDescription(int tag) const
{
	for (const auto desc : this->descriptionTags)
	{
		if (desc == tag)
			return false;
	}
	return true;
}

bool SchemeTuning::isIdentical(const SchemeTuning& arg) const
{
	if (!(this->descriptor.isEqual(arg.descriptor)))
		return false;
	int counter = 0;
	for (const auto& tag1 : this->descriptionTags)
	{
		for (const auto& tag2 : arg.descriptionTags)
		{
			if (tag1 == tag2)
				++counter;
		}
	}
	return (counter == min(this->descriptionTags.size(), arg.descriptionTags.size()));
}

bool SchemeTuning::checkConditionsForAchievable(const vector<tuple<int, int, bool>>& conditions) const
{
	int pos_count = 0, neg_count = 0;
	const auto param = this->descriptor.extractParamTag();
	for (const auto tag : this->descriptionTags)
	{
		for (const auto cond : conditions)
		{
			if ((get<0>(cond) == param) and (get<1>(cond) == tag))
			{
				if (get<2>(cond))
					++neg_count;
				else
					++pos_count;
			}
		}
	}
	return ((pos_count <= 1) and ((neg_count != min(conditions.size(), this->descriptionTags.size())) or (neg_count == 1)));
}