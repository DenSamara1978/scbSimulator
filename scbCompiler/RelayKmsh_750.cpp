#include "RelayKmsh_750.h"

RelayKmsh_750::RelayKmsh_750(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КМШ-750";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayKmsh_750::~RelayKmsh_750()
{

}

int RelayKmsh_750::setJumper(const wstring& jumper)
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

int RelayKmsh_750::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
