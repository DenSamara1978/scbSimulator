#pragma once

#include "SchemeObject.h"

class SchemeVariable : public SchemeObject
{
public:
	SchemeVariable(const wstring& name);
	virtual ~SchemeVariable() override;

	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;
};
