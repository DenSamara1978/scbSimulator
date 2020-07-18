#include "RelayNmpsh_900.h"

RelayNmpsh_900::RelayNmpsh_900(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"НМПШ-900";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmpsh_900::~RelayNmpsh_900()
{

}

int RelayNmpsh_900::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmpsh_900::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
