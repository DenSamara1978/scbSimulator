#include <stdexcept>
#include "SchemeExtendedBlock.h"

int SchemeExtendedBlock::setDefaultCount(const wstring& name)
{
	size_t pos = 0;
	try
	{
		this->defaultCount = std::stoi(name, &pos);
		if ((pos < name.length()) or (this->defaultCount < 1))
			this->defaultCount = -1;
	}
	catch (std::invalid_argument)
	{
		this->defaultCount = -1;
	}
	return this->defaultCount;
}

int SchemeExtendedBlock::addNewConditionCount(const wstring& name)
{
	size_t pos = 0;
	int res = -1;
	try
	{
		res = std::stoi(name, &pos);
		if ((pos < name.length()) || (res < 1))
			res = -1;
	}
	catch (std::invalid_argument)
	{
		res = -1;
	}
	this->complectCountInCondition.push_back(res);
	return res;
}


