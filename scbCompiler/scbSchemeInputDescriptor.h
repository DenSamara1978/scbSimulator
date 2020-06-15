#pragma once

#include "scbComplexName.h"

class scbSchemeInputDescriptor
{
public:
    enum class Type { FreeInput, GroupInput, Input };

private:
    Type m_Type;
    scbComplexName m_Descriptor;

public:
    scbSchemeInputDescriptor ( const scbComplexName& descriptor, Type type );
    scbComplexName& GetDescriptor ();
    const scbComplexName& GetDescriptor () const;
    bool CheckDescriptor ( const scbComplexName& descriptor, Type type ) const;
};

inline scbSchemeInputDescriptor::scbSchemeInputDescriptor ( const scbComplexName& descriptor, Type type ) :
    m_Descriptor ( descriptor ),
    m_Type ( type )
{
}

inline scbComplexName& scbSchemeInputDescriptor::GetDescriptor ()
{
    return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeInputDescriptor::GetDescriptor () const
{
    return this->m_Descriptor;
}

inline bool scbSchemeInputDescriptor::CheckDescriptor ( const scbComplexName& descriptor, Type type ) const
{
    return ( ( this->m_Descriptor.IsFullyEqual ( descriptor ) ) and ( this->m_Type == type ) );
}
