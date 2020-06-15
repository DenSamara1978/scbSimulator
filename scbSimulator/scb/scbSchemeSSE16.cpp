#include "scbSchemeSSE16.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeSSE16::scbSchemeSSE16 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbScheme ( name, ( prep_count + 7 ) & 0xFFFFFFF8, ( main_count + 7 ) & 0xFFFFFFF8, ( statsens_count + 7 ) & 0xFFFFFFF8, ( dynsens_count + 7 ) & 0xFFFFFFF8 ),
	m_Status ( _mm_setzero_si128 ())
{
	const size_t size = 2 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = static_cast < __m128i* > ( _mm_malloc ( size, 16 ) );
	this->m_PrepareCircuitMask = this->m_Memory;
	this->m_PrepareCircuitResult = this->m_PrepareCircuitMask + ( this->m_PrepareCircuitCount >> 3 );
	this->m_MainCircuitMask = this->m_PrepareCircuitMask + ( this->m_PrepareCircuitCount >> 2 );
	this->m_MainCircuitResult = this->m_MainCircuitMask + ( this->m_MainCircuitCount >> 3 );
	this->m_StaticSensitiveMask = this->m_MainCircuitMask + ( this->m_MainCircuitCount >> 2 );
	this->m_StaticSensitiveResult = this->m_StaticSensitiveMask + ( this->m_StaticSensitiveCount >> 3 );
	this->m_DynamicSensitiveMask = this->m_StaticSensitiveMask + ( this->m_StaticSensitiveCount >> 2 );
	this->m_DynamicSensitiveResult = this->m_DynamicSensitiveMask + ( this->m_DynamicSensitiveCount >> 3 );
	memset ( this->m_Memory, 0, size );
}

scbSchemeSSE16::~scbSchemeSSE16 ()
{
	if ( this->m_Memory )
	{
		_mm_free ( this->m_Memory );
		this->m_Memory = nullptr;
	}
}

void scbSchemeSSE16::SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	const int row = index >> 3;
	const int element = index & 7;

	this->m_PrepareCircuitMask [row].m128i_u16 [element] = mask.SSE_mask [0].m128i_u16 [0];
	this->m_PrepareCircuitResult [row].m128i_u16 [element] = result.SSE_mask [0].m128i_u16 [0];
}

void scbSchemeSSE16::SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	const int row = index >> 3;
	const int element = index & 7;

	this->m_MainCircuitMask [row].m128i_u16 [element] = mask.SSE_mask [0].m128i_u16 [0];
	this->m_MainCircuitResult [row].m128i_u16 [element] = result.SSE_mask [0].m128i_u16 [0];
}

void scbSchemeSSE16::SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	const int row = index >> 3;
	const int element = index & 7;

	this->m_StaticSensitiveMask [row].m128i_u16 [element] = mask.SSE_mask [0].m128i_u16 [0];
	this->m_StaticSensitiveResult [row].m128i_u16 [element] = result.SSE_mask [0].m128i_u16 [0];
}

void scbSchemeSSE16::SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result )
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	const int row = index >> 3;
	const int element = index & 7;

	this->m_DynamicSensitiveMask [row].m128i_u16 [element] = mask.SSE_mask [0].m128i_u16 [0];
	this->m_DynamicSensitiveResult [row].m128i_u16 [element] = result.SSE_mask [0].m128i_u16 [0];
}

void scbSchemeSSE16::Recalculate ()
{
	int i;

	scbOutputStream result;
	static const __m128i zero = _mm_setzero_si128 ();
	__m128i mask = this->m_Status;
	__m128i temp;

	const int loop1 = this->m_PrepareCircuitCount >> 3;
	if ( loop1 != 0 )
	{
		result.SSE_mask [0] = _mm_setzero_si128 ();

		for ( i = 0; i < loop1; i++ )
		{
			temp = _mm_cmpeq_epi16 ( _mm_andnot_si128 ( mask, this->m_PrepareCircuitMask [i] ), zero );
			result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_PrepareCircuitResult [i] ) );
		}

		temp = _mm_or_si128 ( result.SSE_mask [0], _mm_shufflehi_epi16 ( _mm_shufflelo_epi16 ( result.SSE_mask [0], _MM_SHUFFLE ( 2, 3, 0, 1 ) ), _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
		result.SSE_mask [0] = _mm_or_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_shuffle_epi32 ( result.SSE_mask [0], _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
		mask = _mm_or_si128 ( mask, result.SSE_mask [0] );
	}

	result.SSE_mask [0] = _mm_setzero_si128 ();

	const int loop2 = this->m_MainCircuitCount >> 3;
	for ( i = 0; i < loop2; i++ )
	{
		temp = _mm_cmpeq_epi16 ( _mm_andnot_si128 ( mask, this->m_MainCircuitMask [i] ), zero );
		result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_and_si128 ( temp, this->m_MainCircuitResult [i] ) );
	}

	temp = _mm_or_si128 ( result.SSE_mask [0], _mm_shufflehi_epi16 ( _mm_shufflelo_epi16 ( result.SSE_mask [0], _MM_SHUFFLE ( 2, 3, 0, 1 ) ), _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
	result.SSE_mask [0] = _mm_or_si128 ( temp, _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
	result.SSE_mask [0] = _mm_or_si128 ( result.SSE_mask [0], _mm_shuffle_epi32 ( result.SSE_mask [0], _MM_SHUFFLE ( 1, 0, 3, 2 ) ) );
	result.SSE_mask [1] = _mm_setzero_si128 ();

	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbSchemeSSE16::SetStatusBit ( int bit )
{
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [0];
	ptr [3] = ptr [2] = ptr [1] = ( ptr [0] |= ( _rotl ( 1, bit & 0x0F ) | _rotl ( 1, ( ( bit & 0x0F ) + 16 ) ) ));
	if ( old != ptr [0] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE16::ResetStatusBit ( int bit )
{
	unsigned long* ptr = reinterpret_cast< unsigned long* > ( &( this->m_Status ) );
	const unsigned long old = ptr [0];
	ptr [3] = ptr [2] = ptr [1] = ( ptr [0] &= ~( _rotl ( 1, bit & 0x0F ) | _rotl ( 1, (( bit & 0x0F ) + 16 ) ) ) );
	if ( old != ptr [0] )
		this->MarkToRecalculate ();
}

void scbSchemeSSE16::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	const __m128i old_status = this->m_Status;
	__m128i temp = _mm_or_si128 ( _mm_loadu_si16 ( mask_on.SSE_mask ), _mm_and_si128 ( this->m_Status, _mm_loadu_si16 ( mask_off.SSE_mask ) ) );
	temp = _mm_or_si128 ( temp, _mm_shufflelo_epi16 ( temp, _MM_SHUFFLE ( 2, 3, 0, 1 ) ) );
	this->m_Status = _mm_shuffle_epi32 ( temp, _MM_SHUFFLE ( 0, 0, 0, 0 ) );

	if ( this->IsNotMarkedToRecalculate () && ( _mm_movemask_epi8 ( _mm_cmpeq_epi32 ( _mm_xor_si128 ( old_status, this->m_Status ), _mm_setzero_si128 () ) ) != 0xFFFF ))
		this->MarkToRecalculate ();
}
