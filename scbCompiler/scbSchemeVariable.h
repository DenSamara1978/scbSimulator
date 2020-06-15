#pragma once

#include "scbSchemeObject.h"

class scbSchemeVariable : public scbSchemeObject
{
public:
	scbSchemeVariable (const wstring& name);
	virtual ~scbSchemeVariable () override;

	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override;
};
