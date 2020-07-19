#include "SchemeSse256.h"
#include "AbstractSchemeDevice.h"
#include "..\util\range.h"

using namespace scb;

using util::inRange;

SchemeSse256::SchemeSse256(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives) :
	Scheme(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives),
	status {_mm_setzero_si128(), _mm_setzero_si128()},
	sensitives {_mm_setzero_si128(), _mm_setzero_si128()},
	staticSensitives {_mm_setzero_si128(), _mm_setzero_si128()}
{
	const size_t size = 16 * 6 * (this->nPrepareCircuits + this->nMainCircuits + this->nStaticSensitives + this->nDynamicSensitives + 1);
	this->memory = static_cast <__m128i*> (_mm_malloc(size, 16));
	this->prepareCircuitMasks = this->memory;
	this->prepareCircuitResults = this->prepareCircuitMasks + this->nPrepareCircuits * 2;
	this->mainCircuitMasks = this->prepareCircuitMasks + this->nPrepareCircuits * 6;
	this->mainCircuitResults = this->mainCircuitMasks + this->nMainCircuits * 2;
	this->staticSensitiveMasks = this->mainCircuitMasks + this->nMainCircuits * 6;
	this->staticSensitiveResults = this->staticSensitiveMasks + this->nStaticSensitives * 2;
	this->dynamicSensitiveMasks = this->staticSensitiveMasks + this->nStaticSensitives * 6;
	this->dynamicSensitiveResults = this->dynamicSensitiveMasks + this->nDynamicSensitives * 2;
	this->dynSensitiveMask = this->dynamicSensitiveMasks + this->nDynamicSensitives * 6;
	this->constSensitiveMask = this->dynSensitiveMask + 2;
	memset(this->memory, 0, size);
}

SchemeSse256::~SchemeSse256()
{
	if (this->memory)
	{
		_mm_free(this->memory);
		this->memory = nullptr;
	}
}

void SchemeSse256::setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask)
{
	this->constSensitiveMask[0] = constMask.sseMask[0];
	this->constSensitiveMask[1] = constMask.sseMask[1];
	this->dynSensitiveMask[0] = dynMask.sseMask[0];
	this->dynSensitiveMask[1] = dynMask.sseMask[1];
}

void SchemeSse256::setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nPrepareCircuits);
	if (!isInRange)
		return;

	this->prepareCircuitMasks[index << 1] = mask.sseMask[0];
	this->prepareCircuitMasks[(index << 1) + 1] = mask.sseMask[1];
	this->prepareCircuitResults[index << 2] = _mm_setzero_si128();
	this->prepareCircuitResults[(index << 2) + 1] = result.sseMask[0];
	this->prepareCircuitResults[(index << 2) + 2] = _mm_setzero_si128();
	this->prepareCircuitResults[(index << 2) + 3] = result.sseMask[1];
}

void SchemeSse256::setMainCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nMainCircuits);
	if (!isInRange)
		return;

	this->mainCircuitMasks[index << 1] = mask.sseMask[0];
	this->mainCircuitMasks[(index << 1) + 1] = mask.sseMask[1];
	this->mainCircuitResults[index << 2] = _mm_setzero_si128();
	this->mainCircuitResults[(index << 2) + 1] = result.sseMask[0];
	this->mainCircuitResults[(index << 2) + 2] = _mm_setzero_si128();
	this->mainCircuitResults[(index << 2) + 3] = result.sseMask[1];
}

void SchemeSse256::setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nStaticSensitives);
	if (!isInRange)
		return;

	this->staticSensitiveMasks[index << 1] = mask.sseMask[0];
	this->staticSensitiveMasks[(index << 1) + 1] = mask.sseMask[1];
	this->staticSensitiveResults[index << 2] = _mm_setzero_si128();
	this->staticSensitiveResults[(index << 2) + 1] = result.sseMask[0];
	this->staticSensitiveResults[(index << 2) + 2] = _mm_setzero_si128();
	this->staticSensitiveResults[(index << 2) + 3] = result.sseMask[1];
}

void SchemeSse256::setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result)
{
	auto isInRange = inRange(index, this->nDynamicSensitives);
	if (!isInRange)
		return;

	this->dynamicSensitiveMasks[index << 1] = mask.sseMask[0];
	this->dynamicSensitiveMasks[(index << 1) + 1] = mask.sseMask[1];
	this->dynamicSensitiveResults[index << 2] = _mm_setzero_si128();
	this->dynamicSensitiveResults[(index << 2) + 1] = result.sseMask[0];
	this->dynamicSensitiveResults[(index << 2) + 2] = _mm_setzero_si128();
	this->dynamicSensitiveResults[(index << 2) + 3] = result.sseMask[1];
}

void SchemeSse256::recalculate()
{
	LARGE_INTEGER startTime, endTime;
	QueryPerformanceCounter(&startTime);

	int i, cmp1, cmp2, cmp;

	OutputStream result;
	static const __m128i zero = _mm_setzero_si128();
	__m128i mask[2] = { this->status[0], this->status[1] };

	if (this->isMarkedToFullRecalculating())
	{
		const int loop1 = this->nPrepareCircuits;
		if (loop1 != 0)
		{
			result.sseMask[0] = _mm_setzero_si128();
			result.sseMask[1] = _mm_setzero_si128();

			for (i = 0; i < loop1; ++i)
			{
				cmp1 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[0], this->prepareCircuitMasks[i << 1]), zero));
				cmp2 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[1], this->prepareCircuitMasks[(i << 1) + 1]), zero));
				cmp = cmp1 & cmp2;
				cmp = cmp & (cmp >> 8);
				cmp = (cmp & (cmp >> 4)) & 1;
				result.sseMask[0] = _mm_or_si128(result.sseMask[0], this->prepareCircuitResults[(i << 2) + cmp]);
				result.sseMask[1] = _mm_or_si128(result.sseMask[1], this->prepareCircuitResults[(i << 2) + 2 + cmp]);
			}

			mask[0] = _mm_or_si128(mask[0], result.sseMask[0]);
			mask[1] = _mm_or_si128(mask[1], result.sseMask[1]);
		}

		result.sseMask[0] = _mm_setzero_si128();
		result.sseMask[1] = _mm_setzero_si128();

		const int loop2 = this->nMainCircuits;
		for (i = 0; i < loop2; ++i)
		{
			cmp1 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[0], this->mainCircuitMasks[i << 1]), zero));
			cmp2 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[1], this->mainCircuitMasks[(i << 1) + 1]), zero));
			cmp = cmp1 & cmp2;
			cmp = cmp & (cmp >> 8);
			cmp = (cmp & (cmp >> 4)) & 1;
			result.sseMask[0] = _mm_or_si128(result.sseMask[0], this->mainCircuitResults[(i << 2) + cmp]);
			result.sseMask[1] = _mm_or_si128(result.sseMask[1], this->mainCircuitResults[(i << 2) + 2 + cmp]);
		}

		for (const auto& device : this->devices)
			device->changeStatus(result);

		result.sseMask[0] = _mm_setzero_si128();
		result.sseMask[1] = _mm_setzero_si128();

		const int loop3 = this->nStaticSensitives;
		for (i = 0; i < loop3; ++i)
		{
			cmp1 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[0], this->staticSensitiveMasks[i << 1]), zero));
			cmp2 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[1], this->staticSensitiveMasks[(i << 1) + 1]), zero));
			cmp = cmp1 & cmp2;
			cmp = cmp & (cmp >> 8);
			cmp = (cmp & (cmp >> 4)) & 1;
			result.sseMask[0] = _mm_or_si128(result.sseMask[0], this->staticSensitiveResults[(i << 2) + cmp]);
			result.sseMask[1] = _mm_or_si128(result.sseMask[1], this->staticSensitiveResults[(i << 2) + 2 + cmp]);
		}

		this->staticSensitives[0] = result.sseMask[0];
		this->staticSensitives[1] = result.sseMask[1];
	}

	result.sseMask[0] = _mm_or_si128(this->constSensitiveMask[0], this->staticSensitives[0]);
	result.sseMask[1] = _mm_or_si128(this->constSensitiveMask[1], this->staticSensitives[1]);

	const int loop4 = this->nDynamicSensitives;
	for (i = 0; i < loop4; ++i)
	{
		cmp1 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[0], this->dynamicSensitiveMasks[i << 1]), zero));
		cmp2 = _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_andnot_si128(mask[1], this->dynamicSensitiveMasks[(i << 1) + 1]), zero));
		cmp = cmp1 & cmp2;
		cmp = cmp & (cmp >> 8);
		cmp = (cmp & (cmp >> 4)) & 1;
		result.sseMask[0] = _mm_or_si128(result.sseMask[0], this->dynamicSensitiveResults[(i << 2) + cmp]);
		result.sseMask[1] = _mm_or_si128(result.sseMask[1], this->dynamicSensitiveResults[(i << 2) + 2 + cmp]);
	}

	this->sensitives[0] = result.sseMask[0];
	this->sensitives[1] = result.sseMask[1];
	this->markRecalculated();

	QueryPerformanceCounter(&endTime);
	this->workingTimes.push_back(this->getDiffTime(startTime, endTime));
}

void SchemeSse256::setStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] |= _rotl(1, bit & 0x1F);
	if (old != ptr[element])
		this->markToFullRecalculating();
}

void SchemeSse256::resetStatusBit(int bit)
{
	const int element = _rotr(bit & 0xE0, 5);
	unsigned long* ptr = reinterpret_cast<unsigned long*> (&(this->status));
	const unsigned long old = ptr[element];
	ptr[element] &= ~(_rotl(1, bit & 0x1F));
	if (old != ptr[element])
		this->markToFullRecalculating();
}

void SchemeSse256::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	const __m128i oldStatus[2] = {this->status[0], this->status[1]};
	this->status[0] = _mm_or_si128(maskOn.sseMask[0], _mm_and_si128(this->status[0], maskOff.sseMask[0]));
	this->status[1] = _mm_or_si128(maskOn.sseMask[1], _mm_and_si128(this->status[1], maskOff.sseMask[1]));

	if (this->isNotMarkedToRecalculate())
	{
		const __m128i difference0 = _mm_xor_si128(oldStatus[0], this->status[0]);
		const __m128i difference1 = _mm_xor_si128(oldStatus[1], this->status[1]);
		const __m128i sensDifference = _mm_or_si128(_mm_and_si128(difference0, this->sensitives[0]), _mm_and_si128(difference1, this->sensitives[1]));

		if (_mm_movemask_epi8(_mm_cmpeq_epi32(sensDifference, _mm_setzero_si128())) != 0xFFFF)
			this->markToFullRecalculating();
		else
		{
			const __m128i dynDifference = _mm_or_si128(_mm_and_si128(difference0, this->dynSensitiveMask[0]), _mm_and_si128(difference1, this->dynSensitiveMask[1]));
			if (_mm_movemask_epi8(_mm_cmpeq_epi32(dynDifference, _mm_setzero_si128())) != 0xFFFF)
				this->markToDynamicSensitivesRecalculating();
		}
	}
}
