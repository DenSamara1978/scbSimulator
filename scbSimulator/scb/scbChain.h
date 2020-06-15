#pragma once

#include "scbAbstractScheme.h"

class scbChain : public scbAbstractScheme
{
	unsigned long* m_Status; // Слово состояния схемы
	int m_StatusCount;

public:
	scbChain ( const wstring& name, int length );
	virtual ~scbChain () override;

	virtual void Init () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void Recalculate () override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};
