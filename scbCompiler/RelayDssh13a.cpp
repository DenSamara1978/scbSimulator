#include "RelayDssh13a.h"

RelayDssh13a::RelayDssh13a(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"���-13�";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::DSSH;
}

RelayDssh13a::~RelayDssh13a()
{

}

int RelayDssh13a::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
