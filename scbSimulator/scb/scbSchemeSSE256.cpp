#include "scbSchemeSSE256.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeSSE256::scbSchemeSSE256 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, prep_count, main_count, statsens_count, dynsens_count ),
	m_Status { _mm_setzero_si128 (), _mm_setzero_si128 () }
{
	const size_t size = 16 * 6 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m128i* > ( _mm_malloc ( size, 16 ));
	this->m_PrepareCircuitMask = this->m_Memory;
	this->m_PrepareCircuitResult = this->m_PrepareCircuitMask + this->m_PrepareCircuitCount * 2;
	this->m_MainCircuitMask = this->m_PrepareCircuitMask + this->m_PrepareCircuitCount * 6;
	this->m_MainCircuitResult = this->m_MainCircuitMask + this->m_MainCircuitCount * 2;
	this->m_StaticSensitiveMask = this->m_MainCircuitMask + this->m_MainCircuitCount * 6;
	this->m_StaticSensitiveResult = this->m_StaticSensitiveMask + this->m_StaticSensitiveCount * 2;
	this->m_DynamicSensitiveMask = this->m_StaticSensitiveMask + this->m_StaticSensitiveCount * 6;
	this->m_DynamicSensitiveResult = this->m_DynamicSensitiveMask + this->m_DynamicSensitiveCount * 2;
	memset ( this->m_Memory, 0, size );
}

scbSchemeSSE256::~scbSchemeSSE256 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeSSE256::SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	this->m_PrepareCircuitMask [index << 1] = mask.SSE_mask [0];
	this->m_PrepareCircuitMask [( index << 1 ) + 1] = mask.SSE_mask [1];
	this->m_PrepareCircuitResult [ index << 2] = _mm_setzero_si128 ();
	this->m_PrepareCircuitResult [( index << 2 ) + 1] = result.SSE_mask [0];
	this->m_PrepareCircuitResult [( index << 2 ) + 2] = _mm_setzero_si128 ();
	this->m_PrepareCircuitResult [( index << 2 ) + 3] = result.SSE_mask [1];
}

void scbSchemeSSE256::SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	this->m_MainCircuitMask [index << 1] = mask.SSE_mask [0];
	this->m_MainCircuitMask [( index << 1 ) + 1] = mask.SSE_mask [1];
	this->m_MainCircuitResult [index << 2] = _mm_setzero_si128 ();
	this->m_MainCircuitResult [( index << 2 ) + 1] = result.SSE_mask [0];
	this->m_MainCircuitResult [( index << 2 ) + 2] = _mm_setzero_si128 ();
	this->m_MainCircuitResult [( index << 2 ) + 3] = result.SSE_mask [1];
}

void scbSchemeSSE256::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	this->m_StaticSensitiveMask [index << 1] = mask.SSE_mask [0];
	this->m_StaticSensitiveMask [( index << 1 ) + 1] = mask.SSE_mask [1];
	this->m_StaticSensitiveResult [index << 2] = _mm_setzero_si128 ();
	this->m_StaticSensitiveResult [( index << 2 ) + 1] = result.SSE_mask [0];
	this->m_StaticSensitiveResult [( index << 2 ) + 2] = _mm_setzero_si128 ();
	this->m_StaticSensitiveResult [( index << 2 ) + 3] = result.SSE_mask [1];
}

void scbSchemeSSE256::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	this->m_DynamicSensitiveMask [index << 1] = mask.SSE_mask [0];
	this->m_DynamicSensitiveMask [( index << 1 ) + 1] = mask.SSE_mask [1];
	this->m_DynamicSensitiveResult [index << 2] = _mm_setzero_si128 ();
	this->m_DynamicSensitiveResult [( index << 2 ) + 1] = result.SSE_mask [0];
	this->m_DynamicSensitiveResult [( index << 2 ) + 2] = _mm_setzero_si128 ();
	this->m_DynamicSensitiveResult [( index << 2 ) + 3] = result.SSE_mask [1];
}

void scbSchemeSSE256::Recalculate ()
{
	int i, cmp1, cmp2, cmp;

	scbOutputStream result;
	static const __m128i zero = _mm_setzero_si128 ();
	__m128i mask [2] = { this->m_Status [0], this->m_Status [1] };

	const int loop1 = this->m_PrepareCircuitCount;
	if ( loop1 != 0 )
	{
		result.SSE_mask [0] = _mm_setzero_si128 ();
		result.SSE_mask [1] = _mm_setzero_si128 ();

		for ( i = 0; i < loop1; i++ )
		{
			cmp1 = _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask [0], this->m_PrepareCircuitMask [i << 1] ), zero ) );
			cmp2 = _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask [1], this->m_PrepareCircuitMask [( i << 1 ) + 1] ), zero ) );
			cmp = cmp1 & cmp2;
			cmp = cmp & ( cmp >> 8 );
			cmp = ( cmp & ( cmp >> 4 ) ) & 1;
			result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], this->m_PrepareCircuitResult [( i << 2 ) + cmp] );
			result.SSE_mask [1] = _mm_or_si128 ( result.SSE_mask [1], this->m_PrepareCircuitResult [( i << 2 ) + 2 + cmp] );
		}

		mask [0] = _mm_or_si128 ( mask [0], result.SSE_mask [0] );
		mask [1] = _mm_or_si128 ( mask [1], result.SSE_mask [1] );
	}

	result.SSE_mask [0] = _mm_setzero_si128 ();
	result.SSE_mask [1] = _mm_setzero_si128 ();

	const int loop2 = this->m_MainCircuitCount;
	for ( i = 0; i < loop2; i++ )
	{
		cmp1 = _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask [0], this->m_MainCircuitMask [i << 1] ), zero ) );
		cmp2 = _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_andnot_si128 ( mask [1], this->m_MainCircuitMask [( i << 1 ) + 1] ), zero ) );
		cmp = cmp1 & cmp2;
		cmp = cmp & ( cmp >> 8 );
		cmp = ( cmp & ( cmp >> 4 ) ) & 1;
		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], this->m_MainCircuitResult [( i << 2 ) + cmp] );
		result.SSE_mask [1] = _mm_or_si128 ( result.SSE_mask [1], this->m_MainCircuitResult [( i << 2 ) + 2 + cmp] );
	}

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeSSE256::SetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0xE0, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] |= _rotl ( 1, bit & 0x1F );
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE256::ResetStatusBit ( int bit )
{
	const int element = _rotr ( bit & 0xE0, 5 );
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [element];
	ptr [element] &= ~( _rotl ( 1, bit & 0x1F ) );
	if ( old != ptr [element] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE256::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	const __m128i old_status [2] = { this->m_Status [0], this->m_Status [1] };
	this->m_Status [0] = _mm_or_si128 ( _mm_load_si128 ( mask_on.SSE_mask ), _mm_and_si128 ( this->m_Status [0], _mm_load_si128 ( mask_off.SSE_mask ) ) );
	this->m_Status [1] = _mm_or_si128 ( _mm_load_si128 ( mask_on.SSE_mask + 1 ), _mm_and_si128 ( this->m_Status [1], _mm_load_si128 ( mask_off.SSE_mask + 1 ) ) );

	if ( this->IsNotMarkedToRecalculate () && ( _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_or_si128 ( _mm_xor_si128 ( old_status [0], this->m_Status [0] ), _mm_xor_si128 ( old_status [1], this->m_Status [1] )), _mm_setzero_si128 () ) ) != 0xFFFF ))
		this->MarkToRecalculate ();
}
