#include <stdexcept>
#include "SchemeRheostat.h"

SchemeRheostat::SchemeRheostat(const wstring& name) :
	SchemeEquipment(name),
	resistance(0)
{
	this->deviceCase = Description::DeviceCase::Rheostat;
	this->typeName = L"–еостат";
}

int SchemeRheostat::setNominal(const wstring& nominal)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		this->resistance = std::stoi(nominal, &pos);
		if (pos < nominal.length())
		{
			this->resistance = 0;
			res = -1;
		}
	}
	catch (std::invalid_argument)
	{
		this->resistance = 0;
		res = -1;
	}
	return (res == 0) ? 0 : -1;
}

int SchemeRheostat::setUnitOfNominal(const wstring& unit)
{
	if (unit == L"ќм")
		return 0;
	else if (unit == L"кќм")
	{
		this->resistance *= 1000;
		return 0;
	}
	else
		return 1;
}

int SchemeRheostat::fixDescription()
{
	return (this->resistance == 0) ? 3 : 0;
}