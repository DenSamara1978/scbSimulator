#pragma once

#include "scbAbstractSchemeDevice.h"
#include "scbPultTablo.h"

class scbPultTabloActiveDevice : public scbAbstractSchemeDevice
{
public:
	scbPultTabloActiveDevice ( scbAbstractScheme* ownerScheme );
	virtual ~scbPultTabloActiveDevice () override;

	// ������, ���������� ������� ������� �� ���������� ��������� ����������
	virtual void Press (); // �������
	virtual void Release (); // ����������
	virtual void TurnCW (); // ������� �� ������� �������
	virtual void TurnCCW (); // ������� ������ ������� �������
	virtual void Unseal (); // ������ ������ � ��������� ������������� �����
	virtual void Seal (); // ��������� ������������� ����� � ��������� ������
	virtual void Remove (); // ���������� �����-�����
	virtual void Insert (); // ������� �����-�����

	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ������-�������� ����� �������
};

