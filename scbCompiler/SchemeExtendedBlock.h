#pragma once

#include "SchemeConditionObject.h"

class SchemeExtendedBlock : public SchemeConditionObject
{
public:
	SchemeExtendedBlock();

	void setName(const wstring& name);
	const wstring getName() const;
	int setDefaultCount(const wstring& name);
	int addNewConditionCount(const wstring& name);

private:
	int defaultCount;
	wstring name;
	vector<int> complectCountInCondition;

};

inline SchemeExtendedBlock::SchemeExtendedBlock() :
	defaultCount(-1)
{
}

inline void SchemeExtendedBlock::setName(const wstring& name)
{
	this->name = name;
}

inline const wstring SchemeExtendedBlock::getName() const
{
	return this->name;
}
