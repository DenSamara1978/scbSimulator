#include "RelayNmshm1_560.h"

RelayNmshm1_560::RelayNmshm1_560(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"����1-560";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"���1-560";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmshm1_560::~RelayNmshm1_560()
{

}

int RelayNmshm1_560::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
