#include "RelayNmpsh2_400.h"

RelayNmpsh2_400::RelayNmpsh2_400(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"НМПШ2-400";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmpsh2_400::~RelayNmpsh2_400()
{

}

int RelayNmpsh2_400::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmpsh2_400::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
