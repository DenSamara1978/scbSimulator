#include "SchemeSse32.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeSse32::SchemeSse32(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, (nPrepareCircuits + 3) & 0xFFFFFFFC, (nMainCircuits + 3) & 0xFFFFFFFC, (nStaticSensitives + 3) & 0xFFFFFFFC, (nDynamicSensitives + 3) & 0xFFFFFFFC),
	status(_mm_setzero_si128()),
	sensitives(_mm_setzero_si128())
{
	const size_t size = 4 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = static_cast <__m128i*> (_mm_malloc(size, 16));
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

SchemeSse32::~SchemeSse32()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeSse32::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0].m128i_u32[0] = constMask.sseMask[0].m128i_u32[0];
	this->dynSensitiveMask[0].m128i_u32[0] = dynMask.sseMask[0].m128i_u32[0];
}

void SchemeSse32::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->prepareCircuitMasks[row].m128i_u32[element] = mask.sseMask[0].m128i_u32[0];
	this->prepareCircuitResults[row].m128i_u32[element] = result.sseMask[0].m128i_u32[0];
}

void SchemeSse32::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->mainCircuitMasks[row].m128i_u32[element] = mask.sseMask[0].m128i_u32[0];
	this->mainCircuitResults[row].m128i_u32[element] = result.sseMask[0].m128i_u32[0];
}

void SchemeSse32::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->staticSensitiveMasks[row].m128i_u32[element] = mask.sseMask[0].m128i_u32[0];
	this->staticSensitiveResults[row].m128i_u32[element] = result.sseMask[0].m128i_u32[0];
}

void SchemeSse32::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	const int row = index >> 2;
	const int element = index & 3;

	this->dynamicSensitiveMasks[row].m128i_u32[element] = mask.sseMask[0].m128i_u32[0];
	this->dynamicSensitiveResults[row].m128i_u32[element] = result.sseMask[0].m128i_u32[0];
}

void SchemeSse32::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i;

	OutputStream result;
	static const __m128i zero = _mm_setzero_si128();
	__m128i temp;
	__m128i mask = this->status;

	const int loop1 = this->nPrepareCircuits >> 2;
	if (loop1 != 0)
	{
		result.sseMask[0] = _mm_setzero_si128();

		for (i = 0; i < loop1; ++i)
		{
			temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->prepareCircuitMasks[i]), zero);
			result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->prepareCircuitResults[i]));
		}

		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(2, 3, 0, 1)));
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(1, 0, 3, 2)));
		mask = _mm_or_si128(mask, result.sseMask[0]);
	}

	result.sseMask[0] = _mm_setzero_si128();

	const int loop2 = this->nMainCircuits >> 2;
	for (i = 0; i < loop2; ++i)
	{
		temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->mainCircuitMasks[i]), zero);
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->mainCircuitResults[i]));
	}

	result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(2, 3, 0, 1)));
	result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(1, 0, 3, 2)));
	result.sseMask[1] = _mm_setzero_si128();

	for (const auto& device : this->devices)
		device->changeStatus(result);

	this->markRecalculated();

	result.sseMask[0] = this->constSensitiveMask[0];

	const int loop3 = this->nStaticSensitives >> 2;
	for (i = 0; i < loop3; ++i)
	{
		temp = _mm_cmpeq_epi16(_mm_andnot_si128(mask, this->staticSensitiveMasks[i]), zero);
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->staticSensitiveResults[i]));
	}

	const int loop4 = this->nDynamicSensitives >> 2;
	for (i = 0; i < loop4; ++i)
	{
		temp = _mm_cmpeq_epi16(_mm_andnot_si128(mask, this->dynamicSensitiveMasks[i]), zero);
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->dynamicSensitiveResults[i]));
	}

	result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(2, 3, 0, 1)));
	this->sensitives = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(1, 0, 3, 2)));

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeSse32::setStatusBit(int bit)
{
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[0];
	ptr[3] = ptr[2] = ptr[1] = (ptr[0] |= _rotl(1, bit & 0x1F));
	if (old != ptr[0])
		this->markToRecalculate();
}

void SchemeSse32::resetStatusBit(int bit)
{
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[0];
	ptr[3] = ptr[2] = ptr[1] = (ptr[0] &= ~(_rotl(1, bit & 0x1F)));
	if (old != ptr[0])
		this->markToRecalculate();
}

void SchemeSse32::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m128i oldStatus = this->status;
	this->status = _mm_shuffle_epi32(_mm_or_si128(_mm_loadu_si32(maskOn.sseMask), _mm_and_si128(this->status, _mm_loadu_si32(maskOff.sseMask))), _MM_SHUFFLE(0, 0, 0, 0));

	if (this->isNotMarkedToRecalculate())
	{
		if (_mm_movemask_epi8(_mm_cmpeq_epi32(_mm_xor_si128(oldStatus, this->status), _mm_setzero_si128())) != 0xFFFF)
			this->markToRecalculate();
	}
}
