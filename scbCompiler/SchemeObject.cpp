#include "SchemeObject.h"

SchemeObject::SchemeObject(const wstring& name) :
	name(name),
	block(-1),
	placement(-1),
	deviceCase(Description::DeviceCase::No)
{

}

SchemeObject::~SchemeObject()
{

}

int SchemeObject::setDescriptor(const ComplexName& descriptor)
{
	return -1;
}

int SchemeObject::setBlock(int id)
{
	return -1;
}

int SchemeObject::setLocation(const wstring& location)
{
	return -1;
}

int SchemeObject::setPlacement(int id, Description::PlacementType placementType)
{
	return -1;
}

int SchemeObject::setJumper(const wstring& jumper)
{
	return -1;
}

int SchemeObject::setOrder(int order)
{
	return -1;
}

int SchemeObject::setCable(const wstring& cable)
{
	return -1;
}

int SchemeObject::setContact(const wstring& contact)
{
	return -1;
}

int SchemeObject::setCount(int count)
{
	return -1;
}

int SchemeObject::setNominal(const wstring& nominal)
{
	return -1;
}

int SchemeObject::setUnitOfNominal(const wstring& unit)
{
	return -1;
}

int SchemeObject::setPowerClass(const wstring& power_class)
{
	return -1;
}

int SchemeObject::setRequirement(int req)
{
	return -1;
}

int SchemeObject::setRequirementFrom(int from)
{
	return -1;
}

int SchemeObject::setRequirementTo(int to)
{
	return -1;
}

int SchemeObject::defaultSettingStatus()
{
	return -1;
}

int SchemeObject::setTypeName(const wstring& name)
{
	return -1;
}

const wstring SchemeObject::getTypeName() const
{
	return L"";
}

bool SchemeObject::checkLocation(int block, int placement, const wstring& location) const
{
	return true;
}
