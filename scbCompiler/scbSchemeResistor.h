#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeResistor : public scbSchemeEquipment
{
public:
    enum class Type { MLT_1, MLT_2, PEV_25, PEV_50 };

private:
    int m_Resistance;
    Type m_Type;

public:
    scbSchemeResistor ( const wstring& name, Type type );

    virtual int SetNominal ( const wstring& nominal ) override;
    virtual int SetUnitOfNominal ( const wstring& unit ) override;
    virtual int FixDescription () override;
};
