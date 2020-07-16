#pragma once

#include "AbstractScheme.h"
#include "AbstractSchemeDevice.h"

namespace scb
{
	class PultTabloLampGroup : public AbstractSchemeDevice
	{
	public:
		PultTabloLampGroup(AbstractScheme* ownerScheme);
		virtual ~PultTabloLampGroup() override;

		bool getLampStatus(int bit) const;

		virtual void initialize() override;
		virtual void changeStatus(const OutputStream& param) override; // ���������� ������-�������� ����� �������
		virtual void idleTimer(unsigned long long time) override;

	private:
		OutputStream lampStatus; // ������� �������� ��������� ����
	};

	inline bool PultTabloLampGroup::getLampStatus(int bit) const
	{
		return (((this->lampStatus.mask[(bit & 0xE0) >> 5]) & (1 << (bit & 31))) != 0);
	}
}