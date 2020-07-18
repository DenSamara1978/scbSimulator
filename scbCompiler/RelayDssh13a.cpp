#include "RelayDssh13a.h"

RelayDssh13a::RelayDssh13a(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"ДСШ-13А";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::DSSH;
}

RelayDssh13a::~RelayDssh13a()
{

}

int RelayDssh13a::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
