#include "RelayPpr3_5000.h"

RelayPpr3_5000::RelayPpr3_5000(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"���3-5000";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::NR;
}

RelayPpr3_5000::~RelayPpr3_5000()
{

}

int RelayPpr3_5000::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
