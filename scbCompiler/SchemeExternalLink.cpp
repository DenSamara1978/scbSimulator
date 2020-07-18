#include <algorithm>
#include "SchemeExternalLink.h"
#include "Description.h"

using std::min;

pair<int, int> SchemeExternalLink::setDescriptionTag(const wstring& name)
{
	auto desc = Description::getDescriptionIdByName(name);
	if (desc == -1)
		return pair {-1, -1}; // Тэг описания некорректный

	this->descriptionTag = desc;
	return pair {0, desc};
}

bool SchemeExternalLink::checkPresenceInConditionsAndDescription(int id) const
{
	for (const auto& group : this->conditions)
	{
		if (this->conditions.back().checkPresence(id))
			return true;
	}
	return (this->descriptionTag == id);
}
