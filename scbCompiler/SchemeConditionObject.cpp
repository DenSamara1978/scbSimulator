#include "SchemeConditionObject.h"

bool SchemeConditionObject::checkForEqualConditions() const
{
	const auto groupCount = this->conditions.size() - 1;
	for (size_t index = 0; index < groupCount; ++index)
	{
		if (this->conditions[index].checkForEqual(this->conditions.back()))
			return true;
	}
	return false;
}
