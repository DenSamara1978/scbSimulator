#pragma once

#include "scbRelay.h"

class scbNeutralRelay : public scbRelay
{
	int m_OnContactBit;
	int m_OffContactBit;
	int m_OnBridgeContactBit;
	int m_OffBridgeContactBit;
	bool m_HasOffContact;
	bool m_HasBridgeContact;

protected:
	virtual void SetMode ( unsigned long mode ) override; // Вызывается из метода ChangeStatus

public:
	scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit );
	scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit, int off_bit );
	scbNeutralRelay ( scbAbstractScheme* ownerScheme, int on_bit, int off_bit, int on_bridge_bit, int off_bridge_bit );
	virtual ~scbNeutralRelay () override;

	virtual void Init () override;
	virtual void TimeToWork ( int signal, unsigned long long time ) override; // Обработка таймера
};

