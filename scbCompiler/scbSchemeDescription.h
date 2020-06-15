#pragma once

#include <vector>
#include <string>
#include <utility>
#include "scbComplexName.h"

using std::vector;
using std::wstring;
using std::pair;
using std::tuple;

class scbSchemeDescription
{
	scbComplexName m_Descriptor;
	int m_Multiplicator; // -1 - Одноэкземплятрный, 0 - ошибка формата, >0 - количество экземпляров

	vector<pair<int, scbDescription::PlacementType>> m_Placements;

	vector<vector<pair<int, bool>>> m_Descriptions;

public:
	scbSchemeDescription ();

	scbComplexName& GetDescriptor ();
	const scbComplexName& GetDescriptor () const;

	int SetMultiplicator ( const wstring& mult );

	int AddNewPlacement ( int placement_id );
	pair<int, scbDescription::PlacementType> SetPlacementType ( const wstring& type );
	bool CanExistAnotherPlacement ( int placement_id, scbDescription::PlacementType placement_type ) const;

	scbDescription::PlacementType GetPlacementType ( int placement_id ) const;

	void AddNewDescriptionGroup ();

	int AddNewDescription ( const wstring&  name );
	bool CheckDescriptionGroups () const;
	bool CheckForTuning ( const vector<int>& tunings ) const;
	bool CheckForExternalLinkDescription ( int tag ) const;
	bool CheckConditionsForAchievable ( const vector<tuple<int, int, bool>>& conditions ) const;
};

inline scbComplexName& scbSchemeDescription::GetDescriptor ()
{
	return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeDescription::GetDescriptor () const
{
	return this->m_Descriptor;
}
