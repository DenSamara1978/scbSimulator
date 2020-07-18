#pragma once

#include <vector>
#include <string>
#include <utility>
#include "ComplexName.h"

using std::vector;
using std::wstring;
using std::pair;
using std::tuple;

class SchemeDescription
{
public:
	SchemeDescription();

	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;

	int setMultiplicator(const wstring& mult);

	int addNewPlacement(int placement_id);
	pair<int, Description::PlacementType> setPlacementType(const wstring& type);
	bool canExistAnotherPlacement(int placement_id, Description::PlacementType placementType) const;

	Description::PlacementType getPlacementType(int placementId) const;

	void addNewDescriptionGroup();

	int addNewDescription(const wstring& name);
	bool checkDescriptionGroups() const;
	bool checkForTuning(const vector<int>& tunings) const;
	bool checkForExternalLinkDescription(int tag) const;
	bool checkConditionsForAchievable(const vector<tuple<int, int, bool>>& conditions) const;

private:
	ComplexName descriptor;
	int multiplicator; // -1 - Одноэкземплятрный, 0 - ошибка формата, >0 - количество экземпляров

	vector<pair<int, Description::PlacementType>> placements;

	vector<vector<pair<int, bool>>> descriptions;

};

inline ComplexName& SchemeDescription::getDescriptor()
{
	return this->descriptor;
}

inline const ComplexName& SchemeDescription::getDescriptor() const
{
	return this->descriptor;
}
