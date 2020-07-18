#include "RelayNmsh4_2400.h"

RelayNmsh4_2400::RelayNmsh4_2400(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШ4-2400";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НМ4-2400";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmsh4_2400::~RelayNmsh4_2400()
{

}

int RelayNmsh4_2400::setJumper(const wstring& jumper)
{
	if ((jumper == L"1-3") or (jumper == L"3-1"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"2-4") or (jumper == L"4-2"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"1-2") or (jumper == L"2-1"))
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

int RelayNmsh4_2400::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
