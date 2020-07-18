#include "RelayPmpush_150_150.h"

RelayPmpush_150_150::RelayPmpush_150_150(const wstring& name, bool plugable) :
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"ПМПУШ-150/150";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"ПМПУ-150/150";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayPmpush_150_150::~RelayPmpush_150_150()
{

}

int RelayPmpush_150_150::setJumper(const wstring& jumper)
{
	if ((jumper == L"1-3") or (jumper == L"3-1"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"3-2") or (jumper == L"4-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayPmpush_150_150::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
