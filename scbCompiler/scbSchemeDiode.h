#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeDiode : public scbSchemeEquipment
{
public:
    enum class Type { D226B };

private:
    Type m_Type;

public:
    scbSchemeDiode ( const wstring& name, Type type );

    virtual int FixDescription () override;
};
