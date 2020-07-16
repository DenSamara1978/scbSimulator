#pragma once

#include "Relay.h"

using namespace scb;

class NeutralRelay : public Relay
{
public:
	NeutralRelay(AbstractScheme* ownerScheme, int onBit);
	NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit);
	NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit, int onBridgeBit, int offBridgeBit);
	virtual ~NeutralRelay() override;

	virtual void initialize() override;
	virtual void timeToWork(int signal, unsigned long long time) override; // Обработка таймера


protected:
	virtual void setMode(unsigned long mode) override; // Вызывается из метода ChangeStatus

private:
	int onContactBit;
	int offContactBit;
	int onBridgeContactBit;
	int offBridgeContactBit;
	bool hasOffContact;
	bool hasBridgeContact;
};

