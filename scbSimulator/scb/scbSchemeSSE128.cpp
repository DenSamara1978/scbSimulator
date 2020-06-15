#include "scbSchemeSSE128.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeSSE128::scbSchemeSSE128 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, prep_count, main_count, statsens_count, dynsens_count ),
	m_Status ( _mm_setzero_si128 ())
{
	const size_t size = 16 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m128i* > ( _mm_malloc ( size, 16 ) );
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

scbSchemeSSE128::~scbSchemeSSE128 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeSSE128::SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	this->m_PrepareCircuitMask [index] = _mm_load_si128 ( mask.SSE_mask );
	this->m_PrepareCircuitResult [index] = _mm_load_si128 ( result.SSE_mask );
}

void scbSchemeSSE128::SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	this->m_MainCircuitMask [index] = _mm_load_si128 ( mask.SSE_mask );
	this->m_MainCircuitResult [index] = _mm_load_si128 ( result.SSE_mask );
}

void scbSchemeSSE128::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	this->m_StaticSensitiveMask [index] = _mm_load_si128 ( mask.SSE_mask );
	this->m_StaticSensitiveResult [index] = _mm_load_si128 ( result.SSE_mask );
}

void scbSchemeSSE128::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	this->m_DynamicSensitiveMask [index] = _mm_load_si128 ( mask.SSE_mask );
	this->m_DynamicSensitiveResult [index] = _mm_load_si128 ( result.SSE_mask );
}

void scbSchemeSSE128::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m128i zero = _mm_setzero_si128 ();
	__m128i mask = this->m_Status;
	__m128i temp;

	const int loop1 = this->m_PrepareCircuitCount;
	if ( loop1 != 0 )
	{
		result.SSE_mask [0] = _mm_setzero_si128 ();

		for ( i = 0; i < loop1; i++ )
		{
			temp = _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask, this->m_PrepareCircuitMask [i] ), zero );
			temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
			temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
			result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_PrepareCircuitResult [i] ));
		}

		mask = _mm_or_si128 ( mask, result.SSE_mask [0] );
	}

	result.SSE_mask [0] = _mm_setzero_si128 ();

	const int loop2 = this->m_MainCircuitCount;
	for ( i = 0; i < loop2; i++ )
	{
		temp = _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask, this->m_MainCircuitMask [i] ), zero );
		temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
		temp = _mm_and_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_MainCircuitResult [i] ) );
	}

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeSSE128::SetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0x60, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] |= _rotl ( 1, bit & 0x1F );
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE128::ResetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0x60, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] &= ~( _rotl ( 1, bit & 0x1F ));
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE128::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	const __m128i old_status = this->m_Status;
	this->m_Status = _mm_or_si128 ( _mm_load_si128 ( mask_on.SSE_mask ), _mm_and_si128 ( this->m_Status, _mm_load_si128 ( mask_off.SSE_mask ) ) );

	if ( this->IsNotMarkedToRecalculate () && ( _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_xor_si128 ( old_status, this->m_Status ), _mm_setzero_si128 () ) ) != 0xFFFF ))
		this->MarkToRecalculate ();
}
