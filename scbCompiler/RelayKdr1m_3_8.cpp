#include "RelayKdr1m_3_8.h"

RelayKdr1m_3_8::RelayKdr1m_3_8(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"���1�-3,8";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_3_8::~RelayKdr1m_3_8()
{

}

int RelayKdr1m_3_8::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
