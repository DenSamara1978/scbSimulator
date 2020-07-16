#pragma once

#include "AbstractScheme.h"

namespace scb
{
	class ConnectionPoint;

	class ConnectionPointScheme : public AbstractScheme
	{
	public:
		ConnectionPointScheme(const wstring& name, ConnectionPoint::ConnectionType type);
		virtual ~ConnectionPointScheme();

		void setStatus(unsigned long status);

		virtual void initialize() override;
		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) override;

	private:
		unsigned long status; // ������� ��������� ����, ��� ������������ � ����� ��
		unsigned long controlStatus[2]; // ������� ��������� ����, ��� ������ �� ���� ��

		ConnectionPoint* point;

	};
}