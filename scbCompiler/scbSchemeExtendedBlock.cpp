#include <stdexcept>
#include "scbSchemeExtendedBlock.h"

int scbSchemeExtendedBlock::SetDefaultCount ( const wstring& name )
{
	size_t pos = 0;
	try
	{
		this->m_DefaultCount = std::stoi ( name, &pos );
		if ( ( pos < name.length () ) || ( this->m_DefaultCount < 1 ) )
			this->m_DefaultCount = -1;
	}
	catch ( std::invalid_argument )
	{
		this->m_DefaultCount = -1;
	}
	return this->m_DefaultCount;
}

int scbSchemeExtendedBlock::AddNewConditionCount ( const wstring& name )
{
	size_t pos = 0;
	int res = -1;
	try
	{
		res = std::stoi ( name, &pos );
		if ( ( pos < name.length () ) || ( res < 1 ) )
			res = -1;
	}
	catch ( std::invalid_argument )
	{
		res = -1;
	}
	this->m_ComplectCountInCondition.push_back ( res );
	return res;
}


