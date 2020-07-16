#pragma once

namespace scb
{
	class MotorDriveDevice;
}

namespace track
{
	class Switch
	{
		bool workingRod; // ����������� ������� ����
		float pointPosition; // ��������� �������� 0.0f - ������� �����, 1.0f - ������� ������
		float leftObstacle; // ����� ����������� 0.0f - ����������� ���, 1.0f - ������ �����������
		float rightObstacle; // ����� ����������� 0.0f - ����������� ���, 1.0f - ������ �����������
		scb::MotorDriveDevice* drive;

	public:
		Switch();
		virtual ~Switch();

		void setDrive(scb::MotorDriveDevice* drive);

		void shiftWorkingRodLeft(float& position, bool& friction);
		void shiftWorkingRodRight(float& position, bool& friction);

		// ��������� ������ ��� �������� �������� �������� � ������
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