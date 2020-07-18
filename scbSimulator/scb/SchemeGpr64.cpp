#include "SchemeGpr64.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeGpr64::SchemeGpr64(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status {0L, 0L},
	sensitives {0L, 0L}
{
	const size_t size = 2 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = new unsigned long[size << 1];
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits * 2;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 4;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits * 2;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 4;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives * 2;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 4;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives * 2;
	this->dynSensitiveMask = this->dynamicSensitiveMasks + this->nDynamicSensitives * 4;
	this->constSensitiveMask = this->dynSensitiveMask + 2;
	memset(this->memory, 0, size);
}

SchemeGpr64::~SchemeGpr64()
{
	if (this->memory)
	{
		delete[] this->memory;
		this->memory = nullptr;
	}
}

void SchemeGpr64::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	memcpy(this->constSensitiveMask, &constMask, 8);
	memcpy(this->dynSensitiveMask, &dynMask, 8);
}

void SchemeGpr64::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->prepareCircuitMasks[index * 2]), &mask, 8);
	memcpy(&(this->prepareCircuitResults[index * 2]), &result, 8);
}

void SchemeGpr64::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->mainCircuitMasks[index * 2]), &mask, 8);
	memcpy(&(this->mainCircuitResults[index * 2]), &result, 8);
}

void SchemeGpr64::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->staticSensitiveMasks[index * 2]), &mask, 8);
	memcpy(&(this->staticSensitiveResults[index * 2]), &result, 8);
}

void SchemeGpr64::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->dynamicSensitiveMasks[index * 2]), &mask, 8);
	memcpy(&(this->dynamicSensitiveResults[index * 2]), &result, 8);
}

void SchemeGpr64::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	unsigned long result[2] {0, 0};
	unsigned long temp;
	unsigned long mask[] = {~this->status[0], ~this->status[1]};

	const int loop1 = this->nPrepareCircuits;
	if (loop1 > 0)
	{
		for (i = 0; i < loop1; ++i)
		{
			temp = (mask[0] & this->prepareCircuitMasks[i * 2]) | (mask[1] & this->prepareCircuitMasks[i * 2 + 1]);
			if (temp == 0)
			{
				result[0] |= this->prepareCircuitResults[i * 2];
				result[1] |= this->prepareCircuitResults[i * 2 + 1];
			}
		}

		mask[0] &= ~result[0];
		mask[1] &= ~result[1];

		memset(result, 0, 8);
	}

	const int loop2 = this->nMainCircuits;
	for (i = 0; i < loop2; ++i)
	{
		temp = (mask[0] & this->mainCircuitMasks[i * 2]) | (mask[1] & this->mainCircuitMasks[i * 2 + 1]);
		if (temp == 0)
		{
			result[0] |= this->mainCircuitResults[i * 2];
			result[1] |= this->mainCircuitResults[i * 2 + 1];
		}
	}

	OutputStream stream;
	memcpy(&(stream.mask), result, 8);
	for (const auto& device : this->devices)
		device->changeStatus(stream);

	this->markRecalculated();

	memcpy(result, this->constSensitiveMask, 8);

	const int loop3 = this->nStaticSensitives;
	for (i = 0; i < loop3; ++i)
	{
		temp = (mask[0] & this->staticSensitiveMasks[i * 2]) | (mask[1] & this->staticSensitiveMasks[i * 2 + 1]);
		if (temp == 0)
		{
			result[0] |= this->staticSensitiveResults[i * 2];
			result[1] |= this->staticSensitiveResults[i * 2 + 1];
		}
	}

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		temp = (mask[0] & this->dynamicSensitiveMasks[i * 2]) | (mask[1] & this->dynamicSensitiveMasks[i * 2 + 1]);
		if (temp == 0)
		{
			result[0] |= this->dynamicSensitiveResults[i * 2];
			result[1] |= this->dynamicSensitiveResults[i * 2 + 1];
		}
	}

	memcpy(this->sensitives, result, 8);

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeGpr64::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	const unsigned long old = this->status[element];
	this->status[element] |= _rotl(1, bit & 0x1F);
	if (old != this->status[element])
		this->markToRecalculate();
}

void SchemeGpr64::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	const unsigned long old = this->status[element];
	this->status[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != this->status[element])
		this->markToRecalculate();
}

void SchemeGpr64::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	unsigned long difference = 0;
	unsigned long oldStatus0, oldStatus1;

	oldStatus0 = this->status[0];
	oldStatus1 = this->status[1];
	this->status[0] = (this->status[0] & maskOff.mask[0]) | maskOn.mask[0];
	this->status[1] = (this->status[1] & maskOff.mask[1]) | maskOn.mask[1];
	difference = (oldStatus0 ^ this->status[0]) | (oldStatus1 ^ this->status[1]);

	if (difference != 0)
		this->markToRecalculate();
}
