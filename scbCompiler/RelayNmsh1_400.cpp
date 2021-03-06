#include "RelayNmsh1_400.h"

RelayNmsh1_400::RelayNmsh1_400(const wstring& name, bool plugable) :
	requirementFrom(-1),
	requirementTo(-1),
	requirementId(-1),
	SchemeRelay(name)
{
	if (this->isPlugable = plugable)
	{
		this->typeName = L"���1-400";
		this->deviceCase = Description::DeviceCase::NMSH;
	}
	else
	{
		this->typeName = L"��1-400";
		this->deviceCase = Description::DeviceCase::NM;
	}
}

RelayNmsh1_400::~RelayNmsh1_400()
{

}

int RelayNmsh1_400::setJumper(const wstring& jumper)
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

int RelayNmsh1_400::setRequirement(int req)
{
	this->requirementId = req;
	return 0;
}

int RelayNmsh1_400::setRequirementFrom(int from)
{
	this->requirementFrom = from;
	return 0;
}

int RelayNmsh1_400::setRequirementTo(int to)
{
	this->requirementTo = to;
	return (this->requirementTo - this->requirementFrom >= 0) ? 0 : 1;
}

int RelayNmsh1_400::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}
