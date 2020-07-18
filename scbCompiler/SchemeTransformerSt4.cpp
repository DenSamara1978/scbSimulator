#include "SchemeTransformerSt4.h"

SchemeTransformerSt4::SchemeTransformerSt4(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::SmallTransformer;
	switch (type)
	{
		case Type::ST4A:
			this->typeName = L"��-4�";
			break;
		case Type::ST4M:
			this->typeName = L"��-4�";
			break;
		case Type::ST4MP:
			this->typeName = L"��-4��";
			break;
		case Type::ST4G:
			this->typeName = L"��-4�";
			break;
	}
}

int SchemeTransformerSt4::setJumper(const wstring& jumper)
{
	return 0;
}

int SchemeTransformerSt4::fixDescription()
{
	return 0;
}
