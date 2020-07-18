#include "SchemeTransformerSkt.h"

SchemeTransformerSkt::SchemeTransformerSkt(const wstring& name) :
	SchemeEquipment(name)
{
	this->deviceCase = Description::DeviceCase::SKTTransformer;
	this->typeName = L"ัสา-1";
}

int SchemeTransformerSkt::setJumper(const wstring& jumper)
{
	return 0;
}

int SchemeTransformerSkt::fixDescription()
{
	return 0;
}
