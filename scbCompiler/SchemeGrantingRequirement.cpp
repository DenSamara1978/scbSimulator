#include "SchemeGrantingRequirement.h"

using std::get;

int SchemeGrantingRequirement::addRequirementName(const ComplexName& descriptor)
{
	const auto count = this->requirementNames.size();
	if (count > 0)
		for (size_t index = 0; index < count - 1; ++index)
			if (this->requirementNames[index].isFullyEqual(descriptor))
				return -1;
	this->requirementNames.push_back(descriptor);
	return 0;
}

bool SchemeGrantingRequirement::checkRequirementNames(const ComplexName& descriptor) const
{
	for (const auto& desc : this->requirementNames)
		if (desc.isFullyEqual(descriptor))
			return true;
	return false;
}

int SchemeGrantingRequirement::sourceSetCount(int count)
{
	if (count <= 0)
		return -1;
	this->sourceCount = count;
	return 0;
}

void SchemeGrantingRequirement::sourceNewRecord()
{
	this->sourceRecords.emplace_back(0, 0, 0);
}

int SchemeGrantingRequirement::sourceSetFrom(int from)
{
	get<0>(this->sourceRecords.back()) = from;
	return 0;
}

int SchemeGrantingRequirement::sourceSetTo(int to)
{
	if (get<0>(this->sourceRecords.back()) <= to)
	{
		get<1>(this->sourceRecords.back()) = to;
		return 0;
	}
	else
		return -1;
}

int SchemeGrantingRequirement::sourceAddOutput(int id)
{
	const auto& outputs = get<2>(this->sourceRecords.back());
	if (outputs.size() < static_cast<size_t> (this->sourceCount))
	{
		get<2>(this->sourceRecords.back()).push_back(id);
		return 0;
	}
	else
		return -1;
}

int SchemeGrantingRequirement::sourceFixRecord()
{
	const auto& outputs = get<2>(this->sourceRecords.back());
	if (outputs.size() == static_cast<size_t> (this->sourceCount))
		return 0;
	else
		return -1;
}
