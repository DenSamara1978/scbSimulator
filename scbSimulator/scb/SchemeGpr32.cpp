#include "SchemeGpr32.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeGpr32::SchemeGpr32(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status(0L),
	sensitives(0L)
{
	const size_t size = 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = new unsigned long[size];
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 2;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 2;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 2;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives;
	this->dynSensitiveMask = this->dynamicSensitiveMasks + this->nDynamicSensitives * 2;
	this->constSensitiveMask = this->dynSensitiveMask + 1;
	memset(this->memory, 0, size);
}

SchemeGpr32::~SchemeGpr32()
{
	if (this->memory)
	{
		delete[] this->memory;
		this->memory = nullptr;
	}
}

void SchemeGpr32::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0] = constMask.mask[0];
	this->dynSensitiveMask[0] = dynMask.mask[0];
}

void SchemeGpr32::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	this->prepareCircuitMasks[index] = mask.mask[0];
	this->prepareCircuitResults[index] = result.mask[0];
}

void SchemeGpr32::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	this->mainCircuitMasks[index] = mask.mask[0];
	this->mainCircuitResults[index] = result.mask[0];
}

void SchemeGpr32::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	this->staticSensitiveMasks[index] = mask.mask[0];
	this->staticSensitiveResults[index] = result.mask[0];
}

void SchemeGpr32::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	this->dynamicSensitiveMasks[index] = mask.mask[0];
	this->dynamicSensitiveResults[index ] = result.mask[0];
}

void SchemeGpr32::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	unsigned long result = 0;
	unsigned long mask = ~this->status;

	const int loop1 = this->nPrepareCircuits;
	if (loop1 > 0)
	{
		for (i = 0; i < loop1; ++i)
		{
			if ((mask & this->prepareCircuitMasks[i]) == 0)
				result |= this->prepareCircuitResults[i];
		}

		mask &= ~result;

		result = 0;
	}

	const int loop2 = this->nMainCircuits;
	for (i = 0; i < loop2; ++i)
	{
		if ((mask & this->mainCircuitMasks[i]) == 0)
			result |= this->mainCircuitResults[i];
	}

	OutputStream stream;
	stream.mask[0] = result;
	for (const auto& device : this->devices)
		device->changeStatus(stream);

	this->markRecalculated();

	result = this->constSensitiveMask[0];

	const int loop3 = this->nStaticSensitives;
	for (i = 0; i < loop3; ++i)
	{
		if ((mask & this->staticSensitiveMasks[i]) == 0)
			result |= this->staticSensitiveResults[i];
	}

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		if ((mask & this->dynamicSensitiveMasks[i]) == 0)
			result |= this->dynamicSensitiveResults[i];
	}

	this->sensitives = result;

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeGpr32::setStatusBit(int bit)
{
	const unsigned long old = this->status;
	this->status |= _rotl(1, bit & 0x1F);
	if (old != this->status)
		this->markToRecalculate();
}

void SchemeGpr32::resetStatusBit(int bit)
{
	const unsigned long old = this->status;
	this->status &= ~(_rotl(1, bit & 0x1F));
	if (old != this->status)
		this->markToRecalculate();
}

void SchemeGpr32::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	unsigned long oldStatus;

	oldStatus = this->status;
	this->status = (this->status & maskOff.mask[0]) | maskOn.mask[0];

	if (oldStatus != this->status)
		this->markToRecalculate();
}
