#include "RelayKdr1m_280.h"

RelayKdr1m_280::RelayKdr1m_280(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"���1�-280";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_280::~RelayKdr1m_280()
{

}

int RelayKdr1m_280::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
