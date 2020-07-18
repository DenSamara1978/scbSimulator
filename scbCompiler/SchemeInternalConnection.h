#pragma once

#include <string>
#include <vector>
#include "ComplexName.h"
#include "SchemeConditionObject.h"

using std::vector;
using std::wstring;

class SchemeInternalConnection : public SchemeConditionObject
{
public:

	ComplexName& getDescriptor(int index);
	const ComplexName& getDescriptor(int index) const;

private:
	ComplexName firstDescriptor;
	ComplexName secondDescriptor;

};

inline ComplexName& SchemeInternalConnection::getDescriptor(int index)
{
	if (index == 0)
		return this->firstDescriptor;
	else
		return this->secondDescriptor;
}

inline const ComplexName& SchemeInternalConnection::getDescriptor(int index) const
{
	if (index == 0)
		return this->firstDescriptor;
	else
		return this->secondDescriptor;
}
