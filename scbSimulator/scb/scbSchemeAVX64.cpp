#include <intrin.h>

#include "scbSchemeAVX64.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeAVX64::scbSchemeAVX64 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, ( prep_count + 3 ) & 0xFFFFFFFC, ( main_count + 3 ) & 0xFFFFFFFC, ( statsens_count + 3 ) & 0xFFFFFFFC, ( dynsens_count + 3 ) & 0xFFFFFFFC ),
	m_Status ( _mm256_setzero_si256 ())
{
	const size_t size = 8 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m256i* > ( _mm_malloc ( size, 16 ) );
	this->m_PrepareCircuitMask = this->m_Memory;
	this->m_PrepareCircuitResult = this->m_PrepareCircuitMask + ( this->m_PrepareCircuitCount >> 2 );
	this->m_MainCircuitMask = this->m_PrepareCircuitMask + ( this->m_PrepareCircuitCount >> 1 );
	this->m_MainCircuitResult = this->m_MainCircuitMask + ( this->m_MainCircuitCount >> 2 );
	this->m_StaticSensitiveMask = this->m_MainCircuitMask + ( this->m_MainCircuitCount >> 1 );
	this->m_StaticSensitiveResult = this->m_StaticSensitiveMask + ( this->m_StaticSensitiveCount >> 2 );
	this->m_DynamicSensitiveMask = this->m_StaticSensitiveMask + ( this->m_StaticSensitiveCount >> 1 );
	this->m_DynamicSensitiveResult = this->m_DynamicSensitiveMask + ( this->m_DynamicSensitiveCount >> 2 );
	memset ( this->m_Memory, 0, size );
}

scbSchemeAVX64::~scbSchemeAVX64 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeAVX64::SetPrepareCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	const int row = index >> 2;
	const int element = index & 3;

	this->m_PrepareCircuitMask[row].m256i_u64[element] = mask.AVX_mask.m256i_u64[0];
	this->m_PrepareCircuitResult[row].m256i_u64[element] = result.AVX_mask.m256i_u64[0];
}

void scbSchemeAVX64::SetMainCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	const int row = index >> 2;
	const int element = index & 3;

	this->m_MainCircuitMask[row].m256i_u64[element] = mask.AVX_mask.m256i_u64[0];
	this->m_MainCircuitResult[row].m256i_u64[element] = result.AVX_mask.m256i_u64[0];
}

void scbSchemeAVX64::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	const int row = index >> 2;
	const int element = index & 3;

	this->m_StaticSensitiveMask [row].m256i_u64 [element] = mask.AVX_mask.m256i_u64 [0];
	this->m_StaticSensitiveMask [row].m256i_u64 [element] = result.AVX_mask.m256i_u64 [0];
}

void scbSchemeAVX64::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	const int row = index >> 2;
	const int element = index & 3;

	this->m_DynamicSensitiveMask [row].m256i_u64 [element] = mask.AVX_mask.m256i_u64 [0];
	this->m_DynamicSensitiveMask [row].m256i_u64 [element] = result.AVX_mask.m256i_u64 [0];
}

void scbSchemeAVX64::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m256i zero = _mm256_setzero_si256 ();
	__m256i mask = this->m_Status;
	__m256i temp;

	const int loop1 = this->m_PrepareCircuitCount >> 2;
	if (loop1 != 0)
	{
		result.AVX_mask = _mm256_setzero_si256 ();

		for (i = 0; i < loop1; i++)
		{
			temp = _mm256_cmpeq_epi64 (_mm256_andnot_si256 (mask, this->m_PrepareCircuitMask[i]), zero);
			result.AVX_mask = _mm256_or_si256 (result.AVX_mask, _mm256_and_si256 (temp, this->m_PrepareCircuitResult[i]));
		}

		temp = _mm256_or_si256 ( result.AVX_mask, _mm256_permute4x64_epi64 (result.AVX_mask, _MM_SHUFFLE (2, 3, 0, 1)));
		mask = _mm256_or_si256 (mask, _mm256_or_si256 (temp, _mm256_permute4x64_epi64 (temp, _MM_SHUFFLE (1, 0, 3, 2))));
	}

	result.AVX_mask = _mm256_setzero_si256 ();

	const int loop2 = this->m_MainCircuitCount >> 2;
	for (i = 0; i < loop2; i++)
	{
		temp = _mm256_cmpeq_epi64 (_mm256_andnot_si256 (mask, this->m_MainCircuitMask[i]), zero);
		result.AVX_mask = _mm256_or_si256 (result.AVX_mask, _mm256_and_si256 (temp, this->m_MainCircuitResult[i]));
	}

	temp = _mm256_or_si256 (result.AVX_mask, _mm256_permute4x64_epi64 (result.AVX_mask, _MM_SHUFFLE (2, 3, 0, 1)));
	result.AVX_mask = _mm256_or_si256 (temp, _mm256_permute4x64_epi64 (temp, _MM_SHUFFLE (1, 0, 3, 2)));

	for (const auto& ptr : this->m_Devices)
		ptr->ChangeStatus (result);

	this->MarkRecalculated ();
}

void scbSchemeAVX64::SetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast< unsigned long* > (&(this->m_Status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = ptr[element + 4] = ptr[element + 6] = (ptr[element] |= _rotl (1, bit & 0x1F));
	if (old != ptr[element])
		this->MarkToRecalculate ();
}

void scbSchemeAVX64::ResetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x20, 5);
	unsigned long* ptr = reinterpret_cast< unsigned long* > (&(this->m_Status));
	const unsigned long old = ptr[element];
	ptr[element + 2] = ptr[element + 4] = ptr[element + 6] = (ptr[element] &= ~(_rotl (1, bit & 0x1F)));
	if (old != ptr[element])
		this->MarkToRecalculate ();
}

void scbSchemeAVX64::CorrectInputStatus (const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id)
{
	const __m256i old_status = this->m_Status;
	this->m_Status = _mm256_permute4x64_epi64 (_mm256_or_si256 (mask_on.AVX_mask, _mm256_and_si256 (this->m_Status, mask_off.AVX_mask)), _MM_SHUFFLE (0, 0, 0, 0));

	if ( this->IsNotMarkedToRecalculate () && ((_mm_movemask_epi8 (_mm256_castsi256_si128 ( _mm256_cmpeq_epi64 ( _mm256_xor_si256 ( old_status, this->m_Status ), _mm256_setzero_si256 () ) )) & 0xFF) != 0xFF ))
		this->MarkToRecalculate ();
}
