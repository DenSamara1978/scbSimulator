#pragma once

#include "SchemeObject.h"

class SchemeOutput : public SchemeObject
{
public:
	enum class Type { No = 0, Requirement, Scheme };

	SchemeOutput(const wstring& name, Type type);
	virtual ~SchemeOutput() override;

	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;

private:
	Type type;

};
