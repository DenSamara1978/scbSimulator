#include "RelayNmshm2_1500.h"

RelayNmshm2_1500::RelayNmshm2_1500(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"����2-1500";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayNmshm2_1500::~RelayNmshm2_1500()
{

}

int RelayNmshm2_1500::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
