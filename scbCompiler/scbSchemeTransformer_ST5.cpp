#include "scbSchemeTransformer_ST5.h"

scbSchemeTransformer_ST5::scbSchemeTransformer_ST5 ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type )
{
    this->m_Case = scbDescription::DeviceCase::SmallTransformer;
    switch ( type )
    {
    case Type::ST5A:
        this->m_TypeName = L"��-5�";
        break;
    case Type::ST5M:
        this->m_TypeName = L"��-5�";
        break;
    case Type::ST5MP:
        this->m_TypeName = L"��-5��";
        break;
    case Type::ST5G:
        this->m_TypeName = L"��-5�";
        break;
    }
}

int scbSchemeTransformer_ST5::SetJumper ( const wstring& jumper )
{
    return 0;
}

int scbSchemeTransformer_ST5::FixDescription ()
{
    return 0;
}
