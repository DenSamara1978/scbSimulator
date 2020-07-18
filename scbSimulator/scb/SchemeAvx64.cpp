#include <intrin.h>

#include "SchemeAvx64.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;


SchemeAvx64::SchemeAvx64(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, (nPrepareCircuits + 3) & 0xFFFFFFFC, (nMainCircuits + 3) & 0xFFFFFFFC, (nStaticSensitives + 3) & 0xFFFFFFFC, (nDynamicSensitives + 3) & 0xFFFFFFFC),
	status(_mm256_setzero_si256()),
	sensitives(_mm256_setzero_si256())
{
	const size_t size = 8 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = static_cast <__m256i*> (_mm_malloc(size, 16));
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + (this->nPrepareCircuits >> 2);
	this->mainCircuitMasks = this->prepareCircuitMasks + (this->nPrepareCircuits >> 1);
	this->mainCircuitResults = this->mainCircuitMasks + (this->nMainCircuits >> 2);
	this->staticSensitiveMasks = this->mainCircuitMasks + (this->nMainCircuits >> 1);
	this->staticSensitiveResults = this->staticSensitiveMasks + (this->nStaticSensitives >> 2);
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + (this->nStaticSensitives >> 1);
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + (this->nDynamicSensitives >> 2);
	this->dynSensitiveMask = this->dynamicSensitiveMasks + (this->nDynamicSensitives >> 1);
	this->constSensitiveMask = this->dynSensitiveMask + 1;
	memset(this->memory, 0, size);
}

SchemeAvx64::~SchemeAvx64()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeAvx64::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0].m256i_u64[0] = constMask.avxMask.m256i_u64[0];
	this->dynSensitiveMask[0].m256i_u64[0] = dynMask.avxMask.m256i_u64[0];
}

void SchemeAvx64::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->prepareCircuitMasks[row].m256i_u64[element] = mask.avxMask.m256i_u64[0];
	this->prepareCircuitResults[row].m256i_u64[element] = result.avxMask.m256i_u64[0];
}

void SchemeAvx64::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->mainCircuitMasks[row].m256i_u64[element] = mask.avxMask.m256i_u64[0];
	this->mainCircuitResults[row].m256i_u64[element] = result.avxMask.m256i_u64[0];
}

void SchemeAvx64::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->staticSensitiveMasks[row].m256i_u64[element] = mask.avxMask.m256i_u64[0];
	this->staticSensitiveMasks[row].m256i_u64[element] = result.avxMask.m256i_u64[0];
}

void SchemeAvx64::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->dynamicSensitiveMasks[row].m256i_u64[element] = mask.avxMask.m256i_u64[0];
	this->dynamicSensitiveMasks[row].m256i_u64[element] = result.avxMask.m256i_u64[0];
}

void SchemeAvx64::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	OutputStream result;
	static const __m256i zero = _mm256_setzero_si256();
	__m256i temp;
	__m256i mask = this->status;

	const int loop1 = this->nPrepareCircuits >> 2;
	if (loop1 != 0)
	{
		result.avxMask = _mm256_setzero_si256();

		for (i = 0; i < loop1; i++)
		{
			temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->prepareCircuitMasks[i]), zero);
			result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->prepareCircuitResults[i]));
		}

		temp = _mm256_or_si256(result.avxMask, _mm256_permute4x64_epi64(result.avxMask, _MM_SHUFFLE(2, 3, 0, 1)));
		mask = _mm256_or_si256(mask, _mm256_or_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2))));
	}

	result.avxMask = _mm256_setzero_si256();

	const int loop2 = this->nMainCircuits >> 2;
	for (i = 0; i < loop2; i++)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->mainCircuitMasks[i]), zero);
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->mainCircuitResults[i]));
	}

	temp = _mm256_or_si256(result.avxMask, _mm256_permute4x64_epi64(result.avxMask, _MM_SHUFFLE(2, 3, 0, 1)));
	result.avxMask = _mm256_or_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));

	for (const auto& device : this->devices)
		device->changeStatus(result);

	this->markRecalculated();

	result.avxMask = this->constSensitiveMask[0];

	const int loop3 = this->nStaticSensitives >> 2;
	for (i = 0; i < loop3; ++i)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->staticSensitiveMasks[i]), zero);
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->staticSensitiveResults[i]));
	}

	const int loop4 = this->nDynamicSensitives >> 2;
	for (i = 0; i < loop4; ++i)
	{
		temp = _mm256_cmpeq_epi64(_mm256_andnot_si256(mask, this->dynamicSensitiveMasks[i]), zero);
		result.avxMask = _mm256_or_si256(result.avxMask, _mm256_and_si256(temp, this->dynamicSensitiveResults[i]));
	}

	temp = _mm256_or_si256(result.avxMask, _mm256_permute4x64_epi64(result.avxMask, _MM_SHUFFLE(2, 3, 0, 1)));
	this->sensitives = _mm256_or_si256(temp, _mm256_permute4x64_epi64(temp, _MM_SHUFFLE(1, 0, 3, 2)));

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeAvx64::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = ptr[element + 4] = ptr[element + 6] = (ptr[element] |= _rotl(1, bit & 0x1F));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeAvx64::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = ptr[element + 4] = ptr[element + 6] = (ptr[element] &= ~(_rotl(1, bit & 0x1F)));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeAvx64::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m256i oldStatus = this->status;
	this->status = _mm256_permute4x64_epi64(_mm256_or_si256(maskOn.avxMask, _mm256_and_si256(this->status, maskOff.avxMask)), _MM_SHUFFLE(0, 0, 0, 0));

	if (this->isNotMarkedToRecalculate())
	{
		if ((_mm_movemask_epi8(_mm256_castsi256_si128(_mm256_cmpeq_epi64(_mm256_xor_si256(oldStatus, this->status), _mm256_setzero_si256()))) & 0xFF) != 0xFF)
			this->markToRecalculate();
	}
}
