#include "RelayKdr1m_120.h"

RelayKdr1m_120::RelayKdr1m_120(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"���1�-120";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_120::~RelayKdr1m_120()
{

}

int RelayKdr1m_120::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
