#include "SchemeDiode.h"

SchemeDiode::SchemeDiode(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type)
{
	this->deviceCase = Description::DeviceCase::Diode;
	switch (type)
	{
		case Type::D226B:
			this->typeName = L"Ä226Á";
			break;
	}
}

int SchemeDiode::fixDescription()
{
	return 0;
}
