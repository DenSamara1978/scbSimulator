#include <algorithm>
#include "scbSchemeCondition.h"
#include "scbDescription.h"

using std::get;

pair<int, int> scbSchemeCondition::AddCondition ( int conditionParam, const wstring& name )
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

	const auto desc = scbDescription::GetDescriptionIdByName ( new_name );
	if ( desc == -1 )
		return pair { -1, -1 }; // Тэг описания некорректный

	const auto cbegin = this->m_Conditions.cbegin ();
	const auto cend = this->m_Conditions.cend ();
	if ( cend != find_if ( cbegin, cend, [conditionParam, desc] ( const auto& val ) { return (( get<1> ( val ) == desc ) and ( get<0> ( val ) == conditionParam )); } ))
		return pair { 1, desc }; // Обнаружено повторение тэга в группе описаний

	this->m_Conditions.push_back ( tuple { conditionParam, desc, negative } );
	return pair { 0, desc };
}

bool scbSchemeCondition::CheckPresence ( int id ) const
{
	const auto cbegin = this->m_Conditions.cbegin ();
	const auto cend = this->m_Conditions.cend ();
	return ( cend != find_if ( cbegin, cend, [id] ( const auto& val ) { return ( ( get<1> ( val ) == id ) and ( get<0> ( val ) == -1 ) ); } ) );
}

bool scbSchemeCondition::CheckForEqual ( const scbSchemeCondition& cond ) const
{
	if ( this->m_Conditions.size () != cond.m_Conditions.size () )
		return false;
	int counter = 0;
	for ( const auto& point1 : this->m_Conditions )
	{
		for ( const auto& point2 : cond.m_Conditions )
			if ( point1 == point2 )
				++counter;
	}
	return ( counter == this->m_Conditions.size () );
}
