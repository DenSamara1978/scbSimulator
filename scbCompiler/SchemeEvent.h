#pragma once

#include "ComplexName.h"
#include "SchemeConditionObject.h"

class SchemeEvent : public SchemeConditionObject
{
public:
	enum class ProbablityClass { No = 0, EngineMSP, EngineMSA, BDR_M };

	SchemeEvent();

	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;

	void statusSet(int status);
	void statusReset(int status);

	int setProbablityClass(const wstring& name);

private:
	ComplexName descriptor;
	vector<int> statusSets;
	vector<int> statusResets;
	ProbablityClass probablityClass;

};

inline ComplexName& SchemeEvent::getDescriptor()
{
	return this->descriptor;
}

inline const ComplexName& SchemeEvent::getDescriptor() const
{
	return this->descriptor;
}

inline void SchemeEvent::statusSet(int status)
{
	this->statusSets.push_back(status);
}

inline void SchemeEvent::statusReset(int status)
{
	this->statusResets.push_back(status);
}
