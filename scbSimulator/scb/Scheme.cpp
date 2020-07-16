#include "Scheme.h"
#include "SchemeOutput.h"
#include "NeutralRelay.h"
#include "PolarRelay.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

Scheme::Scheme(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	AbstractScheme(name),
	nPrepareCircuits(nPrepareCircuits),
	nMainCircuits(nMainCircuits),
	nStaticSensitives(nStaticSensitives),
	nDynamicSensitives(nDynamicSensitives)
{

}

Scheme::~Scheme()
{

}

void Scheme::setPolarRelay(int index, int directionalBit, int reversebit)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return;
	if (this->devices[index] == nullptr)
		this->devices[index] = new PolarRelay(this, directionalBit, reversebit);
}

void Scheme::setNeutralRelay(int index, int onBit)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return;
	if (this->devices[index] == nullptr)
		this->devices[index] = new NeutralRelay(this, onBit);
}

void Scheme::setNeutralRelay(int index, int onBit, int offBit)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return;
	if (this->devices[index] == nullptr)
		this->devices[index] = new NeutralRelay(this, onBit, offBit);
}

void Scheme::setNeutralRelay(int index, int onBit, int offBit, int onBridgeBit, int offBridgeBit)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return;
	if (this->devices[index] == nullptr)
		this->devices[index] = new NeutralRelay(this, onBit, offBit, onBridgeBit, offBridgeBit);
}

void Scheme::addRelayTimeSample(int index, int fromMode, int toMode, int start, int shift)
{
	auto isInRange = inRange(index, this->devices.size());
	auto isExist = (this->devices[index] != nullptr);
	if (isInRange && isExist)
		dynamic_cast <Relay*>(this->devices[index])->setSample(fromMode, toMode, start, shift);
}

void Scheme::addRelayConvertation(int index, int inputBit, int outputBit)
{
	auto isInRange = inRange(index, this->devices.size());
	auto isExist = (this->devices[index] != nullptr);
	if (isInRange && isExist)
		dynamic_cast <Relay*>(this->devices[index])->mapInputOutput(inputBit, outputBit);
}

void Scheme::initialize()
{
	for (const auto& device : this->devices)
		if (device != nullptr)
			device->initialize();
}

void Scheme::mapInputOutput(int outputIndex, int inputBit, int outputBit)
{
	this->devices[outputIndex]->mapInputOutput(inputBit, outputBit);
}
