#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeTransformer_ST5 : public scbSchemeEquipment
{
public:
    enum class Type { ST5A, ST5M, ST5MP, ST5G };

private:
    Type m_Type;

public:
    scbSchemeTransformer_ST5 ( const wstring& name, Type type );

    virtual int SetJumper ( const wstring& jumper );
    virtual int FixDescription ();
};
