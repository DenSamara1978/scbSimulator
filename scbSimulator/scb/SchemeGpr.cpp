#include "SchemeGpr.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeGpr::SchemeGpr(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status {0L, 0L, 0L, 0L}
{
	const size_t size = 4 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives);
	this->memory = new unsigned long[size << 2];
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 2;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 2;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 2;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives;
	memset(this->memory, 0, size);
}

SchemeGpr::~SchemeGpr()
{
	if (this->memory)
	{
		delete[] this->memory;
		this->memory = nullptr;
	}
}

void SchemeGpr::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->prepareCircuitMasks[index * 4]), &mask, 16);
	memcpy(&(this->prepareCircuitResults[index * 4]), &result, 16);
}

void SchemeGpr::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	memcpy(&(this->mainCircuitMasks[index * 4]), &mask, 16);
	memcpy(&(this->mainCircuitResults[index * 4]), &result, 16);
}

void SchemeGpr::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->staticSensitiveMasks[index * 4]), &mask, 16);
	memcpy(&(this->staticSensitiveResults[index * 4]), &result, 16);
}

void SchemeGpr::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	memcpy(&(this->dynamicSensitiveMasks[index * 4]), &mask, 16);
	memcpy(&(this->dynamicSensitiveResults[index * 4]), &result, 16);
}

void SchemeGpr::recalculate()
{
	int i;

	unsigned long result[4] {0, 0, 0, 0};
	unsigned long mask[] = {this->status[0], this->status[1], this->status[2], this->status[3]};
	unsigned long temp;

	const int loop1 = this->nPrepareCircuits;
	if (loop1 > 0)
	{
		for (i = 0; i < loop1; i++)
		{
			temp = (~(mask[0]) & this->prepareCircuitMasks[i * 4]) | (~(mask[1]) & this->prepareCircuitMasks[i * 4 + 1]) |
				(~(mask[2]) & this->prepareCircuitMasks[i * 4 + 2]) | (~(mask[3]) & this->prepareCircuitMasks[i * 4 + 3]);
			if (temp == 0)
			{
				result[0] |= this->prepareCircuitResults[i * 4];
				result[1] |= this->prepareCircuitResults[i * 4 + 1];
				result[2] |= this->prepareCircuitResults[i * 4 + 2];
				result[3] |= this->prepareCircuitResults[i * 4 + 3];
			}
		}

		mask[0] |= result[0];
		mask[1] |= result[1];
		mask[2] |= result[2];
		mask[3] |= result[3];

		memset(result, 0, 16);
	}

	const int loop2 = this->nMainCircuits;
	for (i = 0; i < loop2; i++)
	{
		temp = (~(mask[0]) & this->mainCircuitMasks[i * 4]) | (~(mask[1]) & this->mainCircuitMasks[i * 4 + 1]) |
			(~(mask[2]) & this->mainCircuitMasks[i * 4 + 2]) | (~(mask[3]) & this->mainCircuitMasks[i * 4 + 3]);
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

	this->markRecalculated();
}

void SchemeGpr::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	const unsigned long old = this->status[element];
	this->status[element] |= _rotl(1, bit & 0x1F);
	if (old != this->status[element])
		this->markToRecalculate();
}

void SchemeGpr::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	const unsigned long old = this->status[element];
	this->status[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != this->status[element])
		this->markToRecalculate();
}

void SchemeGpr::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	unsigned long difference = 0;
	unsigned long oldStatus;

	for (int i = 0; i < 4; i++)
	{
		oldStatus = this->status[i];
		this->status[i] = (this->status[i] & maskOff.mask[i]) | maskOn.mask[i];
		difference |= oldStatus ^ this->status[i];
	}

	if (difference != 0)
	{
		// Слово состояния контактов изменилось - надо ставить схемы на расчет
		this->markToRecalculate();
	}
}
