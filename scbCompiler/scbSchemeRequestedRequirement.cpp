#include "scbSchemeRequestedRequirement.h"

int scbSchemeRequestedRequirement::SetLinkedGrantingRequirements ( int index )
{
    if ( this->m_GrantingRequirement == -1 )
    {
        this->m_GrantingRequirement = index;
        return 0;
    }
    else 
        return -1;
}

void scbSchemeRequestedRequirement::AddNewInputGroup ()
{
    this->m_Inputs.emplace_back ();
}

void scbSchemeRequestedRequirement::AddNewInput ( int input )
{
    this->m_Inputs.back ().push_back ( input );
}

void scbSchemeRequestedRequirement::AddNewFakeInput ()
{
    this->m_Inputs.back ().push_back ( -1 );
}

int scbSchemeRequestedRequirement::FixInputGroup ()
{
    int count = 0, fake = 0;
    for ( const auto& input : this->m_Inputs.back () )
    {
        ++count;
        if ( input == -1 )
            ++fake;
    }
    return ( count == fake ) ? -1 : 0;
}
