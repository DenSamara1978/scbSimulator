#pragma once

#include "scbAbstractSchemeDevice.h"

struct scbRelayTimeSample
{
	int ModeFrom;
	int ModeTo;
	int Starting;
	int Shifting;
};

class scbRelay : public scbAbstractSchemeDevice
{
protected:
	int m_CurrentMode; // �����, � ������� � ��������� ������ ��������� ����
	int m_TargetMode; // �����, � ������� ���� ������ �����������
	int m_Status; // 0 - ��������� ��� ����, 1 - �������� �� ������, 2 - ������� �� ������, 3 - ��������� ��� �����, 4 - �������� �� ���������, 5 - ������� �� ���������
	unsigned long long m_TimeStamp;
	int m_Starting;
	int m_Shifting;

	vector<scbRelayTimeSample> m_TimeSamples;

	// �� ������� ������ ����������� � �������������� ���� ����� ���������� ����� ����� ������
	// - ��� �� ������ ����������� ����������� ��� ���������� ������� ����������� �������� ���������
	virtual void SetMode ( unsigned long mode ) abstract; // ���������� �� ������ ChangeStatus

public:
	scbRelay ( scbAbstractScheme* ownerScheme );
	virtual ~scbRelay () override;

	void SetSample ( int from_mode, int to_mode, int start, int shift );

	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // ���������� ������-�������� ����� �������
};
