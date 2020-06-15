#pragma once

#include "scbSchemeObject.h"

class scbSchemeLine : public scbSchemeObject
{
    scbComplexName m_Object;

public:
	scbSchemeLine ( const wstring& name );
	virtual ~scbSchemeLine () override;

    virtual int SetDescriptor ( const scbComplexName& descriptor ) override;
	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override;
};
