#include "SchemeSse128.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeSse128::SchemeSse128(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status(_mm_setzero_si128()),
	sensitives(_mm_setzero_si128())
{
	const size_t size = 16 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = static_cast <__m128i*> (_mm_malloc(size, 16));
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

SchemeSse128::~SchemeSse128()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeSse128::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0] = _mm_load_si128(constMask.sseMask);
	this->dynSensitiveMask[0] = _mm_load_si128(dynMask.sseMask);
}

void SchemeSse128::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	this->prepareCircuitMasks[index] = _mm_load_si128(mask.sseMask);
	this->prepareCircuitResults[index] = _mm_load_si128(result.sseMask);
}

void SchemeSse128::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	this->mainCircuitMasks[index] = _mm_load_si128(mask.sseMask);
	this->mainCircuitResults[index] = _mm_load_si128(result.sseMask);
}

void SchemeSse128::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	this->staticSensitiveMasks[index] = _mm_load_si128(mask.sseMask);
	this->staticSensitiveResults[index] = _mm_load_si128(result.sseMask);
}

void SchemeSse128::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	this->dynamicSensitiveMasks[index] = _mm_load_si128(mask.sseMask);
	this->dynamicSensitiveResults[index] = _mm_load_si128(result.sseMask);
}

void SchemeSse128::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	OutputStream result;
	static const __m128i zero = _mm_setzero_si128();
	__m128i temp;
	__m128i mask = this->status;

	const int loop1 = this->nPrepareCircuits;
	if (loop1 != 0)
	{
		result.sseMask[0] = _mm_setzero_si128();

		for (i = 0; i < loop1; ++i)
		{
			temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->prepareCircuitMasks[i]), zero);
			temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
			temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(1, 0, 3, 2)));
			result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->prepareCircuitResults[i]));
		}

		mask = _mm_or_si128(mask, result.sseMask[0]);
	}

	result.sseMask[0] = _mm_setzero_si128();

	const int loop2 = this->nMainCircuits;
	for (i = 0; i < loop2; ++i)
	{
		temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->mainCircuitMasks[i]), zero);
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->mainCircuitResults[i]));
	}

	for (const auto& device : this->devices)
		device->changeStatus(result);

	this->markRecalculated();

	result.sseMask[0] = this->constSensitiveMask[0];

	const int loop3 = this->nStaticSensitives;
	for (i = 0; i < loop3; ++i)
	{
		temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->staticSensitiveMasks[i]), zero);
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->staticSensitiveResults[i]));
	}

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->dynamicSensitiveMasks[i]), zero);
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->dynamicSensitiveResults[i]));
	}

	this->sensitives = result.sseMask[0];

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeSse128::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] |= _rotl(1, bit & 0x1F);
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeSse128::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x60, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeSse128::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m128i oldStatus = this->status;
	this->status = _mm_or_si128(_mm_load_si128(maskOn.sseMask), _mm_and_si128(this->status, _mm_load_si128(maskOff.sseMask)));

	if (this->isNotMarkedToRecalculate())
	{
		if (_mm_movemask_epi8(_mm_cmpeq_epi32(_mm_xor_si128(oldStatus, this->status), _mm_setzero_si128())) != 0xFFFF)
			this->markToRecalculate();
	}
}
