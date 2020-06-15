#pragma once

class scbMotorDriveDevice;

class trackSwitch
{
	bool m_WorkingRod; // »справность рабочей т€ги
	float m_PointPosition; // ѕоложение остр€ков 0.0f - крайнее левое, 1.0f - крайнее правое
	float m_LeftObstacle; // Ћевое преп€тствие 0.0f - преп€тстви€ нет, 1.0f - полное преп€тствие
	float m_RightObstacle; // Ћевое преп€тствие 0.0f - преп€тстви€ нет, 1.0f - полное преп€тствие
	scbMotorDriveDevice* m_Drive;

public:
	trackSwitch ();
	virtual ~trackSwitch ();

	void SetDrive ( scbMotorDriveDevice* drive );

	void ShiftWorkingRodLeft ( float& position, bool& friction );
	void ShiftWorkingRodRight ( float& position, bool& friction );

	// ¬ременные методы дл€ изучени€ недовода остр€ков и взреза
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
