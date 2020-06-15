#pragma once

#include "scbAbstractSchemeDevice.h"

//class trackSwitch;

class scbConnectionPoint : public scbAbstractSchemeDevice
{
public:
	enum ConnectionType
	{
		SupplierOnly = 0,
		Reciever_DC,
		Reciever_25Hz,
		Reciever_50Hz,
		Reciever_75Hz,
		Reciever_ToneFrequency
	};

private:
	ConnectionType m_Type;
	//	trackSwitch* m_TrackSwitch;

public:
	scbConnectionPoint ( scbAbstractScheme* ownerScheme, ConnectionType type );
	virtual ~scbConnectionPoint ();

	//	void SetSwitch ( trackSwitch* point );

	void SetSignal ( const scbOutputStream& param ); // Вызывается рельсовыми блоками

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается светофором-хозяином

};

