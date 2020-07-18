#include "SchemeEquipment.h"

SchemeEquipment::SchemeEquipment(const wstring& name) :
	SchemeObject(name)
{

}

SchemeEquipment::~SchemeEquipment()
{

}

int SchemeEquipment::setBlock(int id)
{
	this->block = id;
	return 0;
}

int SchemeEquipment::setLocation(const wstring& name)
{
	// Проверка возможности установки этого типа оборудования в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->location = name;
	return 0;
}

int SchemeEquipment::setPlacement(int id, Description::PlacementType placementTtype)
{
	this->placement = id;
	return (Description::checkCaseInPlacement(this->deviceCase, placementTtype)) ? 0 : -1;
}

bool SchemeEquipment::checkLocation(int block, int placement, const wstring& location) const
{
	if (location.empty() or (this->location != location))
		return false;
	else
		return (((block == -1) and (placement == this->placement)) or
			((placement == -1) and (block == this->block)));
}

const SchemeObject::ObjectType SchemeEquipment::getObjectType() const
{
	return SchemeObject::ObjectType::Equipment;
}

const wstring SchemeEquipment::getTypeName() const
{
	return this->typeName;
}
