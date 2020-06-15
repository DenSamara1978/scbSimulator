#include <algorithm>
#include "scbSchemeExternalLink.h"
#include "scbDescription.h"

using std::min;

pair<int, int> scbSchemeExternalLink::SetDescriptionTag ( const wstring& name )
{
	auto desc = scbDescription::GetDescriptionIdByName ( name );
	if ( desc == -1 )
		return pair { -1, -1 }; // Тэг описания некорректный

	this->m_DescriptionTag = desc;
	return pair { 0, desc };
}

bool scbSchemeExternalLink::CheckPresenceInConditionsAndDescription ( int id ) const
{
	for ( const auto& group : this->m_Conditions )
	{
		if ( this->m_Conditions.back ().CheckPresence ( id ) )
			return true;
	}
	return ( this->m_DescriptionTag == id );
}
