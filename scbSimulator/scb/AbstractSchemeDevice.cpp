#include "AbstractSchemeDevice.h"
#include "AbstractScheme.h"

using namespace scb;

using time::Timer;

AbstractSchemeDevice::AbstractSchemeDevice(AbstractScheme* ownerScheme) :
	ownerScheme(ownerScheme),
	hasIdleTimer(false)
{
}

AbstractSchemeDevice::~AbstractSchemeDevice()
{
	auto timer = Timer::getInstance();
	timer->deleteIdleTimer(this);
	timer->deleteTimeToWork(this);
	this->ownerScheme = nullptr;
}

void AbstractSchemeDevice::mapInputOutput(int inputBit, int outputBit)
{
	if ((inputBit > 255) or (inputBit < 0) or (outputBit > 255) or (outputBit < 0)) return;
	Convertation conv;
	conv.inputElement = (inputBit & 0xFFE0 ) >> 5;
	conv.inputMask = 1 << (inputBit & 0x1F );
	conv.outputElement = (outputBit & 0xFFE0 ) >> 5;
	conv.outputMask = 1 << (outputBit & 0x1F );
	this->convertations.push_back(conv);
}

void AbstractSchemeDevice::timeToWork(int signal, unsigned long long time)
{
	// Ïףסעמי גûחמג
}