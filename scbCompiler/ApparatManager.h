#pragma once

#include "Manager.h"

class ApparatManager : public Manager
{
public:
	ApparatManager();
	virtual ~ApparatManager() override;

	virtual int parse(const ParseInfo& info) override;
	virtual void compile() override;
	virtual void flushBinFile(const ofstream& file) override;
	virtual void flushLogFile(const wofstream& file) override;

private:
	/* ����� ��������� - ����� �����
	0 - ����� ����� (����)
	1 - �����
	2 - ������
	*/
	int mode;
	int submode; // �������� - ������ ������ �����


	int parseApparat(const ParseInfo& info);

};