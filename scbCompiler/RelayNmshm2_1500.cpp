#include "RelayNmshm2_1500.h"

RelayNmshm2_1500::RelayNmshm2_1500(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"НМШМ2-1500";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmshm2_1500::~RelayNmshm2_1500()
{

}

int RelayNmshm2_1500::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
