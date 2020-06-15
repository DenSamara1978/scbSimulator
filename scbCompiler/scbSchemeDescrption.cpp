#include <algorithm>
#include <utility>
#include <stdexcept>
#include "scbDescription.h"
#include "scbSchemeDescription.h"

using std::get;

scbSchemeDescription::scbSchemeDescription () :
	m_Multiplicator ( -1 )
{
}

int scbSchemeDescription::SetMultiplicator ( const wstring& mult )
{
	size_t pos = 0;
	int res = 0;
	try
	{
		this->m_Multiplicator = std::stoi ( mult, &pos );
		if ( ( pos < mult.length ()) || ( this->m_Multiplicator <= 1 ) )
		{
			this->m_Multiplicator = 0;
			res = -1;
		}
	}
	catch ( std::invalid_argument )
	{
		this->m_Multiplicator = 0;
		res = -1;
	}
	if ( res == -1 )
		return -1;
	else
		return this->m_Multiplicator;
}

int scbSchemeDescription::AddNewPlacement ( int placement_id )
{
	const auto cbegin = this->m_Placements.cbegin ();
	const auto cend = this->m_Placements.cend ();
	const auto cres = find_if ( cbegin, cend, [placement_id] ( const auto& val ) { return val.first == placement_id; } );
	this->m_Placements.emplace_back ( placement_id, scbDescription::PlacementType::No );
	if ( cres != cend )
		return -1; // Обнаружено дублирование имени размещения
	else
		return 0;
}

pair<int, scbDescription::PlacementType> scbSchemeDescription::SetPlacementType ( const wstring& type )
{
	const auto pl_type = scbDescription::GetPlacementType ( type );
	if ( pl_type != scbDescription::PlacementType::No )
	{
		auto cbegin = this->m_Placements.cbegin ();
		auto cend = this->m_Placements.cend ();
		if ( cend != find_if ( cbegin, cend, [pl_type] ( const auto& val ) { return val.second == pl_type; } ) )
			return pair { 1, scbDescription::PlacementType::No }; // Обнаружено дублирование типа размещения
		else
		{
			this->m_Placements.back ().second = pl_type;
			return pair { 0, pl_type };
		}
	}
	else
		return pair { -1, scbDescription::PlacementType::No }; // Неверный тип размещения
}

scbDescription::PlacementType scbSchemeDescription::GetPlacementType ( int placement_id ) const
{
	const auto cbegin = this->m_Placements.cbegin ();
	const auto cend = this->m_Placements.cend ();
	const auto res = find_if ( cbegin, cend, [placement_id] ( const auto& val ) { return val.first == placement_id; } );
	if ( res != cend )
		return ( *res ).second;
	else
		return scbDescription::PlacementType::No;
}

bool scbSchemeDescription::CanExistAnotherPlacement ( int placement_id, scbDescription::PlacementType placement_type ) const
{
	for ( const auto& pl : this->m_Placements )
	{
		if (( pl.first == placement_id ) and ( pl.second != placement_type ))
			return false;
	}
	return true;
}

void scbSchemeDescription::AddNewDescriptionGroup ()
{
	this->m_Descriptions.emplace_back ();
}

int scbSchemeDescription::AddNewDescription ( const wstring& name )
{
	bool negative = false;
	wstring new_name;
	if ( name.find ( L"не " ) == 0 )
	{
		negative = true;
		new_name = name.substr ( 3 );
	}
	else
		new_name = name;

	auto desc = scbDescription::GetDescriptionIdByName ( new_name );
	if ( desc == -1 )
		return -1; // Тэг описания некорректный

	const auto group = this->m_Descriptions.size () - 1;
	const auto cbegin = this->m_Descriptions [group].cbegin ();
	const auto cend = this->m_Descriptions [group].cend ();
	if ( cend != find_if ( cbegin, cend, [desc] ( const auto& val ) { return val.first == desc;  } ))
		return 1; // Обнаружено повторение тэга в группе описаний

	this->m_Descriptions [group].push_back ( pair { desc, negative } );
	return 0;
}

bool scbSchemeDescription::CheckDescriptionGroups () const
{
	const auto groupCount = this->m_Descriptions.size ();
	size_t anyCount;
	const auto thisCount = this->m_Descriptions.back ().size ();
	int counter;
	for ( size_t group = 0; group < groupCount - 1; ++group )
	{
		anyCount = this->m_Descriptions [group].size ();
		counter = 0;
		for ( size_t anyDesc = 0; anyDesc < anyCount; ++anyDesc )
		{
			for ( size_t thisDesc = 0; thisDesc < thisCount; ++thisDesc )
			{
				if ( this->m_Descriptions [group] [anyDesc] == this->m_Descriptions [groupCount - 1] [thisDesc] )
					++counter;
			}
		}
		if ( counter == std::min ( anyCount, thisCount ) )
			return false;
	}
	return true;
}

bool scbSchemeDescription::CheckForTuning ( const vector<int>& tunings ) const
{
	const size_t groupCount = this->m_Descriptions.size ();
	for ( size_t group = 0; group < groupCount; ++group )
	{
		size_t pos_res = 0, neg_res = 0;
		const size_t descCount = this->m_Descriptions [group].size ();
		for ( const auto tuning : tunings )
		{
			for ( size_t desc = 0; desc < descCount; ++desc )
			{
				auto description = this->m_Descriptions [group] [desc];
				if ( ( description.first == tuning ) and ( description.second == true ) )
					pos_res++;
				if ( ( description.first == tuning ) and ( description.second == false ) )
					neg_res++;
			}
		}
		if ((( pos_res > 1 ) or ( neg_res == tunings.size ())) and ( tunings.size () > 1 ))
			return false;
	}
	return true;
}

bool scbSchemeDescription::CheckForExternalLinkDescription ( int tag ) const
{
	for ( const auto& descGroup : this->m_Descriptions )
	{
		for ( const auto& desc : descGroup )
			if ( desc.first == tag )
				return false;
	}
	return true;
}

bool scbSchemeDescription::CheckConditionsForAchievable ( const vector<tuple<int, int, bool>>& conditions ) const
{
	int counter, condParam, condTag;
	bool condNeg, mark;
	const auto param = this->m_Descriptor.ExtractParamTag ();
	for ( const auto& desc : this->m_Descriptions )
	{
		counter = 0;
		for ( const auto cond : conditions )
		{
			condParam = get<0> ( cond );
			condTag = get<1> ( cond );
			condNeg = get<2> ( cond );
			if ( ( condParam != param ) and ( condParam != -1 ) )
				++counter;
			else
			{
				mark = false;
				for ( const auto tag : desc )
				{
					if ( condTag == tag.first )
					{
						mark = true;
						if ( condNeg == tag.second )
							++counter;
						break;
					}
				}
				if ( !mark )
					++counter;
			}
		}
		if ( counter == conditions.size () )
			return true;
	}
	return false;
}
