#include "RelayNmshm1_1000_560.h"

RelayNmshm1_1000_560::RelayNmshm1_1000_560(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"����1-1000/560";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"���1-1000/560";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmshm1_1000_560::~RelayNmshm1_1000_560()
{

}

int RelayNmshm1_1000_560::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
