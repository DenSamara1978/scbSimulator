#include "SchemeGpr256.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeGpr256::SchemeGpr256(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L},
	sensitives {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L},
	staticSensitives {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}
{
	const size_t size = 8 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = new unsigned long[size << 3];
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits * 8;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 16;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits * 8;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 16;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives * 8;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 16;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives * 8;
	this->dynSensitiveMask = this->dynamicSensitiveMasks + this->nDynamicSensitives * 16;
	this->constSensitiveMask = this->dynSensitiveMask + 8;
	memset(this->memory, 0, size);
}

SchemeGpr256::~SchemeGpr256()
{
	if (this->memory)
	{
		delete[] this->memory;
		this->memory = nullptr;
	}
}

void SchemeGpr256::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	memcpy(this->constSensitiveMask, &constMask, 32);
	memcpy(this->dynSensitiveMask, &dynMask, 32);
}

void SchemeGpr256::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->prepareCircuitMasks[index * 8]), &mask, 32);
	memcpy(&(this->prepareCircuitResults[index * 8]), &result, 32);
}

void SchemeGpr256::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->mainCircuitMasks[index * 8]), &mask, 32);
	memcpy(&(this->mainCircuitResults[index * 8]), &result, 32);
}

void SchemeGpr256::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->staticSensitiveMasks[index * 8]), &mask, 32);
	memcpy(&(this->staticSensitiveResults[index * 8]), &result, 32);
}

void SchemeGpr256::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->dynamicSensitiveMasks[index * 8]), &mask, 32);
	memcpy(&(this->dynamicSensitiveResults[index * 8]), &result, 32);
}

void SchemeGpr256::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	unsigned long result[8] {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned long temp;
	unsigned long mask[] = {~this->status[0], ~this->status[1], ~this->status[2], ~this->status[3],
							~this->status[4], ~this->status[5], ~this->status[6], ~this->status[7]};

	if (this->isMarkedToFullRecalculating())
	{
		const int loop1 = this->nPrepareCircuits;
		if (loop1 > 0)
		{
			for (i = 0; i < loop1; ++i)
			{
				temp = (mask[0] & this->prepareCircuitMasks[i * 8]) | (mask[1] & this->prepareCircuitMasks[i * 8 + 1]) |
					(mask[2] & this->prepareCircuitMasks[i * 8 + 2]) | (mask[3] & this->prepareCircuitMasks[i * 8 + 3]) |
					(mask[4] & this->prepareCircuitMasks[i * 8 + 4]) | (mask[1] & this->prepareCircuitMasks[i * 8 + 5]) |
					(mask[5] & this->prepareCircuitMasks[i * 8 + 6]) | (mask[3] & this->prepareCircuitMasks[i * 8 + 7]);
				if (temp == 0)
				{
					result[0] |= this->prepareCircuitResults[i * 8];
					result[1] |= this->prepareCircuitResults[i * 8 + 1];
					result[2] |= this->prepareCircuitResults[i * 8 + 2];
					result[3] |= this->prepareCircuitResults[i * 8 + 3];
					result[4] |= this->prepareCircuitResults[i * 8 + 4];
					result[5] |= this->prepareCircuitResults[i * 8 + 5];
					result[6] |= this->prepareCircuitResults[i * 8 + 6];
					result[7] |= this->prepareCircuitResults[i * 8 + 7];
				}
			}

			mask[0] &= ~result[0];
			mask[1] &= ~result[1];
			mask[2] &= ~result[2];
			mask[3] &= ~result[3];
			mask[4] &= ~result[4];
			mask[5] &= ~result[5];
			mask[6] &= ~result[6];
			mask[7] &= ~result[7];

			memset(result, 0, 32);
		}

		const int loop2 = this->nMainCircuits;
		for (i = 0; i < loop2; ++i)
		{
			temp = (mask[0] & this->mainCircuitMasks[i * 8]) | (mask[1] & this->mainCircuitMasks[i * 8 + 1]) |
				(mask[2] & this->mainCircuitMasks[i * 8 + 2]) | (mask[3] & this->mainCircuitMasks[i * 8 + 3]) |
				(mask[4] & this->mainCircuitMasks[i * 8 + 4]) | (mask[1] & this->mainCircuitMasks[i * 8 + 5]) |
				(mask[5] & this->mainCircuitMasks[i * 8 + 6]) | (mask[3] & this->mainCircuitMasks[i * 8 + 7]);
			if (temp == 0)
			{
				result[0] |= this->mainCircuitResults[i * 8];
				result[1] |= this->mainCircuitResults[i * 8 + 1];
				result[2] |= this->mainCircuitResults[i * 8 + 2];
				result[3] |= this->mainCircuitResults[i * 8 + 3];
				result[4] |= this->mainCircuitResults[i * 8 + 4];
				result[5] |= this->mainCircuitResults[i * 8 + 5];
				result[6] |= this->mainCircuitResults[i * 8 + 6];
				result[7] |= this->mainCircuitResults[i * 8 + 7];
			}
		}

		OutputStream stream;
		memcpy(&(stream.mask), result, 32);
		for (const auto& device : this->devices)
			device->changeStatus(stream);

		memset(result, 0, 32);

		const int loop3 = this->nStaticSensitives;
		for (i = 0; i < loop3; ++i)
		{
			temp = (mask[0] & this->staticSensitiveMasks[i * 8]) | (mask[1] & this->staticSensitiveMasks[i * 8 + 1]) |
				(mask[2] & this->staticSensitiveMasks[i * 8 + 2]) | (mask[3] & this->staticSensitiveMasks[i * 8 + 3]) |
				(mask[4] & this->staticSensitiveMasks[i * 8 + 4]) | (mask[1] & this->staticSensitiveMasks[i * 8 + 5]) |
				(mask[5] & this->staticSensitiveMasks[i * 8 + 6]) | (mask[3] & this->staticSensitiveMasks[i * 8 + 7]);
			if (temp == 0)
			{
				result[0] |= this->staticSensitiveResults[i * 8];
				result[1] |= this->staticSensitiveResults[i * 8 + 1];
				result[2] |= this->staticSensitiveResults[i * 8 + 2];
				result[3] |= this->staticSensitiveResults[i * 8 + 3];
				result[4] |= this->staticSensitiveResults[i * 8 + 4];
				result[5] |= this->staticSensitiveResults[i * 8 + 5];
				result[6] |= this->staticSensitiveResults[i * 8 + 6];
				result[7] |= this->staticSensitiveResults[i * 8 + 7];
			}
		}

		this->staticSensitives[0] = result[0];
		this->staticSensitives[1] = result[1];
		this->staticSensitives[2] = result[2];
		this->staticSensitives[3] = result[3];
		this->staticSensitives[4] = result[4];
		this->staticSensitives[5] = result[5];
		this->staticSensitives[6] = result[6];
		this->staticSensitives[7] = result[7];
	}

	result[0] = this->constSensitiveMask[0] | this->staticSensitives[0];
	result[1] = this->constSensitiveMask[1] | this->staticSensitives[1];
	result[2] = this->constSensitiveMask[2] | this->staticSensitives[2];
	result[3] = this->constSensitiveMask[3] | this->staticSensitives[3];
	result[4] = this->constSensitiveMask[4] | this->staticSensitives[4];
	result[5] = this->constSensitiveMask[5] | this->staticSensitives[5];
	result[6] = this->constSensitiveMask[6] | this->staticSensitives[6];
	result[7] = this->constSensitiveMask[7] | this->staticSensitives[7];

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		temp = (mask[0] & this->dynamicSensitiveMasks[i * 8]) | (mask[1] & this->dynamicSensitiveMasks[i * 8 + 1]) |
			(mask[2] & this->dynamicSensitiveMasks[i * 8 + 2]) | (mask[3] & this->dynamicSensitiveMasks[i * 8 + 3]) |
			(mask[4] & this->dynamicSensitiveMasks[i * 8 + 4]) | (mask[1] & this->dynamicSensitiveMasks[i * 8 + 5]) |
			(mask[5] & this->dynamicSensitiveMasks[i * 8 + 6]) | (mask[3] & this->dynamicSensitiveMasks[i * 8 + 7]);
		if (temp == 0)
		{
			result[0] |= this->dynamicSensitiveResults[i * 8];
			result[1] |= this->dynamicSensitiveResults[i * 8 + 1];
			result[2] |= this->dynamicSensitiveResults[i * 8 + 2];
			result[3] |= this->dynamicSensitiveResults[i * 8 + 3];
			result[4] |= this->dynamicSensitiveResults[i * 8 + 4];
			result[5] |= this->dynamicSensitiveResults[i * 8 + 5];
			result[6] |= this->dynamicSensitiveResults[i * 8 + 6];
			result[7] |= this->dynamicSensitiveResults[i * 8 + 7];
		}
	}

	memcpy(this->sensitives, result, 32);
	this->markRecalculated();

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeGpr256::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	const unsigned long old = this->status[element];
	this->status[element] |= _rotl(1, bit & 0x1F);
	if (old != this->status[element])
		this->markToFullRecalculating();
}

void SchemeGpr256::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	const unsigned long old = this->status[element];
	this->status[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != this->status[element])
		this->markToFullRecalculating();
}

void SchemeGpr256::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	unsigned long dynDifference = 0;
	unsigned long sensDifference = 0;

	for (int i = 0; i < 8; ++i)
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
