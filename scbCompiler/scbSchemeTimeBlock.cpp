#include "scbSchemeTimeBlock.h"

scbSchemeTimeBlock::scbSchemeTimeBlock ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type )
{
    this->m_Case = scbDescription::DeviceCase::NMSH;
    switch ( type )
    {
    case Type::BVMSH:
        this->m_TypeName = L"����";
        break;
    case Type::BVV_M:
        this->m_TypeName = L"���-�";
        break;
    case Type::BVV_C:
        this->m_TypeName = L"���-�";
        break;
    }
}

int scbSchemeTimeBlock::SetJumper ( const wstring& jumper )
{
    return 0;
}

int scbSchemeTimeBlock::FixDescription ()
{
    return 0;
}
