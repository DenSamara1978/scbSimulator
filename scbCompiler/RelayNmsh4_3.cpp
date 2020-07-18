#include "RelayNmsh4_3.h"

RelayNmsh4_3::RelayNmsh4_3(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШ4-3";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НМ4-3";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmsh4_3::~RelayNmsh4_3()
{

}

int RelayNmsh4_3::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmsh4_3::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
