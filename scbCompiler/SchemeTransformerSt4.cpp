#include "SchemeTransformerSt4.h"

SchemeTransformerSt4::SchemeTransformerSt4(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::SmallTransformer;
	switch (type)
	{
		case Type::ST4A:
			this->typeName = L"бв-4Р";
			break;
		case Type::ST4M:
			this->typeName = L"бв-4Ь";
			break;
		case Type::ST4MP:
			this->typeName = L"бв-4ЬЯ";
			break;
		case Type::ST4G:
			this->typeName = L"бв-4У";
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
