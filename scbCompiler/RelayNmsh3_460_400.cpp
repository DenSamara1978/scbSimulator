#include "RelayNmsh3_460_400.h"

RelayNmsh3_460_400::RelayNmsh3_460_400(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"НМШ3-460/400";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmsh3_460_400::~RelayNmsh3_460_400()
{

}

int RelayNmsh3_460_400::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmsh3_460_400::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
