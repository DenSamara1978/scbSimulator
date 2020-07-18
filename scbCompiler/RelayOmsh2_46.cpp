#include "RelayOmsh2_46.h"

RelayOmsh2_46::RelayOmsh2_46(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"ОМШ2-46";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"ОМ2-46";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayOmsh2_46::~RelayOmsh2_46()
{

}

int RelayOmsh2_46::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
