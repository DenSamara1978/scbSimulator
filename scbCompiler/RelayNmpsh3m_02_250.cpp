#include "RelayNmpsh3m_02_250.h"

RelayNmpsh3m_02_250::RelayNmpsh3m_02_250(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМПШ3М-0,2/250";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НМП3М-0,2/250";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmpsh3m_02_250::~RelayNmpsh3m_02_250()
{

}

int RelayNmpsh3m_02_250::setJumper(const wstring& jumper)
{
	if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmpsh3m_02_250::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
