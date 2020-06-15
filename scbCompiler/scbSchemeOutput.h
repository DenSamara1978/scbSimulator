#pragma once

#include "scbSchemeObject.h"

class scbSchemeOutput : public scbSchemeObject
{
public:
    enum class Type { No = 0, Requirement, Scheme };

private:
    Type m_Type;

public:
	scbSchemeOutput ( const wstring& name, Type type );
	virtual ~scbSchemeOutput () override;

	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override;
};
