#include "SchemeOutput.h"

SchemeOutput::SchemeOutput(const wstring& name, Type type) :
	SchemeObject(name),
	type(type)
{
}

SchemeOutput::~SchemeOutput()
{
}

int SchemeOutput::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}

const SchemeObject::ObjectType SchemeOutput::getObjectType() const
{
	return SchemeObject::ObjectType::Output;
}
