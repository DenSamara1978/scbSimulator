#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeTransformer_ST4 : public scbSchemeEquipment
{
public:
    enum class Type { ST4A, ST4M, ST4MP, ST4G };

private:
    Type m_Type;

public:
    scbSchemeTransformer_ST4 ( const wstring& name, Type type );

    virtual int SetJumper ( const wstring& jumper );
    virtual int FixDescription ();
}
