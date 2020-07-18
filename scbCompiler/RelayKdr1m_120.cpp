#include "RelayKdr1m_120.h"

RelayKdr1m_120::RelayKdr1m_120(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КДР1М-120";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_120::~RelayKdr1m_120()
{

}

int RelayKdr1m_120::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
