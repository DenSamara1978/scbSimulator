#pragma once

#include "SchemeObject.h"

class SchemeInput : public SchemeObject
{
public:
	SchemeInput(const wstring& name);
	virtual ~SchemeInput() override;

	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;
};
