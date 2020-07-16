#pragma once

#include "AbstractScheme.h"

namespace scb
{
	class MotorDriveDevice;

	class MotorDriveScheme : public AbstractScheme
	{
		unsigned long status; // ������� ��������� ����, ��� ������������ � ����� ��
		unsigned long controlStatus; // ������� ��������� ����, ��� ������ �� ���� ��

		MotorDriveDevice* driveDevice;

	public:
		MotorDriveScheme(const wstring& name);
		virtual ~MotorDriveScheme();

		MotorDriveDevice* getDriveDevice() const;

		virtual void initialize() override;
		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) override;
	};

	inline MotorDriveDevice* MotorDriveScheme::getDriveDevice() const
	{
		return this->driveDevice;
	}
}