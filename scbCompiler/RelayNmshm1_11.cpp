#include "RelayNmshm1_11.h"

RelayNmshm1_11::RelayNmshm1_11(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШМ1-11";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НММ1-11";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmshm1_11::~RelayNmshm1_11()
{

}

int RelayNmshm1_11::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
