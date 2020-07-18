#include "RelayKdr1m_435.h"

RelayKdr1m_435::RelayKdr1m_435(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"КДР1М-435";
	this->isPlugable = false;
	this->deviceCase = Description::DeviceCase::KDR;
}

RelayKdr1m_435::~RelayKdr1m_435()
{

}

int RelayKdr1m_435::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
