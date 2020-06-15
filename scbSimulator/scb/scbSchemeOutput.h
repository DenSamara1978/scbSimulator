#pragma once

#include <string>
#include "scbAbstractSchemeDevice.h"

using std::wstring;

/*
	������������ ������ ����������, ������������ �� ���� ��������� �����,
	��������������, ���� ���� ����� ����� ���������� �� ���������� ������ -
	��� ���������� ����� �������������� � scbSchemeOutput ������� �����������
*/

class scbSchemeOutput : public scbAbstractSchemeDevice
{
	wstring* m_TargetSchemeName;
	scbAbstractScheme* m_TargetScheme;
	int m_Id;

public:
	scbSchemeOutput ( scbAbstractScheme* ownerShema, const wstring& name, int id );
	virtual ~scbSchemeOutput () override;

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;

	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ������-�������� ����� �������
};

