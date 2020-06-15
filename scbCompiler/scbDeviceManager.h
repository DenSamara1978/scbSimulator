#pragma once

#include "scbManager.h"

class scbDeviceManager : public scbManager
{
	/* Режим обработки - номер блока
	0 - Шапка шлюза (ШЛЮЗ)
	1 - ВХОДЫ
	2 - ВЫХОДЫ
	*/
	int m_Mode;
	int m_Submode; // Подрежим - разбор внутри блока


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