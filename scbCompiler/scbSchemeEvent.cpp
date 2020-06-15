#include "scbSchemeEvent.h"

scbSchemeEvent::scbSchemeEvent () :
    m_ProbablityClass ( ProbablityClass::No )
{
}

int scbSchemeEvent::SetProbablityClass ( const wstring& name )
{
    if ( name == L"Äâèãàòåëü ÌÑÏ" )
        this->m_ProbablityClass = ProbablityClass::EngineMSP;
    else if ( name == L"Äâèãàòåëü ÌÑÀ" )
        this->m_ProbablityClass = ProbablityClass::EngineMSA;
    else if ( name == L"ÁÄÐ-Ì" )
        this->m_ProbablityClass = ProbablityClass::BDR_M;
    else
        return -1;    
    return 0;
}
