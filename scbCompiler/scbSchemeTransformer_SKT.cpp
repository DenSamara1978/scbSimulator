#include "scbSchemeTransformer_SKT.h"

scbSchemeTransformer_SKT::scbSchemeTransformer_SKT ( const wstring& name ) :
    scbSchemeEquipment ( name )
{
    this->m_Case = scbDescription::DeviceCase::SKTTransformer;
    this->m_TypeName = L"ัสา-1";
}

int scbSchemeTransformer_SKT::SetJumper ( const wstring& jumper )
{
    return 0;
}

int scbSchemeTransformer_SKT::FixDescription ()
{
    return 0;
}
