#include <intrin.h>

#include "SchemeAvx256.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeAvx256::SchemeAvx256(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status(_mm256_setzero_si256()),
	sensitives(_mm256_setzero_si256())
{
	const size_t size = 32 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = static_cast <__m256i*> (_mm_malloc(size, 16));
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

SchemeAvx256::~SchemeAvx256()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeAvx256::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0] = constMask.avxMask;
	this->dynSensitiveMask[0] = dynMask.avxMask;
}

void SchemeAvx256::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	this->prepareCircuitMasks[index] = mask.avxMask;
	this->prepareCircuitResults[index] = result.avxMask;
}

void SchemeAvx256::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	this->mainCircuitMasks[index] = mask.avxMask;
	this->mainCircuitResults[index] = result.avxMask;
}

void SchemeAvx256::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	this->staticSensitiveMasks[index] = mask.avxMask;
	this->staticSensitiveResults[index] = result.avxMask;
}

void SchemeAvx256::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	this->dynamicSensitiveMasks[index] = mask.avxMask;
	this->dynamicSensitiveResults[index] = result.avxMask;
}

void SchemeAvx256::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	OutputStream result;
	static const __m256i zero = _mm256_setzero_si256();
	__m256i temp;
	__m256i mask = this->status;

	const int loop1 = this->nPrepareCircuits;
	if (loop1 != 0)
	{
		result.avxMask = _mm256_setzero_si256();

		for (i = 0; i < loop1; ++i)
		{
			temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->prepareCircuitMasks[i]), zero);
			temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(2, 3, 0, 1)));
			temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));
			result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->prepareCircuitResults[i]));
		}

		mask = _mm256_or_si256(mask, result.avxMask);
	}

	result.avxMask = _mm256_setzero_si256();

	const int loop2 = this->nMainCircuits;
	for (i = 0; i < loop2; ++i)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->mainCircuitMasks[i]), zero);
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->mainCircuitResults[i]));
	}

	for (const auto& device : this->devices)
		device->changeStatus(result);

	this->markRecalculated();

	result.avxMask = this->constSensitiveMask[0];

	const int loop3 = this->nStaticSensitives;
	for (i = 0; i < loop3; ++i)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->staticSensitiveMasks[i]), zero);
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->staticSensitiveResults[i]));
	}

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->dynamicSensitiveMasks[i]), zero);
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->dynamicSensitiveResults[i]));
	}

	this->sensitives = result.avxMask;

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeAvx256::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] |= _rotl(1, bit & 0x1F);
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeAvx256::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeAvx256::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m256i oldStatus = this->status;
	this->status = _mm256_or_si256(maskOn.avxMask, _mm256_and_si256(this->status, maskOff.avxMask));

	if (this->isNotMarkedToRecalculate())
	{
		__m256i temp = _mm256_cmpeq_epi64(_mm256_xor_si256(oldStatus, this->status), _mm256_setzero_si256());
		temp = _mm256_and_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));
		if (_mm_movemask_epi8(_mm256_castsi256_si128(temp)) != 0xFFFF)
		{
			// Слово состояния контактов изменилось - надо ставить схемы на расчет
			this->markToRecalculate();
		}
	}
}
