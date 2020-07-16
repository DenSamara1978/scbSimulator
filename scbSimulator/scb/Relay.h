#pragma once

#include "AbstractSchemeDevice.h"


namespace scb
{
	struct RelayTimeSample
	{
		int modeFrom;
		int modeTo;
		int starting;
		int shifting;
	};

	class Relay : public AbstractSchemeDevice
	{
	public:
		Relay(AbstractScheme* ownerScheme);
		virtual ~Relay() override;

		void setSample(int from_mode, int to_mode, int start, int shift);

		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // ���������� ������-�������� ����� �������

	protected:
		int currentMode; // �����, � ������� � ��������� ������ ��������� ����
		int targetMode; // �����, � ������� ���� ������ �����������
		int status; // 0 - ��������� ��� ����, 1 - �������� �� ������, 2 - ������� �� ������, 3 - ��������� ��� �����, 4 - �������� �� ���������, 5 - ������� �� ���������
		unsigned long long timeStamp;
		int starting;
		int shifting;

		vector<RelayTimeSample> timeSamples;

		// �� ������� ������ ����������� � �������������� ���� ����� ���������� ����� ����� ������
		// - ��� �� ������ ����������� ����������� ��� ���������� ������� ����������� �������� ���������
		virtual void setMode(unsigned long mode) abstract; // ���������� �� ������ ChangeStatus
	};
}