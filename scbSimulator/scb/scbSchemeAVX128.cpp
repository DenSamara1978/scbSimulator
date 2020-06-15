#include <intrin.h>

#include "scbSchemeAVX128.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeAVX128::scbSchemeAVX128 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, ( prep_count + 1 ) & 0xFFFFFFFE, ( main_count + 1 ) & 0xFFFFFFFE, ( statsens_count + 1 ) & 0xFFFFFFFE, ( dynsens_count + 1 ) & 0xFFFFFFFE ),
	m_Status ( _mm256_setzero_si256 ())
{
	const size_t size = 16 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m256i* > ( _mm_malloc ( size, 16 ) );
	this->m_PrepareCircuitMask = this->m_Memory;
	this->m_PrepareCircuitResult = this->m_PrepareCircuitMask + ( this->m_PrepareCircuitCount >> 1 );
	this->m_MainCircuitMask = this->m_PrepareCircuitMask + this->m_PrepareCircuitCount;
	this->m_MainCircuitResult = this->m_MainCircuitMask + ( this->m_MainCircuitCount >> 1 );
	this->m_StaticSensitiveMask = this->m_MainCircuitMask + this->m_MainCircuitCount;
	this->m_StaticSensitiveResult = this->m_StaticSensitiveMask + ( this->m_StaticSensitiveCount >> 1 );
	this->m_DynamicSensitiveMask = this->m_StaticSensitiveMask + this->m_StaticSensitiveCount;
	this->m_DynamicSensitiveResult = this->m_DynamicSensitiveMask + ( this->m_DynamicSensitiveCount >> 1 );
	memset ( this->m_Memory, 0, size );
}

scbSchemeAVX128::~scbSchemeAVX128 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeAVX128::SetPrepareCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	const int row = index >> 1;
	const int element = ( index & 1 ) << 1;

	this->m_PrepareCircuitMask[row].m256i_u64[element] = mask.AVX_mask.m256i_u64[0];
	this->m_PrepareCircuitMask[row].m256i_u64[element + 1] = mask.AVX_mask.m256i_u64[1];
	this->m_PrepareCircuitResult[row].m256i_u64[element] = result.AVX_mask.m256i_u64[0];
	this->m_PrepareCircuitResult[row].m256i_u64[element + 1] = result.AVX_mask.m256i_u64[1];
}

void scbSchemeAVX128::SetMainCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	const int row = index >> 1;
	const int element = (index & 1) << 1;

	this->m_MainCircuitMask[row].m256i_u64[element] = mask.AVX_mask.m256i_u64[0];
	this->m_MainCircuitMask[row].m256i_u64[element + 1] = mask.AVX_mask.m256i_u64[1];
	this->m_MainCircuitResult[row].m256i_u64[element] = result.AVX_mask.m256i_u64[0];
	this->m_MainCircuitResult[row].m256i_u64[element + 1] = result.AVX_mask.m256i_u64[1];
}

void scbSchemeAVX128::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	const int row = index >> 1;
	const int element = ( index & 1 ) << 1;

	this->m_StaticSensitiveMask [row].m256i_u64 [element] = mask.AVX_mask.m256i_u64 [0];
	this->m_StaticSensitiveMask [row].m256i_u64 [element + 1] = mask.AVX_mask.m256i_u64 [1];
	this->m_StaticSensitiveResult [row].m256i_u64 [element] = result.AVX_mask.m256i_u64 [0];
	this->m_StaticSensitiveResult [row].m256i_u64 [element + 1] = result.AVX_mask.m256i_u64 [1];
}

void scbSchemeAVX128::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	const int row = index >> 1;
	const int element = ( index & 1 ) << 1;

	this->m_DynamicSensitiveMask [row].m256i_u64 [element] = mask.AVX_mask.m256i_u64 [0];
	this->m_DynamicSensitiveMask [row].m256i_u64 [element + 1] = mask.AVX_mask.m256i_u64 [1];
	this->m_DynamicSensitiveResult [row].m256i_u64 [element] = result.AVX_mask.m256i_u64 [0];
	this->m_DynamicSensitiveResult [row].m256i_u64 [element + 1] = result.AVX_mask.m256i_u64 [1];
}

void scbSchemeAVX128::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m256i zero = _mm256_setzero_si256 ();
	__m256i mask = this->m_Status;
	__m256i temp;

	const int loop1 = this->m_PrepareCircuitCount >> 1;
	if (loop1 != 0)
	{
		result.AVX_mask = _mm256_setzero_si256 ();

		for (i = 0; i < loop1; i++)
		{
			temp = _mm256_cmpeq_epi64 (_mm256_andnot_si256 (mask, this->m_PrepareCircuitMask[i]), zero);
			temp = _mm256_and_si256 (temp, _mm256_permute4x64_epi64 (temp, _MM_SHUFFLE (2, 3, 0, 1)));
			result.AVX_mask = _mm256_or_si256 (result.AVX_mask, _mm256_and_si256 (temp, this->m_PrepareCircuitResult[i]));
		}

		mask = _mm256_or_si256 (mask, _mm256_or_si256 (result.AVX_mask, _mm256_permute4x64_epi64 (result.AVX_mask, _MM_SHUFFLE (1, 0, 3, 2))));
	}

	result.AVX_mask = _mm256_setzero_si256 ();

	const int loop2 = this->m_MainCircuitCount >> 1;
	for (i = 0; i < loop2; i++)
	{
		temp = _mm256_cmpeq_epi64 (_mm256_andnot_si256 (mask, this->m_MainCircuitMask[i]), zero);
		temp = _mm256_and_si256 (temp, _mm256_permute4x64_epi64 (temp, _MM_SHUFFLE (2, 3, 0, 1)));
		result.AVX_mask = _mm256_or_si256 (result.AVX_mask, _mm256_and_si256 (temp, this->m_MainCircuitResult[i]));
	}

	result.AVX_mask = _mm256_or_si256 (result.AVX_mask, _mm256_permute4x64_epi64 (result.AVX_mask, _MM_SHUFFLE (1, 0, 3, 2)));

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeAVX128::SetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x60, 5);
	unsigned long* ptr = reinterpret_cast< unsigned long* > (&(this->m_Status));
	const unsigned long old = ptr[element];
	ptr [element + 4] = ( ptr[element] |= _rotl (1, bit & 0x1F));
	if (old != ptr[element])
		this->MarkToRecalculate ();
}

void scbSchemeAVX128::ResetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x60, 5);
	unsigned long* ptr = reinterpret_cast< unsigned long* > (&(this->m_Status));
	const unsigned long old = ptr[element];
	ptr[element + 4] = ( ptr[element] &= ~(_rotl (1, bit & 0x1F)));
	if (old != ptr[element])
		this->MarkToRecalculate ();
}

void scbSchemeAVX128::CorrectInputStatus (const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id)
{
	const __m256i old_status = this->m_Status;
	this->m_Status = _mm256_permute4x64_epi64 ( _mm256_or_si256 (mask_on.AVX_mask, _mm256_and_si256 (this->m_Status, mask_off.AVX_mask)), _MM_SHUFFLE ( 1, 0, 1, 0 ));

	if ( this->IsNotMarkedToRecalculate () && ( (_mm_movemask_epi8 (_mm256_castsi256_si128 ( _mm256_cmpeq_epi64 ( _mm256_xor_si256 ( old_status, this->m_Status ), _mm256_setzero_si256 () ) )) & 0xFFFF ) != 0xFFFF))
		this->MarkToRecalculate ();
}
