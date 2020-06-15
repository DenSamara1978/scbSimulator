#pragma once

#include "scbRelay.h"

class scbPolarRelay : public scbRelay
{
	int m_DirectContactBit;
	int m_ReverseContactBit;

protected:
	virtual void SetMode ( unsigned long mode ) override; // Вызывается из метода ChangeStatus

public:
	scbPolarRelay ( scbAbstractScheme* ownerScheme, int dir_bit, int rev_bit );
	virtual ~scbPolarRelay () override;

	virtual void Init () override;
	virtual void TimeToWork ( int signal, unsigned long long time ) override; // Обработка таймера
};

