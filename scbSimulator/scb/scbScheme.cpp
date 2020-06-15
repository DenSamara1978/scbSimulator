#include "scbScheme.h"
#include "scbSchemeOutput.h"
#include "scbNeutralRelay.h"
#include "scbPolarRelay.h"

scbScheme::scbScheme ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count ) :
	scbAbstractScheme ( name ),
	m_MainCircuitCount ( main_count ),
	m_StaticSensitiveCount ( statsens_count ),
	m_DynamicSensitiveCount ( dynsens_count ),
	m_PrepareCircuitCount ( prep_count )
{

}

scbScheme::~scbScheme ()
{

}

void scbScheme::SetPolarRelay ( int index, int dir_bit, int rev_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;

	this->m_Devices [index] = new scbPolarRelay ( this, dir_bit, rev_bit );
}

void scbScheme::SetNeutralRelay ( int index, int on_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;

	this->m_Devices [index] = new scbNeutralRelay ( this, on_bit );
}

void scbScheme::SetNeutralRelay ( int index, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;

	this->m_Devices [index] = new scbNeutralRelay ( this, on_bit, off_bit );
}

void scbScheme::SetNeutralRelay ( int index, int on_bit, int off_bit, int on_bridge_bit, int off_bridge_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;

	this->m_Devices [index] = new scbNeutralRelay ( this, on_bit, off_bit, on_bridge_bit, off_bridge_bit );
}

void scbScheme::AddRelayTimeSample ( int index, int from_mode, int to_mode, int start, int shift )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	dynamic_cast < scbRelay* > ( this->m_Devices [index] )->SetSample ( from_mode, to_mode, start, shift );
}

void scbScheme::AddRelayConvertation ( int index, int in_bit, int out_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size () ) ) ) return;
	dynamic_cast < scbRelay* > ( this->m_Devices [index] )->MapInputOutput ( in_bit, out_bit );
}

void scbScheme::Init ()
{
	for ( const auto& ptr : this->m_Devices )
		if ( ptr != nullptr )
			ptr->Init ();
}

void scbScheme::MapInputOutput ( int output_index, int in_bit, int out_bit )
{
	this->m_Devices [output_index]->MapInputOutput ( in_bit, out_bit );
}
