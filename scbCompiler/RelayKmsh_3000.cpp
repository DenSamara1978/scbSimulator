#include "RelayKmsh_3000.h"

RelayKmsh_3000::RelayKmsh_3000(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"КМШ-3000";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"КМ-3000";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayKmsh_3000::~RelayKmsh_3000()
{

}

int RelayKmsh_3000::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") || (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayKmsh_3000::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
