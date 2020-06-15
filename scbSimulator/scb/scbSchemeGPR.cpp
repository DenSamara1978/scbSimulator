#include "scbSchemeGPR.h"
#include "scbAbstractSchemeDevice.h"

scbSchemeGPR::scbSchemeGPR (const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count) :
	scbScheme ( name, prep_count, main_count, statsens_count, dynsens_count ),
	m_Status { 0L, 0L, 0L, 0L }
{
	const size_t size = 4 * 2 * ( this->m_PrepareCircuitCount + this->m_MainCircuitCount + this->m_StaticSensitiveCount + this->m_DynamicSensitiveCount );
	this->m_Memory = new unsigned long [size << 2];
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

scbSchemeGPR::~scbSchemeGPR ()
{
	if ( this->m_Memory )
	{
		delete[] this->m_Memory;
		this->m_Memory = nullptr;
	}
}

void scbSchemeGPR::SetPrepareCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_PrepareCircuitCount )) return;

	memcpy (&( this->m_PrepareCircuitMask [index * 4]), &mask, 16);
	memcpy (&( this->m_PrepareCircuitResult [index * 4] ), &result, 16);
}

void scbSchemeGPR::SetMainCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_MainCircuitCount )) return;

	memcpy (&( this->m_MainCircuitMask [index * 4] ), &mask, 16);
	memcpy (&( this->m_MainCircuitResult [index * 4] ), &result, 16);
}

void scbSchemeGPR::SetStaticSensitiveCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_StaticSensitiveCount )) return;

	memcpy (&( this->m_StaticSensitiveMask [index * 4] ), &mask, 16);
	memcpy (&( this->m_StaticSensitiveResult [index * 4] ), &result, 16);
}

void scbSchemeGPR::SetDynamicSensitiveCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result)
{
	if (( index < 0 ) && ( index >= this->m_DynamicSensitiveCount )) return;

	memcpy (&( this->m_DynamicSensitiveMask [index * 4] ), &mask, 16);
	memcpy (&( this->m_DynamicSensitiveResult [index * 4] ), &result, 16);
}

void scbSchemeGPR::Recalculate ()
{
	int i;

	unsigned long result [4] { 0, 0, 0, 0 };
	unsigned long mask [] = { this->m_Status [0], this->m_Status [1], this->m_Status [2], this->m_Status [3] };
	unsigned long temp;

	const int loop1 = this->m_PrepareCircuitCount;
	if ( loop1 > 0 )
	{
		for ( i = 0; i < loop1; i++ )
		{
			temp = ( ~( mask [0] ) & this->m_PrepareCircuitMask [i * 4] ) | ( ~( mask [1] ) & this->m_PrepareCircuitMask [i * 4 + 1] ) | 
				( ~( mask [2] ) & this->m_PrepareCircuitMask [i * 4 + 2] ) | ( ~( mask [3] ) & this->m_PrepareCircuitMask [i * 4 + 3] );
			if ( temp == 0 )
			{
				result [0] |= this->m_PrepareCircuitResult [i * 4];
				result [1] |= this->m_PrepareCircuitResult [i * 4 + 1];
				result [2] |= this->m_PrepareCircuitResult [i * 4 + 2];
				result [3] |= this->m_PrepareCircuitResult [i * 4 + 3];
			}
		}

		mask [0] |= result [0];
		mask [1] |= result [1];
		mask [2] |= result [2];
		mask [3] |= result [3];

		memset (result, 0, 16);
	}

	const int loop2 = this->m_MainCircuitCount;
	for (i = 0; i < loop2; i++)
	{
		temp = ( ~( mask [0] ) & this->m_MainCircuitMask [i * 4] ) | ( ~( mask [1] ) & this->m_MainCircuitMask [i * 4 + 1] ) |
			( ~( mask [2] ) & this->m_MainCircuitMask [i * 4 + 2] ) | ( ~( mask [3] ) & this->m_MainCircuitMask [i * 4 + 3] );
		if ( temp == 0 )
		{
			result [0] |= this->m_MainCircuitResult [i * 4];
			result [1] |= this->m_MainCircuitResult [i * 4 + 1];
			result [2] |= this->m_MainCircuitResult [i * 4 + 2];
			result [3] |= this->m_MainCircuitResult [i * 4 + 3];
		}
	}

	scbOutputStream stream;
	memcpy ( &( stream.Mask ), result, 16);
	for (const auto& ptr : this->m_Devices)
		ptr->ChangeStatus (stream);

	this->MarkRecalculated ();
}

void scbSchemeGPR::SetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x60, 5);
	const unsigned long old = this->m_Status [element];
	this->m_Status [element] |= _rotl (1, bit & 0x1F);
	if (old != this->m_Status [element])
		this->MarkToRecalculate ();
}

void scbSchemeGPR::ResetStatusBit (int bit)
{
	const int element = _rotr (bit & 0x60, 5);
	const unsigned long old = this->m_Status [element];
	this->m_Status [element] &= ~(_rotl (1, bit & 0x1F));
	if (old != this->m_Status [element])
		this->MarkToRecalculate ();
}

void scbSchemeGPR::CorrectInputStatus (const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id)
{
	unsigned long difference = 0;
	unsigned long old_status;

	for ( int i = 0; i < 4; i++ )
	{
		old_status = this->m_Status [i];
		this->m_Status [i] = ( this->m_Status [i] & mask_off.Mask [i] ) | mask_on.Mask [i];
		difference |= old_status ^ this->m_Status [i];
	}

	if ( difference != 0 )
	{
		// Слово состояния контактов изменилось - надо ставить схемы на расчет
		this->MarkToRecalculate ();
	}
}
