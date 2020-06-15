#include "scbSchemeConditionObject.h"

bool scbSchemeConditionObject::CheckForEqualConditions () const
{
	const auto groupCount = this->m_Conditions.size () - 1;
	for ( size_t index = 0; index < groupCount; ++index )
	{
		if ( this->m_Conditions [index].CheckForEqual ( this->m_Conditions.back () ) )
			return true;
	}
	return false;
}
