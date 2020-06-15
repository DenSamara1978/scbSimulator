#include <algorithm>
#include "scbDescription.h"
#include "scbSchemeTuning.h"

using std::min;
using std::get;

int scbSchemeTuning::AddNewDescription ( const wstring&  name )
{
	const auto desc = scbDescription::GetDescriptionIdByName ( name );
	if ( desc == -1 )
		return -1; // Тэг описания некорректный

	const auto cbegin = this->m_DescriptionTags.cbegin ();
	const auto cend = this->m_DescriptionTags.cend ();
	if ( cend != find ( cbegin, cend, desc ))
		return 1; // Обнаружено повторение тэга в группе описаний

	this->m_DescriptionTags.push_back ( desc );
	return 0;
}

bool scbSchemeTuning::CheckForExternalLinkDescription ( int tag ) const
{
	for ( const auto desc : this->m_DescriptionTags )
	{
		if ( desc == tag )
			return false;
	}
	return true;
}

bool scbSchemeTuning::IsIdentical ( const scbSchemeTuning& arg ) const
{
	if ( !( this->m_Descriptor.IsEqual ( arg.m_Descriptor ) ))
		return false;
	int counter = 0;
	for ( const auto& tag1 : this->m_DescriptionTags )
	{
		for ( const auto& tag2 : arg.m_DescriptionTags )
		{
			if ( tag1 == tag2 )
				++counter;
		}
	}
	return ( counter == min ( this->m_DescriptionTags.size (), arg.m_DescriptionTags.size ()) );
}

bool scbSchemeTuning::CheckConditionsForAchievable ( const vector<tuple<int, int, bool>>& conditions ) const
{
	int pos_count = 0, neg_count = 0;
	const auto param = this->m_Descriptor.ExtractParamTag ();
	for ( const auto tag : this->m_DescriptionTags )
	{
		for ( const auto cond : conditions )
		{
			if ( ( get<0> ( cond ) == param ) and ( get<1> ( cond ) == tag ) )
			{
				if ( get<2> ( cond ) )
					++neg_count;
				else
					++pos_count;
			}
		}
	}
	return ( ( pos_count <= 1 ) and ( ( neg_count != min ( conditions.size (), this->m_DescriptionTags.size ()) ) or ( neg_count == 1 ) ) );
}