#include "scbAbstractScheme.h"
#include "scbSchemeOutput.h"
#include "scbTimer.h"

scbAbstractScheme::~scbAbstractScheme ()
{
	if ( this->m_MarkedToRecalculate )
	{
		this->m_MarkedToRecalculate = false;
		scbTimer::Instance ()->DeleteSchemeToRecalculate ( this );
	}
	for ( auto& ptr : this->m_Devices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}
}

void scbAbstractScheme::SetDeviceCount ( int count )
{
	for ( auto& ptr : this->m_Devices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}
	this->m_Devices.resize ( count , nullptr );
}

void scbAbstractScheme::SetOutput ( int index, const wstring& name, int block )
{
	if ( ( index < 0 ) || ( index >= static_cast< int > ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;

	this->m_Devices [index] = new scbSchemeOutput ( this, name, block );
}

void scbAbstractScheme::MapInputOutput ( int output_index, int in_bit, int out_bit )
{
	if ( ( output_index >= 0 ) && ( output_index < static_cast<int> ( this->m_Devices.size ())) && ( this->m_Devices [output_index] != nullptr ) )
		this->m_Devices [output_index]->MapInputOutput ( in_bit, out_bit );
}
