#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "scbComplexName.h"

using std::wstring;
using std::vector;
using std::tuple;

class scbSchemeGrantingRequirement
{
public:
    enum class Type { Source, Transit };

private:
	wstring m_SourceName; // Локальное имя потребности для Source
    Type m_Type;

    vector<scbComplexName> m_RequirementNames; // Имена, под которыми потребности видны наружу
    vector<tuple<int, int, vector<int>>> m_SourceRecords; // Записи для Source - "от", "до", ["индекс входа"]
    int m_SourceCount; // Количество раздаваемых выходов, для Source
    int m_MaxRequesting; // Масимальный номер запроса для Source

    int m_RequestedRequirement; // Индекс источника для Transit

public:
	scbSchemeGrantingRequirement ( const wstring& name );
    scbSchemeGrantingRequirement ( int requested_req );
    const wstring& GetName () const;

    void SetMaxRequesting ( int num );
    int GetMaxRequesting () const;
    int AddRequirementName ( const scbComplexName& descriptor );
    bool CheckRequirementNames ( const scbComplexName& descriptor ) const;
    int SourceSetCount ( int count );
    void SourceNewRecord ();
    int SourceSetFrom ( int from );
    int SourceSetTo ( int to );
    int SourceAddOutput ( int id );
    int SourceFixRecord ();

    bool IsSourceEnable () const;

    int GetLinkedRequestedRequirement () const;
};

inline scbSchemeGrantingRequirement::scbSchemeGrantingRequirement ( const wstring& name ) :
	m_SourceName ( name ),
    m_Type ( Type::Source ),
    m_SourceCount ( 0 ),
    m_MaxRequesting ( 0 ),
    m_RequestedRequirement ( -1 )
{
}

inline scbSchemeGrantingRequirement::scbSchemeGrantingRequirement ( int requested_req ) :
    m_Type ( Type::Transit ),
    m_SourceCount ( 0 ),
    m_MaxRequesting ( 0 ),
    m_RequestedRequirement ( requested_req )
{
}

inline const wstring& scbSchemeGrantingRequirement::GetName () const
{
	return this->m_SourceName;
}

inline void scbSchemeGrantingRequirement::SetMaxRequesting ( int num )
{
    this->m_MaxRequesting = num;
}

inline int scbSchemeGrantingRequirement::GetMaxRequesting () const
{
    return this->m_MaxRequesting;
}

inline bool scbSchemeGrantingRequirement::IsSourceEnable () const
{
    return ( this->m_SourceCount != 0 );
}

inline int scbSchemeGrantingRequirement::GetLinkedRequestedRequirement () const
{
    return this->m_RequestedRequirement;
}
