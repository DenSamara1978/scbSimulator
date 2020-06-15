#pragma once

#include "scbComplexName.h"
#include "scbSchemeConditionObject.h"

class scbSchemeEvent : public scbSchemeConditionObject
{
public:
    enum class ProbablityClass { No = 0, EngineMSP, EngineMSA, BDR_M };

private:
    scbComplexName m_Descriptor;
    vector<int> m_StatusSet;
    vector<int> m_StatusReset;
    ProbablityClass m_ProbablityClass;

public:
    scbSchemeEvent ();

    scbComplexName& GetDescriptor ();
    const scbComplexName& GetDescriptor () const;

    void StatusSet ( int status );
    void StatusReset ( int status );

    int SetProbablityClass ( const wstring& name );
};

inline scbComplexName& scbSchemeEvent::GetDescriptor ()
{
    return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeEvent::GetDescriptor () const
{
    return this->m_Descriptor;
}

inline void scbSchemeEvent::StatusSet ( int status )
{
    this->m_StatusSet.push_back ( status );
}

inline void scbSchemeEvent::StatusReset ( int status )
{
    this->m_StatusReset.push_back ( status );
}
