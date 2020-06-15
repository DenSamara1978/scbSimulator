#include "scbSchemeTransformer_ST4.h"

scbSchemeTransformer_ST4::scbSchemeTransformer_ST4 ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type )
{
    this->m_Case = scbDescription::DeviceCase::SmallTransformer;
    switch ( type )
    {
    case Type::ST4A:
        this->m_TypeName = L"бв-4Р";
        break;
    case Type::ST4M:
        this->m_TypeName = L"бв-4Ь";
        break;
    case Type::ST4MP:
        this->m_TypeName = L"бв-4ЬЯ";
        break;
    case Type::ST4G:
        this->m_TypeName = L"бв-4У";
        break;
    }
}

int scbSchemeTransformer_ST4::SetJumper ( const wstring& jumper )
{
    return 0;
}

int scbSchemeTransformer_ST4::FixDescription ()
{
    return 0;
}
