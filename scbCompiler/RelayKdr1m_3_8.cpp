#include "RelayKdr1m_3_8.h"

RelayKdr1m_3_8::RelayKdr1m_3_8(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КДР1М-3,8";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_3_8::~RelayKdr1m_3_8()
{

}

int RelayKdr1m_3_8::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
