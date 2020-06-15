#pragma once

#include "scbAbstractScheme.h"

class scbConnectionPoint;

class scbConnectionPointScheme : public scbAbstractScheme
{
	unsigned long m_Status; // Текущее состояние того, что отправляется в схемы ЭЦ
	unsigned long m_ControlStatus [2]; // Текущее состояние того, что пришло из схем ЭЦ

	scbConnectionPoint* m_Point;

public:
	scbConnectionPointScheme ( const wstring& name, scbConnectionPoint::ConnectionType type );
	virtual ~scbConnectionPointScheme ();

	void SetStatus ( unsigned long status );

	virtual void Init () override;
	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};
