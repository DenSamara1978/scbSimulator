#include <stdexcept>
#include "SchemeResistor.h"

SchemeResistor::SchemeResistor(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type),
	resistance(0)
{
	this->deviceCase = Description::DeviceCase::Resistor;
	switch (type)
	{
		case Type::PEV_25:
			this->typeName = L"ÏÝÂ-25";
			break;
		case Type::PEV_50:
			this->typeName = L"ÏÝÂ-50";
			break;
		case Type::MLT_1:
			this->typeName = L"ÌËÒ-1";
			break;
		case Type::MLT_2:
			this->typeName = L"ÌËÒ-2";
			break;
	}
}

int SchemeResistor::setNominal(const wstring& nominal)
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
	return (res == 0) ? 0 : 1;
}

int SchemeResistor::setUnitOfNominal(const wstring& unit)
{
	if (unit == L"Îì")
		return 0;
	else if (unit == L"êÎì")
	{
		this->resistance *= 1000;
		return 0;
	}
	else
		return 1;
}

int SchemeResistor::fixDescription()
{
	return (this->resistance == 0) ? 3 : 0;
}
