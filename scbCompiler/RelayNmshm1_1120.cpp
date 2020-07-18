#include "RelayNmshm1_1120.h"

RelayNmshm1_1120::RelayNmshm1_1120(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШМ1-1120";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НММ1-1120";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmshm1_1120::~RelayNmshm1_1120()
{

}

int RelayNmshm1_1120::setJumper(const wstring& jumper)
{
	if ((jumper == L"1-2") or (jumper == L"2-1"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"3-4") or (jumper == L"4-3"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmshm1_1120::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
