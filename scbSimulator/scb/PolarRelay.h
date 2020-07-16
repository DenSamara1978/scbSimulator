#pragma once

#include "Relay.h"

namespace scb
{
	class PolarRelay : public Relay
	{
	public:
		PolarRelay(AbstractScheme* ownerScheme, int directionalBit, int reverseBit);
		virtual ~PolarRelay() override;

		virtual void initialize() override;
		virtual void timeToWork(int signal, unsigned long long time) override; // ��������� �������

	protected:
		virtual void setMode(unsigned long mode) override; // ���������� �� ������ ChangeStatus

	private:
		int directionalContactBit;
		int reverseContactBit;
	};
}
