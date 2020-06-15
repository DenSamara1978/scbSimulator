#pragma once

#include <string>
#include <array>
#include "scbSchemeObject.h"

using std::wstring;
using std::array;

class scbSchemeCross : public scbSchemeObject
{
    int m_Order;
    wstring m_Cable;
    array<int, 8> m_Contacts;
    int m_Count;

public:
    scbSchemeCross ( const wstring& name );
    virtual ~scbSchemeCross () override;

    virtual int SetLocation ( const wstring& location ) override;
    virtual int SetPlacement ( int id, scbDescription::PlacementType pl_type ) override;
    virtual int SetOrder ( int order ) override;
    virtual int SetCable ( const wstring& cable ) override;
    virtual int SetContact ( const wstring& contact ) override;
    virtual int SetCount ( int count ) override;

    virtual int FixDescription () override;
    virtual const ObjectType GetObjectType () const override;
};




