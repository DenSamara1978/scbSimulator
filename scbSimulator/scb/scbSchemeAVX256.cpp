#include <intrin.h>

#include "scbSchemeAVX256.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeAVX256::scbSchemeAVX256 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, prep_count, main_count, statsens_count, dynsens_count ),
	m_Status ( _mm256_setzero_si256 ())
{
	const size_t size = 32 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m256i* > ( _mm_malloc ( size, 16 ) );
	this->m_PrepareCircuitMask = this->m_Memory;
	this->m_PrepareCircuitResult = this->m_PrepareCircuitMask + this->m_PrepareCircuitCount;
	this->m_MainCircuitMask = this->m_PrepareCircuitMask + this->m_PrepareCircuitCount * 2;
	this->m_MainCircuitResult = this->m_MainCircuitMask + this->m_MainCircuitCount;
	this->m_StaticSensitiveMask = this->m_MainCircuitMask + this->m_MainCircuitCount * 2;
	this->m_StaticSensitiveResult = this->m_StaticSensitiveMask + this->m_StaticSensitiveCount;
	this->m_DynamicSensitiveMask = this->m_StaticSensitiveMask + this->m_StaticSensitiveCount * 2;
	this->m_DynamicSensitiveResult = this->m_DynamicSensitiveMask + this->m_DynamicSensitiveCount;
	memset ( this->m_Memory, 0, size );
}

scbSchemeAVX256::~scbSchemeAVX256 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeAVX256::SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	this->m_PrepareCircuitMask [index] = mask.AVX_mask;
	this->m_PrepareCircuitResult [index] = result.AVX_mask;
}

void scbSchemeAVX256::SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	this->m_MainCircuitMask [index] = mask.AVX_mask;
	this->m_MainCircuitResult [index] = result.AVX_mask;
}

void scbSchemeAVX256::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	this->m_StaticSensitiveMask [index] = mask.AVX_mask;
	this->m_StaticSensitiveResult [index] = result.AVX_mask;
}

void scbSchemeAVX256::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	this->m_DynamicSensitiveMask [index] = mask.AVX_mask;
	this->m_DynamicSensitiveResult [index] = result.AVX_mask;
}

void scbSchemeAVX256::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m256i zero = _mm256_setzero_si256 ();
	__m256i mask = this->m_Status;
	__m256i temp;

	const int loop1 = this->m_PrepareCircuitCount;
	if ( loop1 != 0 )
	{
		result.AVX_mask = _mm256_setzero_si256 ();

		for ( i = 0; i < loop1; i++ )
		{
			temp = _mm256_cmpeq_epi64 ( _mm256_andnot_si256 ( mask, this->m_PrepareCircuitMask [i] ), zero );
			temp = _mm256_and_si256 ( temp, _mm256_permute4x64_epi64 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
			temp = _mm256_and_si256 ( temp, _mm256_permute4x64_epi64 ( temp, _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
			result.AVX_mask = _mm256_or_si256 ( result.AVX_mask, _mm256_and_si256 ( temp, this->m_PrepareCircuitResult [i] ) );
		}

		mask = _mm256_or_si256 ( mask, result.AVX_mask );
	}

	result.AVX_mask = _mm256_setzero_si256 ();

	const int loop2 = this->m_MainCircuitCount;
	for ( i = 0; i < loop2; i++ )
	{
		temp = _mm256_cmpeq_epi64 ( _mm256_andnot_si256 ( mask, this->m_MainCircuitMask [i] ), zero );
		temp = _mm256_and_si256 ( temp, _mm256_permute4x64_epi64 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
		temp = _mm256_and_si256 ( temp, _mm256_permute4x64_epi64 ( temp, _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
		result.AVX_mask = _mm256_or_si256 ( result.AVX_mask, _mm256_and_si256 ( temp, this->m_MainCircuitResult [i] ) );
	}

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeAVX256::SetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0xE0, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] |= _rotl ( 1, bit & 0x1F );
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeAVX256::ResetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0xE0, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] &= ~( _rotl ( 1, bit & 0x1F ));
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeAVX256::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	const __m256i old_status = this->m_Status;
	this->m_Status = _mm256_or_si256 ( mask_on.AVX_mask, _mm256_and_si256 ( this->m_Status, mask_off.AVX_mask ) );

	if ( this->IsNotMarkedToRecalculate () )
	{
		__m256i temp = _mm256_cmpeq_epi64 ( _mm256_xor_si256 ( old_status, this->m_Status ), _mm256_setzero_si256 () );
		temp = _mm256_and_si256 ( temp, _mm256_permute4x64_epi64 ( temp, _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
		if ( _mm_movemask_epi8 ( _mm256_castsi256_si128 ( temp )) != 0xFFFF )
		{
			// Слово состояния контактов изменилось - надо ставить схемы на расчет
			this->MarkToRecalculate ();
		}
	}
}
