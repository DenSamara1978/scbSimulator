#pragma once

#include "AbstractSchemeDevice.h"

//class trackSwitch;

namespace scb
{
	class ConnectionPoint : public AbstractSchemeDevice
	{
	public:
		enum class ConnectionType
		{
			SupplierOnly = 0,
			RecieverDC,
			Reciever25Hz,
			Reciever50Hz,
			Reciever75Hz,
			RecieverToneFrequency
		};

		ConnectionPoint(AbstractScheme* ownerScheme, ConnectionType type);
		virtual ~ConnectionPoint();

		//	void SetSwitch ( trackSwitch* point );

		void setSignal(const OutputStream& param); // Вызывается рельсовыми блоками

		virtual void initialize() override;
		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // Вызывается светофором-хозяином

	private:
		ConnectionType type;
		//	trackSwitch* m_TrackSwitch;
	};
}
