#include <stdexcept>
#include "scbSchemeRheostat.h"

scbSchemeRheostat::scbSchemeRheostat ( const wstring& name ) :
    scbSchemeEquipment ( name ),
    m_Resistance ( 0 )
{
    this->m_Case = scbDescription::DeviceCase::Rheostat;
    this->m_TypeName = L"–еостат";
}

int scbSchemeRheostat::SetNominal ( const wstring& nominal )
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
    return ( res == 0 ) ? 0 : -1;
}

int scbSchemeRheostat::SetUnitOfNominal ( const wstring& unit )
{
    if ( unit == L"ќм" )
        return 0;
    else if ( unit == L"кќм" )
    {
        this->m_Resistance *= 1000;
        return 0;
    }
    else
        return 1;
}

int scbSchemeRheostat::FixDescription ()
{
    return ( this->m_Resistance == 0 ) ? 3 : 0;
}