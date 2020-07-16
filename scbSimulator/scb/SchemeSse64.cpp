#include "SchemeSse64.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeSse64::SchemeSse64(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, (nPrepareCircuits + 1) & 0xFFFFFFFE, (nMainCircuits + 1) & 0xFFFFFFFE, (nStaticSensitives + 1) & 0xFFFFFFFE, (nDynamicSensitives + 1) & 0xFFFFFFFE),
	status(_mm_setzero_si128())
{
	const size_t size = 8 * 2 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives);
	this->memory = static_cast <__m128i*> (_mm_malloc(size, 16));
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + (this->nPrepareCircuits >> 1);
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits;
	this->mainCircuitResults = this->mainCircuitMasks + (this->nMainCircuits >> 1);
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits;
	this->staticSensitiveResults = this->staticSensitiveMasks + (this->nStaticSensitives >> 1);
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + (this->nDynamicSensitives >> 1);
	memset(this->memory, 0, size);
}

SchemeSse64::~SchemeSse64()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeSse64::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	const int row = index >> 1;
	const int element = index & 1;

	this->prepareCircuitMasks[row].m128i_u64[element] = mask.sseMask[0].m128i_u64[0];
	this->prepareCircuitResults[row].m128i_u64[element] = result.sseMask[0].m128i_u64[0];
}

void SchemeSse64::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	const int row = index >> 1;
	const int element = index & 1;

	this->mainCircuitMasks[row].m128i_u64[element] = mask.sseMask[0].m128i_u64[0];
	this->mainCircuitResults[row].m128i_u64[element] = result.sseMask[0].m128i_u64[0];
}

void SchemeSse64::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	const int row = index >> 1;
	const int element = index & 1;

	this->staticSensitiveMasks[row].m128i_u64[element] = mask.sseMask[0].m128i_u64[0];
	this->staticSensitiveResults[row].m128i_u64[element] = result.sseMask[0].m128i_u64[0];
}

void SchemeSse64::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	const int row = index >> 1;
	const int element = index & 1;

	this->dynamicSensitiveMasks[row].m128i_u64[element] = mask.sseMask[0].m128i_u64[0];
	this->dynamicSensitiveResults[row].m128i_u64[element] = result.sseMask[0].m128i_u64[0];
}

void SchemeSse64::recalculate()
{
	int i;

	OutputStream result;
	static const __m128i zero = _mm_setzero_si128();
	__m128i mask = this->status;
	__m128i temp;

	const int loop1 = this->nPrepareCircuits >> 1;
	if (loop1 != 0)
	{
		result.sseMask[0] = _mm_setzero_si128();

		for (i = 0; i < loop1; ++i)
		{
			temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->prepareCircuitMasks[i]), zero);
			temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
			result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->prepareCircuitResults[i]));
		}

		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(1, 0, 3, 2)));
		mask = _mm_or_si128(mask, result.sseMask[0]);
	}

	result.sseMask[0] = _mm_setzero_si128();

	const int loop2 = this->nMainCircuits >> 1;
	for (i = 0; i < loop2; ++i)
	{
		temp = _mm_cmpeq_epi32(_mm_andnot_si128(mask, this->mainCircuitMasks[i]), zero);
		temp = _mm_and_si128(temp, _mm_shuffle_epi32(temp, _MM_SHUFFLE(2, 3, 0, 1)));
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_and_si128(temp, this->mainCircuitResults[i]));
	}

	result.sseMask[0] = _mm_or_si128(result.sseMask[0], _mm_shuffle_epi32(result.sseMask[0], _MM_SHUFFLE(1, 0, 3, 2)));
	result.sseMask[1] = _mm_setzero_si128();

	for (const auto& device : this->devices)
		device->changeStatus(result);

	this->markRecalculated();
}

void SchemeSse64::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = (ptr[element] |= _rotl(1, bit & 0x1F));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeSse64::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = (ptr[element] &= ~(_rotl(1, bit & 0x1F)));
	if (old != ptr[element])
		this->markToRecalculate();
}

void SchemeSse64::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m128i oldStatus = this->status;
	this->status = _mm_shuffle_epi32(_mm_or_si128(_mm_loadu_si64(maskOn.sseMask), _mm_and_si128(this->status, _mm_loadu_si64(maskOff.sseMask))), _MM_SHUFFLE(1, 0, 1, 0));

	if (this->isNotMarkedToRecalculate() && (_mm_movemask_epi8(_mm_cmpeq_epi32(_mm_xor_si128(oldStatus, this->status), _mm_setzero_si128())) != 0xFFFF))
		this->markToRecalculate();
}
