#pragma once

#include "scbSchemeObject.h"

class scbSchemeInput : public scbSchemeObject
{
public:
	scbSchemeInput ( const wstring& name);
	virtual ~scbSchemeInput () override;

	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override;
};
