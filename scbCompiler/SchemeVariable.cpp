#include "SchemeVariable.h"

SchemeVariable::SchemeVariable(const wstring& name) :
	SchemeObject(name)
{

}

SchemeVariable::~SchemeVariable()
{

}

int SchemeVariable::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}

const SchemeObject::ObjectType SchemeVariable::getObjectType() const
{
	return SchemeObject::ObjectType::Variable;
}
