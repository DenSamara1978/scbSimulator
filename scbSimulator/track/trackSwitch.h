#pragma once

class scbMotorDriveDevice;

class trackSwitch
{
	bool m_WorkingRod; // ����������� ������� ����
	float m_PointPosition; // ��������� �������� 0.0f - ������� �����, 1.0f - ������� ������
	float m_LeftObstacle; // ����� ����������� 0.0f - ����������� ���, 1.0f - ������ �����������
	float m_RightObstacle; // ����� ����������� 0.0f - ����������� ���, 1.0f - ������ �����������
	scbMotorDriveDevice* m_Drive;

public:
	trackSwitch ();
	virtual ~trackSwitch ();

	void SetDrive ( scbMotorDriveDevice* drive );

	void ShiftWorkingRodLeft ( float& position, bool& friction );
	void ShiftWorkingRodRight ( float& position, bool& friction );

	// ��������� ������ ��� �������� �������� �������� � ������
	void IncreaseLeftObstacle ();
	void DecreaseLeftObstacle ();
	void IncreaseRightObstacle ();
	void DecreaseRightObstacle ();
	float GetLeftObstacle () const;
	float GetRightObstacle () const;
	//
};

inline void trackSwitch::SetDrive ( scbMotorDriveDevice* drive )
{
	this->m_Drive = drive;
}

inline float trackSwitch::GetLeftObstacle () const
{
	return this->m_LeftObstacle;
}

inline float trackSwitch::GetRightObstacle () const
{
	return this->m_RightObstacle;
}
