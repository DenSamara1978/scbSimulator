#include <stdexcept>
#include "scbSchemeResistor.h"

scbSchemeResistor::scbSchemeResistor ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type ),
    m_Resistance ( 0 )
{
    this->m_Case = scbDescription::DeviceCase::Resistor;
    switch ( type )
    {
    case Type::PEV_25:
        this->m_TypeName = L"ÏÝÂ-25";
        break;
    case Type::PEV_50:
        this->m_TypeName = L"ÏÝÂ-50";
        break;
    case Type::MLT_1:
        this->m_TypeName = L"ÌËÒ-1";
        break;
    case Type::MLT_2:
        this->m_TypeName = L"ÌËÒ-2";
        break;
    }
}

int scbSchemeResistor::SetNominal ( const wstring& nominal )
{
    size_t pos = 0;
    int res = 0;
    try
    {
        this->m_Resistance = std::stoi ( nominal, &pos );
        if ( pos < nominal.length () )
        {
            this->m_Resistance = 0;
            res = -1;
        }
    }
    catch ( std::invalid_argument )
    {
        this->m_Resistance = 0;
        res = -1;
    }
    return ( res == 0 ) ? 0 : 1;
}

int scbSchemeResistor::SetUnitOfNominal ( const wstring& unit )
{
    if ( unit == L"Îì" )
        return 0;
    else if ( unit == L"êÎì" )
    {
        this->m_Resistance *= 1000;
        return 0;
    }
    else
        return 1;
}

int scbSchemeResistor::FixDescription ()
{
    return ( this->m_Resistance == 0 ) ? 3 : 0;
}
