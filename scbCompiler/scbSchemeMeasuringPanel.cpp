#include "scbSchemeMeasuringPanel.h"

scbSchemeMeasuringPanel::scbSchemeMeasuringPanel ( const wstring& name ) :
    scbSchemeEquipment ( name )
{
    this->m_Case = scbDescription::DeviceCase::MeasuringPanel;
}

int scbSchemeMeasuringPanel::FixDescription ()
{
    if ( this->m_ObjectNames.size () == 0 )
        return 5;
    else
        return 0;
}
