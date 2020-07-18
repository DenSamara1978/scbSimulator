#include "RelayKmsh_450.h"

RelayKmsh_450::RelayKmsh_450(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"КМШ-450";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"КМ-450";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayKmsh_450::~RelayKmsh_450()
{

}

int RelayKmsh_450::setJumper(const wstring& jumper)
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

int RelayKmsh_450::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
