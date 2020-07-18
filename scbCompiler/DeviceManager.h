#pragma once

#include "Manager.h"

class DeviceManager : public Manager
{
public:
	DeviceManager ();
	virtual ~DeviceManager () override;

	virtual int parse ( const ParseInfo& info ) override;
	virtual void clear () override;
	virtual void compile () override;
	virtual void flushBinFile ( const ofstream& file ) override;
	virtual void flushLogFile ( const wofstream& file ) override;

private:
	/* ����� ��������� - ����� �����
	0 - ����� ����� (����)
	1 - �����
	2 - ������
	*/
	int mode;
	int submode; // �������� - ������ ������ �����


	int parseDevice(const ParseInfo& info);
	int parseInput(const ParseInfo& info);
	int parseOutput(const ParseInfo& info);

};