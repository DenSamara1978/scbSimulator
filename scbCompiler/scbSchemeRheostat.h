#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeRheostat : public scbSchemeEquipment
{
    int m_Resistance;

public:
    scbSchemeRheostat ( const wstring& name );

    virtual int SetNominal ( const wstring& nominal ) override;
    virtual int SetUnitOfNominal ( const wstring& unit ) override;
    virtual int FixDescription () override;
};
