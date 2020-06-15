#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeCapacitor : public scbSchemeEquipment
{
public:
    enum class Type { KEG_1_30V, KEG_2_30V, MBGCH_1_1_250V, MBGCH_1_2A_250V, EGC_30V };

private:
    int m_Capacity;
    Type m_Type;

public:
    scbSchemeCapacitor ( const wstring& name, Type type );

    virtual int SetNominal ( const wstring& nominal ) override;
    virtual int SetUnitOfNominal ( const wstring& unit ) override;
    virtual int FixDescription () override;
};
