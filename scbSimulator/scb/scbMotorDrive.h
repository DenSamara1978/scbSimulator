#pragma once

#include "scbAbstractScheme.h"

class scbMotorDriveDevice;

class scbMotorDrive : public scbAbstractScheme
{
	unsigned long m_Status; // ������� ��������� ����, ��� ������������ � ����� ��
	unsigned long m_ControlStatus; // ������� ��������� ����, ��� ������ �� ���� ��

	scbMotorDriveDevice* m_DriveDevice;

public:
	scbMotorDrive ( const wstring& name );
	virtual ~scbMotorDrive ();

	scbMotorDriveDevice* GetDriveDevice () const;

	virtual void Init () override;
	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};

inline scbMotorDriveDevice* scbMotorDrive::GetDriveDevice () const
{
	return this->m_DriveDevice;
}
