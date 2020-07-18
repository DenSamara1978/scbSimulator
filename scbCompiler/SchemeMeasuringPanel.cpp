#include "SchemeMeasuringPanel.h"

SchemeMeasuringPanel::SchemeMeasuringPanel(const wstring& name) :
	SchemeEquipment(name)
{
	this->deviceCase = Description::DeviceCase::MeasuringPanel;
}

int SchemeMeasuringPanel::fixDescription()
{
	if (this->objectNames.size() == 0)
		return 5;
	else
		return 0;
}
