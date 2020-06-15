#pragma once

#include "scbAbstractScheme.h"

class scbConnectionPoint;

class scbConnectionPointScheme : public scbAbstractScheme
{
	unsigned long m_Status; // ������� ��������� ����, ��� ������������ � ����� ��
	unsigned long m_ControlStatus [2]; // ������� ��������� ����, ��� ������ �� ���� ��

	scbConnectionPoint* m_Point;

public:
	scbConnectionPointScheme ( const wstring& name, scbConnectionPoint::ConnectionType type );
	virtual ~scbConnectionPointScheme ();

	void SetStatus ( unsigned long status );

	virtual void Init () override;
	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};
