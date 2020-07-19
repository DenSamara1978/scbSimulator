#include "SchemeGpr128.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeGpr128::SchemeGpr128(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status {0L, 0L, 0L, 0L},
	sensitives {0L, 0L, 0L, 0L},
	staticSensitives {0L, 0L, 0L, 0L}
{
	const size_t size = 4 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = new unsigned long[size << 2];
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits * 4;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 8;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits * 4;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 8;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives * 4;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 8;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives * 4;
	this->dynSensitiveMask = this->dynamicSensitiveMasks + this->nDynamicSensitives * 8;
	this->constSensitiveMask = this->dynSensitiveMask + 4;
	memset(this->memory, 0, size);
}

SchemeGpr128::~SchemeGpr128()
{
	if (this->memory)
	{
		delete[] this->memory;
		this->memory = nullptr;
	}
}

void SchemeGpr128::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	memcpy(this->constSensitiveMask, &constMask, 16);
	memcpy(this->dynSensitiveMask, &dynMask, 16);
}

void SchemeGpr128::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->prepareCircuitMasks[index * 4]), &mask, 16);
	memcpy(&(this->prepareCircuitResults[index * 4]), &result, 16);
}

void SchemeGpr128::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->mainCircuitMasks[index * 4]), &mask, 16);
	memcpy(&(this->mainCircuitResults[index * 4]), &result, 16);
}

void SchemeGpr128::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->staticSensitiveMasks[index * 4]), &mask, 16);
	memcpy(&(this->staticSensitiveResults[index * 4]), &result, 16);
}

void SchemeGpr128::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->dynamicSensitiveMasks[index * 4]), &mask, 16);
	memcpy(&(this->dynamicSensitiveResults[index * 4]), &result, 16);
}

void SchemeGpr128::recalculate()
{

	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	unsigned long result[4] {0, 0, 0, 0};
	unsigned long temp;
	unsigned long mask[] = { ~this->status[0], ~this->status[1], ~this->status[2], ~this->status[3] };

	if (this->isMarkedToFullRecalculating())
	{
		const int loop1 = this->nPrepareCircuits;
		if (loop1 > 0)
		{
			for (i = 0; i < loop1; ++i)
			{
				temp = (mask[0] & this->prepareCircuitMasks[i * 4]) | (mask[1] & this->prepareCircuitMasks[i * 4 + 1]) |
					(mask[2] & this->prepareCircuitMasks[i * 4 + 2]) | (mask[3] & this->prepareCircuitMasks[i * 4 + 3]);
				if (temp == 0)
				{
					result[0] |= this->prepareCircuitResults[i * 4];
					result[1] |= this->prepareCircuitResults[i * 4 + 1];
					result[2] |= this->prepareCircuitResults[i * 4 + 2];
					result[3] |= this->prepareCircuitResults[i * 4 + 3];
				}
			}

			mask[0] &= ~result[0];
			mask[1] &= ~result[1];
			mask[2] &= ~result[2];
			mask[3] &= ~result[3];

			memset(result, 0, 16);
		}

		const int loop2 = this->nMainCircuits;
		for (i = 0; i < loop2; ++i)
		{
			temp = (mask[0] & this->mainCircuitMasks[i * 4]) | (mask[1] & this->mainCircuitMasks[i * 4 + 1]) |
				(mask[2] & this->mainCircuitMasks[i * 4 + 2]) | (mask[3] & this->mainCircuitMasks[i * 4 + 3]);
			if (temp == 0)
			{
				result[0] |= this->mainCircuitResults[i * 4];
				result[1] |= this->mainCircuitResults[i * 4 + 1];
				result[2] |= this->mainCircuitResults[i * 4 + 2];
				result[3] |= this->mainCircuitResults[i * 4 + 3];
			}
		}

		OutputStream stream;
		memcpy(&(stream.mask), result, 16);
		for (const auto& device : this->devices)
			device->changeStatus(stream);

		memset(result, 0, 16);

		const int loop3 = this->nStaticSensitives;
		for (i = 0; i < loop3; ++i)
		{
			temp = (mask[0] & this->staticSensitiveMasks[i * 4]) | (mask[1] & this->staticSensitiveMasks[i * 4 + 1]) |
				(mask[2] & this->staticSensitiveMasks[i * 4 + 2]) | (mask[3] & this->staticSensitiveMasks[i * 4 + 3]);
			if (temp == 0)
			{
				result[0] |= this->staticSensitiveResults[i * 4];
				result[1] |= this->staticSensitiveResults[i * 4 + 1];
				result[2] |= this->staticSensitiveResults[i * 4 + 2];
				result[3] |= this->staticSensitiveResults[i * 4 + 3];
			}
		}

		this->staticSensitives[0] = result[0];
		this->staticSensitives[1] = result[1];
		this->staticSensitives[2] = result[2];
		this->staticSensitives[3] = result[3];
	}

	result[0] = this->constSensitiveMask[0] | this->staticSensitives[0];
	result[1] = this->constSensitiveMask[1] | this->staticSensitives[1];
	result[2] = this->constSensitiveMask[2] | this->staticSensitives[2];
	result[3] = this->constSensitiveMask[3] | this->staticSensitives[3];

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		temp = (mask[0] & this->dynamicSensitiveMasks[i * 4]) | (mask[1] & this->dynamicSensitiveMasks[i * 4 + 1]) |
			(mask[2] & this->dynamicSensitiveMasks[i * 4 + 2]) | (mask[3] & this->dynamicSensitiveMasks[i * 4 + 3]);
		if (temp == 0)
		{
			result[0] |= this->dynamicSensitiveResults[i * 4];
			result[1] |= this->dynamicSensitiveResults[i * 4 + 1];
			result[2] |= this->dynamicSensitiveResults[i * 4 + 2];
			result[3] |= this->dynamicSensitiveResults[i * 4 + 3];
		}
	}

	memcpy(this->sensitives, result, 16);
	this->markRecalculated();

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeGpr128::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	const unsigned long old = this->status[element];
	this->status[element] |= _rotl(1, bit & 0x1F);
	if (old != this->status[element])
		this->markToFullRecalculating();
}

void SchemeGpr128::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	const unsigned long old = this->status[element];
	this->status[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != this->status[element])
		this->markToFullRecalculating();
}

void SchemeGpr128::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	unsigned long dynDifference = 0;
	unsigned long sensDifference = 0;

	for (int i = 0; i < 4; ++i)
	{
		unsigned long oldStatus;
		unsigned long difference;
		oldStatus = this->status[i];
		this->status[i] = (this->status[i] & maskOff.mask[i]) | maskOn.mask[i];
		difference = (oldStatus ^ this->status[i]);
		dynDifference |= difference & this->dynSensitiveMask[i];
		sensDifference |= difference & this->sensitives[i];
	}

	if (sensDifference != 0)
		this->markToFullRecalculating();
	else if (dynDifference != 0)
		this->markToDynamicSensitivesRecalculating();
}
