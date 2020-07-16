#include "AbstractSchemeDevice.h"

using namespace scb;

AbstractSchemeDevice::AbstractSchemeDevice(AbstractScheme* ownerScheme) :
	ownerScheme(ownerScheme)
{
}

AbstractSchemeDevice::~AbstractSchemeDevice()
{
	this->cleanupTimers();
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

