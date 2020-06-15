#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeTimeBlock : public scbSchemeEquipment
{
public:
    enum class Type { BVMSH, BVV_M, BVV_C };

private:
    Type m_Type;

public:
    scbSchemeTimeBlock ( const wstring& name, Type type );

    virtual int SetJumper ( const wstring& jumper ) override;
    virtual int FixDescription () override;
};
