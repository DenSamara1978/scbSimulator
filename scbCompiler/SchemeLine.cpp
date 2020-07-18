#include "SchemeLine.h"

SchemeLine::SchemeLine(const wstring& name) :
	SchemeObject(name)
{

}

SchemeLine::~SchemeLine()
{

}

int SchemeLine::setDescriptor(const ComplexName& descriptor)
{
	this->object = descriptor;
	return 0;
}

int SchemeLine::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}

const SchemeObject::ObjectType SchemeLine::getObjectType() const
{
	return SchemeObject::ObjectType::Line;
}
