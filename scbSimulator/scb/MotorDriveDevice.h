#pragma once

#include "AbstractSchemeDevice.h"

namespace track
{
	class Switch;
}

namespace scb
{

	class MotorDriveDevice : public AbstractSchemeDevice
	{
	public:
		MotorDriveDevice(AbstractScheme* ownerShema);
		virtual ~MotorDriveDevice();

		void setSwitch(track::Switch* point);

		virtual void initialize() override;
		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // ���������� ����������-��������

		bool shiftGate(float position);
		void shiftControlRod(float position);

		void flapDown();
		void flapUp();
		void leftWedgeInsert();
		void leftWedgeRemove();
		void rightWedgeInsert();
		void rightWedgeRemove();

		float getMotorPhase() const;
		float getReductorPhase() const;
		float getFlapPosition() const;
		float getGatePosition() const;
		float getControlLinePosition() const;
		float getLeftSwivelCamPosition() const;
		float getRightSwivelCamPosition() const;
		float getAutoSwitch12Position() const;
		float getAutoSwitch34Position() const;
		float getLeftWedgePosition() const;
		float getRightWedgePosition() const;

	private:
		void recalculateAutoSwitch();

		float frostAmount1; // ���������� ���� �� ������ ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
		float frostAmount2; // ���������� ���� �� ������ ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
		float frostAmount3; // ���������� ���� �� ������� ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )
		float frostAmount4; // ���������� ���� �� ��������� ������ ����������������� ( 0.0f - ��� ������, 1.0f - ��������� ������� )

		float temperature; // ������� �����������

		static constexpr float frostSlewRate = 1.0f; // ���������� �������� ���������� ����, ��. � ���.-����.������� 
		static constexpr float frostMeltingRate = 1.0f; // ��������� �������� ������ ����, ��. � ���.-����.�������
		static constexpr float frostContactLevel = 0.6f; // ������� ����, ���� �������� ����������������� �� ��������� ���� ����

		static constexpr float lockSwitchLevel = 0.2f; // ������� ������������ ��
		static constexpr float autoSwitchLevel = 0.5f; // ������� ������������ ������������������

		static constexpr float swivelCamFallingTime = 10.0f; // ����� ������������ ������� ����������� ������� � ��� �����, ��
		static constexpr float flapTime = 500.0f; // ����� ��������/��������� ���������� ��������, ��
		static constexpr float motorRatePerSecondWork = 10.0f; // �������� �������� ����� ��������� � ������� ������, ��/�
		static constexpr float motorRatePerSecondFriction = 5.0f; // �������� �������� ����� ��������� ��� �������, ��/�
		static constexpr float gearRatio = 10.0f; // ������������ ����� ���������
		static constexpr float gapSector = 16.0f; // ������ ������ ����� ��������� ��������� � ������, ��������
		static constexpr float workingSector = 280.0f; // ������ �������� �������� ���������, ��������

		bool friction; // ������� �������
		float leftSwivelCamPosition; // ��������� ������ ����������� �������, 0 - ����� � ���� �����, 1 - ����� �� ����������� �����
		float rightSwivelCamPosition; // ��������� ������� ����������� �������, 0 - ����� � ���� �����, 1 - ����� �� ����������� �����
		float autoSwitchGap; // ����� ����� ��������� ��������� � ������ ����������������� 0 - ����� � ����� �����, +16 - ����� � ������ �����
		float motorPhase; // ���� ��������� ����� ������, ������
		float reductorPhase; // ���� ��������� ������� �������� �����������������, ������ ( �� 140 ����� ������ �� -140 ����� ����� )
		float flapPosition; // ��������� ���������� �������� ( 0.0f - �������, 1.0f - ��������� )
		float gatePosition; // ��������� ������ ( 0.0f - ������� �����, 1.0f - ������� ������ )
		float controlLinePosition; // ��������� ����������� ������ ( 0.0f - ������� �����, 1.0f - ������� ������ )
		float autoSwitch12Position; // ��������� ������ ����������������� ( -1.0f - ������� ����� ( ������� ), 0.0f - ������� , 1.0f - ������� ������ ( ����������� ))
		float autoSwitch34Position; // ��������� ������� ����������������� ( -1.0f - ������� ������ ( ������� ), 0.0f - ������� , 1.0f - ������� ����� ( ����������� ))

		/* ��������� ���������� �������� � �������������� ��������
		0 - �������� �������, ������� �������
		1 - �������� ����������, ������� �������
		2 - �������� ����������, ������� ���������
		3 - �������� �������, ������� ���������
		4 - �������� �����������, ������� ���������
		5 - �������� �����������, ������� �������
		*/
		int flapStatus;

		/* ��������� ������ ���������
		0 - �����
		1 - ������ ������
		2 - ������� ������
		3 - ������ �����
		4 - ������� �����
		*/
		int motorStatus;
		bool controlLinePresence;
		bool isGateClose;

		bool leftSwivelCamFalling; // ����������� ��������� ������ ����������� ������� � �������� ��� �����
		bool rightSwivelCamFalling; // ����������� ��������� ������� ����������� ������� � �������� ��� �����

		static constexpr int autoSwitch12ControlBit = 0;
		static constexpr int autoSwitch12PowerBit = 1;
		static constexpr int autoSwitch34ControlBit = 2;
		static constexpr int autoSwitch34PowerBit = 3;
		static constexpr int workingAmperageBit = 4;
		static constexpr int frictionAmperageBit = 5;
		static constexpr int autoSwitch1FrostBit = 6;
		static constexpr int autoSwitch2FrostBit = 7;
		static constexpr int autoSwitch3FrostBit = 8;
		static constexpr int autoSwitch4FrostBit = 9;
		static constexpr int lockSwitchBit = 10;

		unsigned long long timeStamp;

		track::Switch* trackSwitch;
	};

	inline float MotorDriveDevice::getMotorPhase() const
	{
		return this->motorPhase;
	}

	inline float MotorDriveDevice::getReductorPhase() const
	{
		return this->reductorPhase;
	}

	inline float MotorDriveDevice::getFlapPosition() const
	{
		return this->flapPosition;
	}

	inline float MotorDriveDevice::getGatePosition() const
	{
		return this->gatePosition;
	}

	inline float MotorDriveDevice::getControlLinePosition() const
	{
		return this->controlLinePosition;
	}

	inline float MotorDriveDevice::getAutoSwitch12Position() const
	{
		return this->autoSwitch12Position;
	}

	inline float MotorDriveDevice::getAutoSwitch34Position() const
	{
		return this->autoSwitch34Position;

	}

	inline float MotorDriveDevice::getLeftSwivelCamPosition() const
	{
		return this->leftSwivelCamPosition;
	}

	inline float MotorDriveDevice::getRightSwivelCamPosition() const
	{
		return this->rightSwivelCamPosition;
	}
}