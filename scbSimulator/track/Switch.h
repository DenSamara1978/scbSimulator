#pragma once

namespace scb
{
	class MotorDriveDevice;
}

namespace track
{
	class Switch
	{
		bool workingRod; // »справность рабочей т€ги
		float pointPosition; // ѕоложение остр€ков 0.0f - крайнее левое, 1.0f - крайнее правое
		float leftObstacle; // Ћевое преп€тствие 0.0f - преп€тстви€ нет, 1.0f - полное преп€тствие
		float rightObstacle; // Ћевое преп€тствие 0.0f - преп€тстви€ нет, 1.0f - полное преп€тствие
		scb::MotorDriveDevice* drive;

	public:
		Switch();
		virtual ~Switch();

		void setDrive(scb::MotorDriveDevice* drive);

		void shiftWorkingRodLeft(float& position, bool& friction);
		void shiftWorkingRodRight(float& position, bool& friction);

		// ¬ременные методы дл€ изучени€ недовода остр€ков и взреза
		void increaseLeftObstacle();
		void decreaseLeftObstacle();
		void increaseRightObstacle();
		void decreaseRightObstacle();
		float getLeftObstacle() const;
		float getRightObstacle() const;
		//
	};

	inline void Switch::setDrive(scb::MotorDriveDevice* drive)
	{
		this->drive = drive;
	}

	inline float Switch::getLeftObstacle() const
	{
		return this->leftObstacle;
	}

	inline float Switch::getRightObstacle() const
	{
		return this->rightObstacle;
	}
}