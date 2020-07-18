#include "SchemeTransformerSt5.h"

SchemeTransformerSt5::SchemeTransformerSt5(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::SmallTransformer;
	switch (type)
	{
		case Type::ST5A:
			this->typeName = L"бв-5Р";
			break;
		case Type::ST5M:
			this->typeName = L"бв-5Ь";
			break;
		case Type::ST5MP:
			this->typeName = L"бв-5ЬЯ";
			break;
		case Type::ST5G:
			this->typeName = L"бв-5У";
			break;
	}
}

int SchemeTransformerSt5::setJumper(const wstring& jumper)
{
	return 0;
}

int SchemeTransformerSt5::fixDescription()
{
	return 0;
}
