#pragma once

#include "scbAbstractSchemeDevice.h"

class trackSwitch;

class scbMotorDriveDevice : public scbAbstractSchemeDevice
{
	float m_FrostAmount1; // ���������� ���� �� ������ ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
	float m_FrostAmount2; // ���������� ���� �� ������ ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
	float m_FrostAmount3; // ���������� ���� �� ������� ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
	float m_FrostAmount4; // ���������� ���� �� ��������� ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )

	float m_Temperature; // ������� �����������

	static constexpr float m_cFrostSlewRate = 1.0f; // ���������� �������� ���������� ����, ��. � ���.-����.������� 
	static constexpr float m_cFrostMeltingRate = 1.0f; // ��������� �������� ������ ����, ��. � ���.-����.�������
	static constexpr float m_cFrostContactLevel = 0.6f; // ������� ����, ���� �������� ����������������� �� ��������� ���� ����

	static constexpr float m_cLockSwitchLevel = 0.2f; // ������� ������������ ��
	static constexpr float m_cAutoSwitchLevel = 0.5f; // ������� ������������ ������������������

	static constexpr float m_cSwivelCamFallingTime = 10.0f; // ����� ������������ ������� ����������� ������� � ��� �����, ��
	static constexpr float m_cFlapTime = 500.0f; // ����� ��������/��������� ���������� ��������, ��
	static constexpr float m_cMotorRatePerSecondWork = 10.0f; // �������� �������� ����� ��������� � ������� ������, ��/�
	static constexpr float m_cMotorRatePerSecondFriction = 5.0f; // �������� �������� ����� ��������� ��� �������, ��/�
	static constexpr float m_cGearRatio = 10.0f; // ������������ ����� ���������
	static constexpr float m_cGapSector = 16.0f; // ������ ������ ����� ��������� ��������� � ������, ��������
	static constexpr float m_cWorkingSector = 280.0f; // ������ �������� �������� ���������, ��������

	bool m_Friction; // ������� �������
	float m_LeftSwivelCamPosition; // ��������� ������ ����������� �������, 0 - ����� � ���� �����, 1 - ����� �� ����������� �����
	float m_RightSwivelCamPosition; // ��������� ������� ����������� �������, 0 - ����� � ���� �����, 1 - ����� �� ����������� �����
	float m_AutoSwitchGap; // ����� ����� ��������� ��������� � ������ ����������������� 0 - ����� � ����� �����, +16 - ����� � ������ �����
	float m_MotorPhase; // ���� ��������� ����� ������, ������
	float m_ReductorPhase; // ���� ��������� ������� �������� �����������������, ������ ( �� 140 ����� ������ �� -140 ����� ����� )
	float m_FlapPosition; // ��������� ���������� �������� ( 0.0f - �������, 1.0f - ��������� )
	float m_GatePosition; // ��������� ������ ( 0.0f - ������� �����, 1.0f - ������� ������ )
	float m_ControlLinePosition; // ��������� ����������� ������ ( 0.0f - ������� �����, 1.0f - ������� ������ )
	float m_AutoSwitch12Position; // ��������� ������ ����������������� ( -1.0f - ������� ����� ( ������� ), 0.0f - ������� , 1.0f - ������� ������ ( ����������� ))
	float m_AutoSwitch34Position; // ��������� ������� ����������������� ( -1.0f - ������� ������ ( ������� ), 0.0f - ������� , 1.0f - ������� ����� ( ����������� ))

	/* ��������� ���������� �������� � �������������� ��������
	0 - �������� �������, ������� �������
	1 - �������� ����������, ������� �������
	2 - �������� ����������, ������� ���������
	3 - �������� �������, ������� ���������
	4 - �������� �����������, ������� ���������
	5 - �������� �����������, ������� �������
	*/
	int m_FlapStatus;

	/* ��������� ������ ���������
	0 - �����
	1 - ������ ������
	2 - ������� ������
	3 - ������ �����
	4 - ������� �����
	*/
	int m_MotorStatus;
	bool m_ControlLinePresence;
	bool m_IsGateClose;

	bool m_LeftSwivelCamFalling; // ����������� ��������� ������ ����������� ������� � �������� ��� �����
	bool m_RightSwivelCamFalling; // ����������� ��������� ������� ����������� ������� � �������� ��� �����
								 
	static constexpr int m_cAutoSwitch12ControlBit = 0;
	static constexpr int m_cAutoSwitch12PowerBit = 1;
	static constexpr int m_cAutoSwitch34ControlBit = 2;
	static constexpr int m_cAutoSwitch34PowerBit = 3;
	static constexpr int m_cWorkingAmperageBit = 4;
	static constexpr int m_cFrictionAmperageBit = 5;
	static constexpr int m_cAutoSwitch1FrostBit = 6;
	static constexpr int m_cAutoSwitch2FrostBit = 7;
	static constexpr int m_cAutoSwitch3FrostBit = 8;
	static constexpr int m_cAutoSwitch4FrostBit = 9;
	static constexpr int m_cLockSwitchBit = 10;

	unsigned long long m_TimeStamp;

	trackSwitch* m_TrackSwitch;

	void RecalculateAutoSwitch ();

public:
	scbMotorDriveDevice ( scbAbstractScheme* ownerShema );
	virtual ~scbMotorDriveDevice ();

	void SetSwitch ( trackSwitch* point );

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ����������-��������

	bool ShiftGate ( float position );
	void ShiftControlRod ( float position );

	void FlapDown ();
	void FlapUp ();
	void LeftWedgeInsert ();
	void LeftWedgeRemove ();
	void RightWedgeInsert ();
	void RightWedgeRemove ();

	float GetMotorPhase () const;
	float GetReductorPhase () const;
	float GetFlapPosition () const;
	float GetGatePosition () const;
	float GetControlLinePosition () const;
	float GetLeftSwivelCamPosition () const;
	float GetRightSwivelCamPosition () const;
	float GetAutoSwitch12Position () const;
	float GetAutoSwitch34Position () const;
	float GetLeftWedgePosition () const;
	float GetRightWedgePosition () const;
};

inline float scbMotorDriveDevice::GetMotorPhase () const
{
	return this->m_MotorPhase;
}

inline float scbMotorDriveDevice::GetReductorPhase () const
{
	return this->m_ReductorPhase;
}

inline float scbMotorDriveDevice::GetFlapPosition () const
{
	return this->m_FlapPosition;
}

inline float scbMotorDriveDevice::GetGatePosition () const
{
	return this->m_GatePosition;
}

inline float scbMotorDriveDevice::GetControlLinePosition () const
{
	return this->m_ControlLinePosition;
}

inline float scbMotorDriveDevice::GetAutoSwitch12Position () const
{
	return this->m_AutoSwitch12Position;
}

inline float scbMotorDriveDevice::GetAutoSwitch34Position () const
{
	return this->m_AutoSwitch34Position;

}

inline float scbMotorDriveDevice::GetLeftSwivelCamPosition () const
{
	return this->m_LeftSwivelCamPosition;
}

inline float scbMotorDriveDevice::GetRightSwivelCamPosition () const
{
	return this->m_RightSwivelCamPosition;
}
