#include "SchemeBlock.h"
#include "Description.h"

SchemeBlock::SchemeBlock(const wstring& name) :
	SchemeObject(name)
{

}

SchemeBlock::~SchemeBlock()
{

}

int SchemeBlock::setPlacement(int id, Description::PlacementType placementType)
{
	this->placement = id;
	return (Description::checkCaseInPlacement(this->deviceCase, placementType)) ? 0 : -1;
}

int SchemeBlock::setLocation(const wstring& location)
{
	// Проверка возможности установки этого типа блока в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->location = location;
	return 0;
}

int SchemeBlock::setTypeName(const wstring& name)
{
	auto [_case, id] = Description::getBlockInfo(name);
	this->typeId = id;
	this->deviceCase = _case;
	if (id != -1)
		return 0;
	else
		return -1;
}
/*
const wstring scbSchemeBlock::GetTypeName () const
{
	return this->m_TypeName;
}*/

int SchemeBlock::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}

bool SchemeBlock::checkLocation(int block, int placement, const wstring& location) const
{
	return ((placement == this->placement) and !location.empty() and (location == this->location));
}

const SchemeObject::ObjectType SchemeBlock::getObjectType() const
{
	return SchemeObject::ObjectType::Block;
}
