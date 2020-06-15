#include "scbSchemeGrantingRequirement.h"

using std::get;

int scbSchemeGrantingRequirement::AddRequirementName ( const scbComplexName& descriptor )
{
    const auto count = this->m_RequirementNames.size ();
    if ( count > 0 )
        for ( size_t index = 0; index < count - 1; ++index )
            if ( this->m_RequirementNames [index].IsFullyEqual ( descriptor ) )
                return -1;
    this->m_RequirementNames.push_back ( descriptor );
    return 0;
}

bool scbSchemeGrantingRequirement::CheckRequirementNames ( const scbComplexName& descriptor ) const
{
    for ( const auto& desc : this->m_RequirementNames )
        if ( desc.IsFullyEqual ( descriptor ) )
            return true;
    return false;
}

int scbSchemeGrantingRequirement::SourceSetCount ( int count )
{
    if ( count <= 0 )
        return -1;
    this->m_SourceCount = count;
    return 0;
}

void scbSchemeGrantingRequirement::SourceNewRecord ()
{
    this->m_SourceRecords.emplace_back ( 0, 0, 0 );
}

int scbSchemeGrantingRequirement::SourceSetFrom ( int from )
{
    get<0> ( this->m_SourceRecords.back () ) = from;
    return 0;
}

int scbSchemeGrantingRequirement::SourceSetTo ( int to )
{
    if ( get<0> ( this->m_SourceRecords.back () ) <= to )
    {
        get<1> ( this->m_SourceRecords.back () ) = to;
        return 0;
    }
    else
        return -1;
}

int scbSchemeGrantingRequirement::SourceAddOutput ( int id )
{
    const auto& outputs = get<2> ( this->m_SourceRecords.back () );
    if ( outputs.size () < static_cast<size_t> ( this->m_SourceCount ))
    {
        get<2> ( this->m_SourceRecords.back ()).push_back ( id );
        return 0;
    }
    else
        return -1;
}

int scbSchemeGrantingRequirement::SourceFixRecord ()
{
    const auto& outputs = get<2> ( this->m_SourceRecords.back () );
    if ( outputs.size () == static_cast<size_t> ( this->m_SourceCount ))
        return 0;
    else
        return -1;
}
