#pragma once

#include <string>
#include <vector>
#include "scbComplexName.h"
#include "scbSchemeConditionObject.h"

using std::vector;
using std::wstring;

class scbSchemeExternalConnection : public scbSchemeConditionObject
{
	scbComplexName m_Descriptor;

public:
	scbComplexName& GetDescriptor ();
	const scbComplexName& GetDescriptor () const;
};

inline scbComplexName& scbSchemeExternalConnection::GetDescriptor ()
{
	return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeExternalConnection::GetDescriptor () const
{
	return this->m_Descriptor;
}
