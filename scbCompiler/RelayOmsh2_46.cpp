#include "RelayOmsh2_46.h"

RelayOmsh2_46::RelayOmsh2_46(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"���2-46";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"��2-46";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayOmsh2_46::~RelayOmsh2_46()
{

}

int RelayOmsh2_46::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
