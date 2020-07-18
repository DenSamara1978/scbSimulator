#pragma once

#include "SchemeObject.h"

class SchemeLine : public SchemeObject
{
public:
	SchemeLine(const wstring& name);
	virtual ~SchemeLine() override;

	virtual int setDescriptor(const ComplexName& descriptor) override;
	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;

private:
	ComplexName object;

};
