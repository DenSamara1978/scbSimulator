#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeTransformer_SKT : public scbSchemeEquipment
{
public:
    scbSchemeTransformer_SKT ( const wstring& name );

    virtual int SetJumper ( const wstring& jumper );
    virtual int FixDescription ();
};
