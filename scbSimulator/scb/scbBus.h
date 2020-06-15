#pragma once

#include "scbAbstractScheme.h"

class scbBus : public scbAbstractScheme
{
	unsigned long* m_Status; // Слово состояния схемы
	int m_StatusCount;

public:
	scbBus ( const wstring& name, int length );
	virtual ~scbBus () override;

	virtual void Init () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void Recalculate () override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};