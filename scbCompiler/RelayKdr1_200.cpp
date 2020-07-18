#include "RelayKdr1_200.h"

RelayKdr1_200::RelayKdr1_200(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КДР1-200";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1_200::~RelayKdr1_200()
{

}

int RelayKdr1_200::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
