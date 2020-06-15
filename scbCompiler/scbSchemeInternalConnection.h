#pragma once

#include <string>
#include <vector>
#include "scbComplexName.h"
#include "scbSchemeConditionObject.h"

using std::vector;
using std::wstring;

class scbSchemeInternalConnection : public scbSchemeConditionObject
{
	scbComplexName m_FirstDescriptor;
	scbComplexName m_SecondDescriptor;

public:

	scbComplexName& GetDescriptor ( int index );
	const scbComplexName& GetDescriptor ( int index ) const;
};

inline scbComplexName& scbSchemeInternalConnection::GetDescriptor ( int index )
{
	if ( index == 0 )
		return this->m_FirstDescriptor;
	else
		return this->m_SecondDescriptor;
}

inline const scbComplexName& scbSchemeInternalConnection::GetDescriptor ( int index ) const
{
	if ( index == 0 )
		return this->m_FirstDescriptor;
	else
		return this->m_SecondDescriptor;
}
