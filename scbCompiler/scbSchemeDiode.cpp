#include "scbSchemeDiode.h"

scbSchemeDiode::scbSchemeDiode ( const wstring& name, Type type ) :
    scbSchemeEquipment ( name ),
    m_Type ( type )
{
    this->m_Case = scbDescription::DeviceCase::Diode;
    switch ( type )
    {
    case Type::D226B:
        this->m_TypeName = L"Ä226Á";
        break;
    }
}

int scbSchemeDiode::FixDescription ()
{
    return 0;
}
