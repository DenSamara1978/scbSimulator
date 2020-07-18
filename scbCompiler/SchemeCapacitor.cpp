#include <stdexcept>
#include "SchemeCapacitor.h"

SchemeCapacitor::SchemeCapacitor(const wstring& name, Type type) :
	SchemeEquipment(name),
	type(type),
	capacity(0)
{
	this->deviceCase = Description::DeviceCase::Capacitor;
	switch (type)
	{
		case Type::KEG_1_30V:
			this->typeName = L"ÊÝÃ-1-30Â";
			break;
		case Type::KEG_2_30V:
			this->typeName = L"ÊÝÃ-2-30Â";
			break;
		case Type::MBGCH_1_1_250V:
			this->typeName = L"ÌÁÃ×-1-1-250Â";
			break;
		case Type::MBGCH_1_2A_250V:
			this->typeName = L"ÌÁÃ×-1-2À-250Â";
			break;
		case Type::EGC_30V:
			this->typeName = L"ÝÃÖ-30Â";
			break;
	}
}

int SchemeCapacitor::setNominal(const wstring& nominal)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		this->capacity = std::stoi(nominal, &pos);
		if (pos < nominal.length())
		{
			this->capacity = 0;
			res = -1;
		}
	}
	catch (std::invalid_argument)
	{
		this->capacity = 0;
		res = -1;
	}
	return (res == 0) ? 0 : 1;
}

int SchemeCapacitor::setUnitOfNominal(const wstring& unit)
{
	return (unit == L"ìêÔ") ? 0 : 1;
}

int SchemeCapacitor::fixDescription()
{
	return (this->capacity == 0) ? 3 : 0;
}
