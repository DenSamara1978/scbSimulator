#include "RelayNmshm2_3000.h"

RelayNmshm2_3000::RelayNmshm2_3000(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"НМШМ2-3000";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmshm2_3000::~RelayNmshm2_3000()
{

}

int RelayNmshm2_3000::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmshm2_3000::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
