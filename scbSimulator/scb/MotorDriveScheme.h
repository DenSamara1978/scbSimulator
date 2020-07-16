#pragma once

#include "AbstractScheme.h"

namespace scb
{
	class MotorDriveDevice;

	class MotorDriveScheme : public AbstractScheme
	{
		unsigned long status; // Текущее состояние того, что отправляется в схемы ЭЦ
		unsigned long controlStatus; // Текущее состояние того, что пришло из схем ЭЦ

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