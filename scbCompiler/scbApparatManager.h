#pragma once

#include "scbManager.h"

class scbApparatManager : public scbManager
{
	/* ����� ��������� - ����� �����
	0 - ����� ����� (����)
	1 - �����
	2 - ������
	*/
	int m_Mode;
	int m_Submode; // �������� - ������ ������ �����


	int ParseApparat ( const scbParseInfo& info );

public:
	scbApparatManager ();
	virtual ~scbApparatManager () override;

	virtual int Parse ( const scbParseInfo& info ) override;
	virtual void Compile () override;
	virtual void FlushBinFile ( const ofstream& file ) override;
	virtual void FlushLogFile ( const wofstream& file ) override;
};