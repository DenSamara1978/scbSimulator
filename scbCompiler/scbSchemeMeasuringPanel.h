#pragma once

#include "scbSchemeEquipment.h"

class scbSchemeMeasuringPanel : public scbSchemeEquipment
{
public:
    scbSchemeMeasuringPanel ( const wstring& name );

    virtual int FixDescription () override;
};
