#include "SchemeStatus.h"

SchemeStatus::SchemeStatus(const wstring& name) :
	SchemeObject(name),
	isDefaultSetting(false)
{

}

SchemeStatus::~SchemeStatus()
{

}

int SchemeStatus::fixDescription()
{
	// Нет ошибок завершения описания
	return 0;
}

int SchemeStatus::defaultSettingStatus()
{
	this->isDefaultSetting = true;
	return 0;
}

const SchemeObject::ObjectType SchemeStatus::getObjectType() const
{
	return SchemeObject::ObjectType::Status;
}
