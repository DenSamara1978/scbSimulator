#include <stdexcept>
#include "scbSchemeFuse.h"

scbSchemeFuse::scbSchemeFuse ( const wstring& name ) :
    scbSchemeEquipment ( name ),
    m_MaxCurrent ( 0.0f ),
    m_PowerClass ( PowerClass::No )
{
    this->m_Case = scbDescription::DeviceCase::Fuse;
    this->m_TypeName = L"��������������";
}

int scbSchemeFuse::SetNominal ( const wstring& nominal )
{
    size_t pos = 0;
    int res = 0;
    try
    {
        this->m_MaxCurrent = std::stof ( nominal, &pos );
        if ( pos < nominal.length () )
        {
            this->m_MaxCurrent = 0.0f;
            res = -1;
        }
    }
    catch ( std::invalid_argument )
    {
        this->m_MaxCurrent = 0.0f;
        res = -1;
    }
    return ( res == 0 ) ? 0 : 1;
}

int scbSchemeFuse::SetUnitOfNominal ( const wstring& unit )
{
    return ( unit == L"�" ) ? 0 : 1;
}

int scbSchemeFuse::SetPowerClass ( const wstring& power_class )
{
    if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::RPB;
    else if ( power_class == L"����" )
        this->m_PowerClass = PowerClass::PHKS;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::PHS;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::OHS;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::PHL;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::OHL;
    else if ( power_class == L"�" )
        this->m_PowerClass = PowerClass::P;
    else if ( power_class == L"�" )
        this->m_PowerClass = PowerClass::M;
    else if ( power_class == L"��" )
        this->m_PowerClass = PowerClass::SH;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::KSH;
    else if ( power_class == L"���" )
        this->m_PowerClass = PowerClass::SHM;
    else
        return 1;

    return 0;
}

int scbSchemeFuse::FixDescription ()
{
    if ( this->m_MaxCurrent == 0 )
        return 3;
    else if ( this->m_PowerClass == PowerClass::No )
        return 4;
    else
        return 0;
}
