#include "RelayKdr1_280.h"

RelayKdr1_280::RelayKdr1_280(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КДР1-280";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1_280::~RelayKdr1_280()
{

}

int RelayKdr1_280::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
