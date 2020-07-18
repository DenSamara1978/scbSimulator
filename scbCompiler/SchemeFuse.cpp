#include <stdexcept>
#include "SchemeFuse.h"

SchemeFuse::SchemeFuse(const wstring& name) :
	SchemeEquipment(name),
	maxCurrent(0.0f),
	powerClass(PowerClass::No)
{
	this->deviceCase = Description::DeviceCase::Fuse;
	this->typeName = L"Ïðåäîõðàíèòåëü";
}

int SchemeFuse::setNominal(const wstring& nominal)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		this->maxCurrent = std::stof(nominal, &pos);
		if (pos < nominal.length())
		{
			this->maxCurrent = 0.0f;
			res = -1;
		}
	}
	catch (std::invalid_argument)
	{
		this->maxCurrent = 0.0f;
		res = -1;
	}
	return (res == 0) ? 0 : 1;
}

int SchemeFuse::setUnitOfNominal(const wstring& unit)
{
	return (unit == L"À") ? 0 : 1;
}

int SchemeFuse::setPowerClass(const wstring& powerClass)
{
	if (powerClass == L"ÐÏÁ")
		this->powerClass = PowerClass::RPB;
	else if (powerClass == L"ÏÕÊÑ")
		this->powerClass = PowerClass::PHKS;
	else if (powerClass == L"ÏÕÑ")
		this->powerClass = PowerClass::PHS;
	else if (powerClass == L"ÎÕÑ")
		this->powerClass = PowerClass::OHS;
	else if (powerClass == L"ÏÕË")
		this->powerClass = PowerClass::PHL;
	else if (powerClass == L"ÎÕË")
		this->powerClass = PowerClass::OHL;
	else if (powerClass == L"Ï")
		this->powerClass = PowerClass::P;
	else if (powerClass == L"Ì")
		this->powerClass = PowerClass::M;
	else if (powerClass == L"ÑÕ")
		this->powerClass = PowerClass::SH;
	else if (powerClass == L"ÊÑÕ")
		this->powerClass = PowerClass::KSH;
	else if (powerClass == L"ÑÕÌ")
		this->powerClass = PowerClass::SHM;
	else
		return 1;

	return 0;
}

int SchemeFuse::fixDescription()
{
	if (this->maxCurrent == 0)
		return 3;
	else if (this->powerClass == PowerClass::No)
		return 4;
	else
		return 0;
}
