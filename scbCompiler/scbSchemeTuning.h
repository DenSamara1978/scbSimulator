#pragma once

#include <vector>
#include "scbComplexName.h"

using std::vector;
using std::pair;
using std::tuple;

class scbSchemeTuning
{
	scbComplexName m_Descriptor;
	vector<int> m_DescriptionTags;

public:
	scbComplexName& GetDescriptor ();
	int AddNewDescription ( const wstring&  name );

	pair<int, const vector<int>> GetDescriptionTags () const;
	bool CheckForExternalLinkDescription ( int tag ) const;

	bool IsIdentical ( const scbSchemeTuning& arg ) const;
	bool CheckConditionsForAchievable ( const vector<tuple<int, int, bool>>& conditions ) const;
};

inline scbComplexName& scbSchemeTuning::GetDescriptor ()
{
	return this->m_Descriptor;
}

inline pair<int, const vector<int>> scbSchemeTuning::GetDescriptionTags () const
{
	return pair { this->m_Descriptor.ExtractParamTag (), this->m_DescriptionTags };
}
