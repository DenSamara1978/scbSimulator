#pragma once

#include <vector>
#include "ComplexName.h"

using std::vector;
using std::pair;
using std::tuple;

class SchemeTuning
{
public:
	ComplexName& getDescriptor();
	int addNewDescription(const wstring& name);

	pair<int, const vector<int>> getDescriptionTags() const;
	bool checkForExternalLinkDescription(int tag) const;

	bool isIdentical(const SchemeTuning& arg) const;
	bool checkConditionsForAchievable(const vector<tuple<int, int, bool>>& conditions) const;

private:
	ComplexName descriptor;
	vector<int> descriptionTags;

};

inline ComplexName& SchemeTuning::getDescriptor()
{
	return this->descriptor;
}

inline pair<int, const vector<int>> SchemeTuning::getDescriptionTags() const
{
	return pair {this->descriptor.extractParamTag(), this->descriptionTags};
}
