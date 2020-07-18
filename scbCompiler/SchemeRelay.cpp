#include "SchemeRelay.h"

SchemeRelay::SchemeRelay(const wstring& name) :
	SchemeObject(name)
{

}

SchemeRelay::~SchemeRelay()
{

}

int SchemeRelay::setBlock(int id)
{
	this->block = id;
	return 0;
}

int SchemeRelay::setLocation(const wstring& name)
{
	// Проверка возможности установки этого типа реле в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->location = name;
	return 0;
}

int SchemeRelay::setPlacement(int id, Description::PlacementType pl_type)
{
	this->placement = id;
	return (Description::checkCaseInPlacement(this->deviceCase, pl_type)) ? 0 : -1;
}

const SchemeObject::ObjectType SchemeRelay::getObjectType() const
{
	return SchemeObject::ObjectType::Relay;
}

const wstring SchemeRelay::getTypeName() const
{
	return this->typeName;
}

bool SchemeRelay::checkLocation(int block, int placement, const wstring& location) const
{
	if (location.empty() or (this->location != location))
		return false;
	else
		return (((block == -1) and (placement == this->placement)) or
			((placement == -1) and (block == this->block)));
}
