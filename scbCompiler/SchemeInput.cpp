#include "SchemeInput.h"

SchemeInput::SchemeInput(const wstring& name) :
	SchemeObject(name)
{

}

SchemeInput::~SchemeInput()
{

}

int SchemeInput::fixDescription()
{
	// ��� ������ ���������� ��������
	return 0;
}

const SchemeObject::ObjectType SchemeInput::getObjectType() const
{
	return SchemeObject::ObjectType::Input;
}
