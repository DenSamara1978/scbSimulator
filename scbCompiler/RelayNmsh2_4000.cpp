#include "RelayNmsh2_4000.h"

RelayNmsh2_4000::RelayNmsh2_4000(const wstring& name, bool plugable) :
	requirementFrom(-1),
	requirementTo(-1),
	requirementId(-1),
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"НМШ2-4000";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"НМ2-4000";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmsh2_4000::~RelayNmsh2_4000()
{

}

int RelayNmsh2_4000::setJumper(const wstring& jumper)
{
	if ((jumper == L"1-2") or (jumper == L"2-1"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"3-4") or (jumper == L"4-3"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"1-3") or (jumper == L"3-1"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"2-4") or (jumper == L"4-2"))
	{
		// TODO 
		return 0;
	}
	else if ((jumper == L"2-3") or (jumper == L"3-2"))
	{
		// TODO 
		return 0;
	}
	else
		return 1;
}

int RelayNmsh2_4000::setRequirement(int req)
{
	this->requirementId = req;
	return 0;
}

int RelayNmsh2_4000::setRequirementFrom(int from)
{
	this->requirementFrom = from;
	return 0;
}

int RelayNmsh2_4000::setRequirementTo(int to)
{
	this->requirementTo = to;
	return (this->requirementTo - this->requirementFrom >= 0) ? 0 : 1;
}

int RelayNmsh2_4000::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}
