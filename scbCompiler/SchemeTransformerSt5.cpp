#include "SchemeTransformerSt5.h"

SchemeTransformerSt5::SchemeTransformerSt5(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::SmallTransformer;
	switch (type)
	{
		case Type::ST5A:
			this->typeName = L"��-5�";
			break;
		case Type::ST5M:
			this->typeName = L"��-5�";
			break;
		case Type::ST5MP:
			this->typeName = L"��-5��";
			break;
		case Type::ST5G:
			this->typeName = L"��-5�";
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
