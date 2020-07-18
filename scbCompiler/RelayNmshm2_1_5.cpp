#include "RelayNmshm2_1_5.h"

RelayNmshm2_1_5::RelayNmshm2_1_5(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШМ2-1,5";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НММ2-1,5";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmshm2_1_5::~RelayNmshm2_1_5()
{

}

int RelayNmshm2_1_5::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
