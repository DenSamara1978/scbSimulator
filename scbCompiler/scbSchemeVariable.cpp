#include "scbSchemeVariable.h"

scbSchemeVariable::scbSchemeVariable (const wstring& name) :
	scbSchemeObject (name)
{

}

scbSchemeVariable::~scbSchemeVariable ()
{

}

int scbSchemeVariable::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}

const scbSchemeObject::ObjectType scbSchemeVariable::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Variable;
}
