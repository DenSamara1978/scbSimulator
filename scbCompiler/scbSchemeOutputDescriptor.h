#pragma once

#include "scbComplexName.h"

class scbSchemeOutputDescriptor
{
public:
    enum class Type { Output, GroupOutput, TargetOutput, Requirement };

private:
    Type m_Type;
    scbComplexName m_Descriptor;

public:
    scbSchemeOutputDescriptor ( const scbComplexName& descriptor, Type type );
    scbComplexName& GetDescriptor ();
    const scbComplexName& GetDescriptor () const;
    bool CheckDescriptor ( const scbComplexName& descriptor, Type type ) const;
};

inline scbSchemeOutputDescriptor::scbSchemeOutputDescriptor ( const scbComplexName& descriptor, Type type ) :
    m_Descriptor ( descriptor ),
    m_Type ( type )
{
}

inline scbComplexName& scbSchemeOutputDescriptor::GetDescriptor ()
{
    return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeOutputDescriptor::GetDescriptor () const
{
    return this->m_Descriptor;
}

inline bool scbSchemeOutputDescriptor::CheckDescriptor ( const scbComplexName& descriptor, Type type ) const
{
    return ( ( this->m_Descriptor.IsFullyEqual ( descriptor ) ) and ( this->m_Type == type ) );
}
