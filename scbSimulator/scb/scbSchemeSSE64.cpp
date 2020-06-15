#include "scbSchemeSSE64.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeSSE64::scbSchemeSSE64 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, ( prep_count + 1 ) & 0xFFFFFFFE, ( main_count + 1 ) & 0xFFFFFFFE, ( statsens_count + 1 ) & 0xFFFFFFFE, ( dynsens_count + 1 ) & 0xFFFFFFFE ),
	m_Status ( _mm_setzero_si128 ())
{
	const size_t size = 8 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m128i* > ( _mm_malloc ( size, 16 ) );
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

scbSchemeSSE64::~scbSchemeSSE64 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeSSE64::SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	const int row = index >> 1;
	const int element = index & 1;

	this->m_PrepareCircuitMask [row].m128i_u64 [element] = mask.SSE_mask [0].m128i_u64 [0];
	this->m_PrepareCircuitResult [row].m128i_u64 [element] = result.SSE_mask [0].m128i_u64 [0];
}

void scbSchemeSSE64::SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	const int row = index >> 1;
	const int element = index & 1;

	this->m_MainCircuitMask [row].m128i_u64 [element] = mask.SSE_mask [0].m128i_u64 [0];
	this->m_MainCircuitResult [row].m128i_u64 [element] = result.SSE_mask [0].m128i_u64 [0];
}

void scbSchemeSSE64::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	const int row = index >> 1;
	const int element = index & 1;

	this->m_StaticSensitiveMask [row].m128i_u64 [element] = mask.SSE_mask [0].m128i_u64 [0];
	this->m_StaticSensitiveResult [row].m128i_u64 [element] = result.SSE_mask [0].m128i_u64 [0];
}

void scbSchemeSSE64::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	const int row = index >> 1;
	const int element = index & 1;

	this->m_DynamicSensitiveMask [row].m128i_u64 [element] = mask.SSE_mask [0].m128i_u64 [0];
	this->m_DynamicSensitiveResult [row].m128i_u64 [element] = result.SSE_mask [0].m128i_u64 [0];
}

void scbSchemeSSE64::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m128i zero = _mm_setzero_si128 ();
	__m128i mask = this->m_Status;
	__m128i temp;

	const int loop1 = this->m_PrepareCircuitCount >> 1;
	if ( loop1 != 0 )
	{
		result.SSE_mask [0] = _mm_setzero_si128 ();

		for ( i = 0; i < loop1; i++ )
		{
			temp = _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask, this->m_PrepareCircuitMask [i] ), zero );
			temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
			result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_PrepareCircuitResult [i] ) );
		}

		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_shuffle_epi32 ( result.SSE_mask [0], _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
		mask = _mm_or_si128 ( mask, result.SSE_mask [0] );
	}

	result.SSE_mask [0] = _mm_setzero_si128 ();

	const int loop2 = this->m_MainCircuitCount >> 1;
	for ( i = 0; i < loop2; i++ )
	{
		temp = _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask, this->m_MainCircuitMask [i] ), zero );
		temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_MainCircuitResult [i] ) );
	}

	result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_shuffle_epi32 ( result.SSE_mask [0], _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
	result.SSE_mask [1] = _mm_setzero_si128 ();

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeSSE64::SetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0x20, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element + 2] = ( ptr [element] |= _rotl ( 1, bit & 0x1F ));
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE64::ResetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0x20, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element + 2] = ( ptr [element] &= ~( _rotl ( 1, bit & 0x1F ) ));
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE64::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	const __m128i old_status = this->m_Status;
	this->m_Status = _mm_shuffle_epi32 ( _mm_or_si128 ( _mm_loadu_si64 ( mask_on.SSE_mask ), _mm_and_si128 ( this->m_Status, _mm_loadu_si64 ( mask_off.SSE_mask ) ) ), _MM_SHUFFLE ( 1, 0, 1, 0 ));

	if ( this->IsNotMarkedToRecalculate () && ( _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_xor_si128 ( old_status, this->m_Status ), _mm_setzero_si128 () ) ) != 0xFFFF ))
		this->MarkToRecalculate ();
}
