#pragma once

#include <vector>
#include "scbComplexName.h"

using std::vector;

class scbSchemeRequestedRequirement
{
    scbComplexName m_Name;
    int m_GrantingRequirement;
    vector<vector<int>> m_Inputs;

public:
    scbSchemeRequestedRequirement ();
    void SetDescriptor ( const scbComplexName& descriptor );
    scbComplexName& GetDescriptor ();
    const scbComplexName& GetDescriptor () const;

    int SetLinkedGrantingRequirements ( int index );
    int GetLinkedGrantingRequirements () const;

    void AddNewInputGroup ();
    void AddNewInput ( int input );
    void AddNewFakeInput ();
    int FixInputGroup ();
};

inline scbSchemeRequestedRequirement::scbSchemeRequestedRequirement () :
    m_GrantingRequirement ( -1 )
{
}

inline void scbSchemeRequestedRequirement::SetDescriptor ( const scbComplexName& descriptor )
{
    this->m_Name = descriptor;
}

inline scbComplexName& scbSchemeRequestedRequirement::GetDescriptor ()
{
    return this->m_Name;
}

inline const scbComplexName& scbSchemeRequestedRequirement::GetDescriptor () const
{
    return this->m_Name;
}

inline int scbSchemeRequestedRequirement::GetLinkedGrantingRequirements () const
{
    return this->m_GrantingRequirement;
}
