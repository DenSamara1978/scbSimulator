#include "scbBus.h"
#include "scbSchemeOutput.h"

scbBus::scbBus ( const wstring& name, int length ) :
	scbAbstractScheme ( name )
{
	this->m_Status = new unsigned long [this->m_StatusCount = length];
	memset ( this->m_Status, 0, sizeof ( unsigned long ) * length );
}

scbBus::~scbBus ()
{
	if ( this->m_Status != nullptr )
	{
		delete [] this->m_Status;
		this->m_Status = nullptr;
		this->m_StatusCount = 0;
	}
}

void scbBus::Init ()
{
	// Ïףסעמי גûחמג
}

void scbBus::SetStatusBit ( int bit )
{
	// Ïףסעמי גûחמג
}

void scbBus::ResetStatusBit ( int bit )
{
	// Ïףסעמי גûחמג
}

void scbBus::Recalculate ()
{
	scbOutputStream result;
	unsigned long temp = 0;

	const int loop = this->m_StatusCount;
	for ( int i = 0; i < loop; i++ )
		temp |= this->m_Status [i];

	result.Mask [0] = ( temp == 0 ) ? 0 : 1;
	for ( const auto& ptr : this->m_Devices )
		ptr->ChangeStatus ( result );

	this->MarkRecalculated ();
}

void scbBus::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	bool changed = false;
	unsigned long old_val, new_val;

	const int loop = this->m_StatusCount;
	for ( int i = 0; i < loop; i++ )
	{
		new_val = ( this->m_Status [i] & mask_off.Mask [i] ) | mask_on.Mask [i];
		if ( !changed )
		{
			old_val = this->m_Status [i];
			if ( !changed )
			{
				if ( ( old_val != new_val ) && ( ( old_val & new_val ) == 0 ) )
					changed = true;
			}
		}
		this->m_Status [i] = new_val;
	}

	if ( changed )
		this->MarkToRecalculate ();
}
