#pragma once

#include <string>
#include <vector>
#include "ComplexName.h"
#include "SchemeConditionObject.h"

using std::vector;
using std::wstring;

class SchemeExternalConnection : public SchemeConditionObject
{
public:
	ComplexName& getDescriptor ();
	const ComplexName& getDescriptor () const;

private:
	ComplexName descriptor;

};

inline ComplexName& SchemeExternalConnection::getDescriptor ()
{
	return this->descriptor;
}

inline const ComplexName& SchemeExternalConnection::getDescriptor () const
{
	return this->descriptor;
}
