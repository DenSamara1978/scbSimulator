#pragma once

#include <vector>
#include "ComplexName.h"

using std::vector;

class SchemeRequestedRequirement
{
public:
	SchemeRequestedRequirement();
	void setDescriptor(const ComplexName& descriptor);
	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;

	int setLinkedGrantingRequirements(int index);
	int getLinkedGrantingRequirements() const;

	void addNewInputGroup();
	void addNewInput(int input);
	void addNewFakeInput();
	int fixInputGroup();

private:
	ComplexName name;
	int grantingRequirement;
	vector<vector<int>> inputs;

};

inline SchemeRequestedRequirement::SchemeRequestedRequirement() :
	grantingRequirement(-1)
{
}

inline void SchemeRequestedRequirement::setDescriptor(const ComplexName& descriptor)
{
	this->name = descriptor;
}

inline ComplexName& SchemeRequestedRequirement::getDescriptor()
{
	return this->name;
}

inline const ComplexName& SchemeRequestedRequirement::getDescriptor() const
{
	return this->name;
}

inline int SchemeRequestedRequirement::getLinkedGrantingRequirements() const
{
	return this->grantingRequirement;
}
