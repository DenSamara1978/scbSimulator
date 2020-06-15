#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeFuse : public scbSchemeEquipment
{
    enum class PowerClass { No = 0, RPB, PHKS, PHS, OHS, P, M, KSH, SH, SHM, PHL, OHL };

    float m_MaxCurrent;
    PowerClass m_PowerClass;

public:
    scbSchemeFuse ( const wstring& name );

    virtual int SetNominal ( const wstring& nominal ) override;
    virtual int SetUnitOfNominal ( const wstring& unit ) override;
    virtual int SetPowerClass ( const wstring& power_class ) override;
    virtual int FixDescription () override;
};
