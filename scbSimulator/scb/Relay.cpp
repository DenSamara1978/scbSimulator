#include "Relay.h"

using namespace scb;

Relay::Relay(AbstractScheme* ownerScheme) :
	AbstractSchemeDevice(ownerScheme),
	currentMode(0),
	targetMode(0),
	timeStamp(0),
	status(0),
	starting(0),
	shifting(0)
{

}

Relay::~Relay()
{
}

void Relay::setSample(int from_mode, int to_mode, int start, int shift)
{
	this->timeSamples.push_back({from_mode, to_mode, start, shift});
}

void Relay::idleTimer(unsigned long long time)
{
	// Пустой вызов
}

void Relay::changeStatus(const OutputStream& param)
{
	unsigned long mode[] = {0l, 0l, 0l, 0l, 0l, 0l, 0l, 0l};

	for (auto& convertation : this->convertations)
		if ((param.mask[convertation.inputElement] & convertation.inputMask) != 0)
			mode[convertation.outputElement] |= convertation.outputMask;

	this->setMode(mode[0]); // Используется только 32 бита результата
}
