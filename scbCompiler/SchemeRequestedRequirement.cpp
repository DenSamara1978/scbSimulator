#include "SchemeRequestedRequirement.h"

int SchemeRequestedRequirement::setLinkedGrantingRequirements(int index)
{
	if (this->grantingRequirement == -1)
	{
		this->grantingRequirement = index;
		return 0;
	}
	else
		return -1;
}

void SchemeRequestedRequirement::addNewInputGroup()
{
	this->inputs.emplace_back();
}

void SchemeRequestedRequirement::addNewInput(int input)
{
	this->inputs.back().push_back(input);
}

void SchemeRequestedRequirement::addNewFakeInput()
{
	this->inputs.back().push_back(-1);
}

int SchemeRequestedRequirement::fixInputGroup()
{
	int count = 0, fake = 0;
	for (const auto& input : this->inputs.back())
	{
		++count;
		if (input == -1)
			++fake;
	}
	return (count == fake) ? -1 : 0;
}
