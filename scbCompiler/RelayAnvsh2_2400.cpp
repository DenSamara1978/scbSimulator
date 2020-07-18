#include "RelayAnvsh2_2400.h"

RelayAnvsh2_2400::RelayAnvsh2_2400(const wstring& name) :
	SchemeRelay(name)
{
	this->typeName = L"АНВШ2-2400";
	this->isPlugable = true;
	this->deviceCase = Description::DeviceCase::NMSH;
}

RelayAnvsh2_2400::~RelayAnvsh2_2400()
{

}

int RelayAnvsh2_2400::setJumper(const wstring& jumper)
{
	if ((jumper == L"21-41") or (jumper == L"41-21"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"21-42") or (jumper == L"42-21"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"41-42") or (jumper == L"42-41"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"41-61") or (jumper == L"61-41"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"61-62") or (jumper == L"62-61"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"61-81") or (jumper == L"81-61"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"62-81") or (jumper == L"81-62"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayAnvsh2_2400::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
