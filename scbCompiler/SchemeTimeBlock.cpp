#include "SchemeTimeBlock.h"

SchemeTimeBlock::SchemeTimeBlock(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::NMSH;
	switch (type)
	{
		case Type::BVMSH:
			this->typeName = L"абль";
			break;
		case Type::BVV_M:
			this->typeName = L"абб-л";
			break;
		case Type::BVV_C:
			this->typeName = L"абб-ж";
			break;
	}
}

int SchemeTimeBlock::setJumper(const wstring& jumper)
{
	return 0;
}

int SchemeTimeBlock::fixDescription()
{
	return 0;
}
