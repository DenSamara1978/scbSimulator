#pragma once

#include "SchemeEquipment.h"

class SchemeMeasuringPanel : public SchemeEquipment
{
public:
    SchemeMeasuringPanel ( const wstring& name );

    virtual int fixDescription () override;
};
