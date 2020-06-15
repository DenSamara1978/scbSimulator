#pragma once

#include "scbManager.h"

class scbDeviceManager : public scbManager
{
	/* ����� ��������� - ����� �����
	0 - ����� ����� (����)
	1 - �����
	2 - ������
	*/
	int m_Mode;
	int m_Submode; // �������� - ������ ������ �����


	int ParseDevice ( const scbParseInfo& info );
	int ParseInput ( const scbParseInfo& info );
	int ParseOutput ( const scbParseInfo& info );

public:
	scbDeviceManager ();
	virtual ~scbDeviceManager () override;

	virtual int Parse ( const scbParseInfo& info ) override;
	virtual void Clear () override;
	virtual void Compile () override;
	virtual void FlushBinFile ( const ofstream& file ) override;
	virtual void FlushLogFile ( const wofstream& file ) override;
};