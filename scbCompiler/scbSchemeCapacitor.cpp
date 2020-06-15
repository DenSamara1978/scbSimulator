#include <stdexcept>
#include "scbSchemeCapacitor.h"

scbSchemeCapacitor::scbSchemeCapacitor ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type ),
    m_Capacity ( 0 )
{
    this->m_Case = scbDescription::DeviceCase::Capacitor;
    switch ( type )
    {
    case Type::KEG_1_30V:
        this->m_TypeName = L"���-1-30�";
        break;
    case Type::KEG_2_30V:
        this->m_TypeName = L"���-2-30�";
        break;
    case Type::MBGCH_1_1_250V:
        this->m_TypeName = L"����-1-1-250�";
        break;
    case Type::MBGCH_1_2A_250V:
        this->m_TypeName = L"����-1-2�-250�";
        break;
    case Type::EGC_30V:
        this->m_TypeName = L"���-30�";
        break;
    }
}

int scbSchemeCapacitor::SetNominal ( const wstring& nominal )
{
    size_t pos = 0;
    int res = 0;
    try
    {
        this->m_Capacity = std::stoi ( nominal, &pos );
        if ( pos < nominal.length ())
        {
            this->m_Capacity = 0;
            res = -1;
        }
    }
    catch ( std::invalid_argument )
    {
        this->m_Capacity = 0;
        res = -1;
    }
    return ( res == 0 ) ? 0 : 1;
}

int scbSchemeCapacitor::SetUnitOfNominal ( const wstring& unit )
{
    return ( unit == L"���" ) ? 0 : 1;
}

int scbSchemeCapacitor::FixDescription ()
{
    return ( this->m_Capacity == 0 ) ? 3 : 0;
}
