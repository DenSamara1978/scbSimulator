#include "scbSchemeStatus.h"

scbSchemeStatus::scbSchemeStatus (const wstring& name) :
	scbSchemeObject (name),
	m_IsDefaultSetting ( false )
{

}

scbSchemeStatus::~scbSchemeStatus ()
{

}

int scbSchemeStatus::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}

int scbSchemeStatus::DefaultSettingStatus ()
{
	this->m_IsDefaultSetting = true;
	return 0;
}

const scbSchemeObject::ObjectType scbSchemeStatus::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Status;
}
