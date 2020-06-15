#include "scbPultTablo.h"
#include "scbPultTabloButtonKmd.h"
#include "scbPultTabloButtonKmdf.h"
#include "scbPultTabloButtonSchm1m.h"
#include "scbPultTabloCommutatorKmd.h"
#include "scbPultTabloCommutatorKmt.h"
#include "scbPultTabloLampGroup.h"
#include "scbPultTabloAmpermeter.h"
#include "scbPultTabloBell.h"
#include "scbSchemeOutput.h"

scbPultTablo::scbPultTablo ( const wstring& name ) :
	scbAbstractScheme ( name )
{
	memset ( &( this->m_TabloStatus ), 0, sizeof ( scbOutputStream ));
}

scbPultTablo::~scbPultTablo ()
{
	for ( auto& ptr : this->m_ActiveDevices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	for ( auto& ptr : this->m_PassiveDevices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	for ( auto& ptr : this->m_LampGroups )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}
}

void scbPultTablo::SetDeviceCount ( int pultWidth, int outputs, int activeDevs, int passiveDevs, int lampGroups )
{
	this->m_PultStatus.resize ( pultWidth, { 0, 0, 0, 0, 0, 0, 0, 0 } );

	for ( auto& ptr : this->m_Devices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	for ( auto& ptr : this->m_ActiveDevices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	for ( auto& ptr : this->m_PassiveDevices )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	for ( auto& ptr : this->m_LampGroups )
		if ( ptr != nullptr )
		{
			delete ptr;
			ptr = nullptr;
		}

	this->m_OutputOverBlocks.resize ( pultWidth );
	for ( auto& ptr : this->m_OutputOverBlocks )
		ptr.resize ( 0 );

	this->m_Devices.resize ( outputs, nullptr );
	this->m_ActiveDevices.resize ( activeDevs, nullptr );
	this->m_PassiveDevices.resize ( passiveDevs, nullptr );
	this->m_LampGroups.resize ( lampGroups );

	for ( auto& ptr : this->m_LampGroups )
		ptr = new scbPultTabloLampGroup ( this );

}

void scbPultTablo::SetOutput ( int index, const wstring& name, int block )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_Devices.size () ) ) ) return;
	if ( this->m_Devices [index] != nullptr ) return;
	if ( ( block < 0 ) || ( block > static_cast< int > ( this->m_PultStatus.size () ) ) ) return;

	this->m_Devices [index] = new scbSchemeOutput ( this, name, -1 );
	this->m_OutputOverBlocks [block].push_back ( index );
}

void scbPultTablo::SetBell ( int index, int continuously_bit, int impulse_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_PassiveDevices.size () ) ) ) return;
	if ( this->m_PassiveDevices [index] != nullptr ) return;

	this->m_PassiveDevices [index] = new scbPultTabloBell ( this, continuously_bit, impulse_bit );
}

void scbPultTablo::SetAmpermeter ( int index, int start_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_PassiveDevices.size () ) ) ) return;
	if ( this->m_PassiveDevices [index] != nullptr ) return;

	this->m_PassiveDevices [index] = new scbPultTabloAmpermeter ( this, start_bit );
}

void scbPultTablo::SetButtonKmd ( int index, scbPultTablo::Color color, int on_bit )
{
	if (( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size ()))) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloButtonKmd ( this, color, on_bit );
}

void scbPultTablo::SetButtonKmd ( int index, scbPultTablo::Color color, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () )) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloButtonKmd ( this, color, on_bit, off_bit );
}

void scbPultTablo::SetButtonKmdf ( int index, scbPultTablo::Color color, int on_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () )) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloButtonKmdf ( this, color, on_bit );
}

void scbPultTablo::SetButtonKmdf ( int index, scbPultTablo::Color color, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) )) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloButtonKmdf ( this, color, on_bit, off_bit );
}

void scbPultTablo::SetButtonSchm1m ( int index, scbPultTablo::Color color, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) )) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloButtonSchm1m ( this, color, on_bit, off_bit );
}

void scbPultTablo::SetCommutatorKmd ( int index, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) ) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloCommutatorKmd ( this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit );
}

void scbPultTablo::SetCommutatorKmdn ( int index, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) ) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloCommutatorKmd ( this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit, on_bit, off_bit );
}

void scbPultTablo::SetCommutatorKmt ( int index, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) ) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloCommutatorKmt ( this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit );
}

void scbPultTablo::SetCommutatorKmtn ( int index, scbPultTablo::Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit )
{
	if ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_ActiveDevices.size () ) ) ) return;
	if ( this->m_ActiveDevices [index] != nullptr ) return;

	this->m_ActiveDevices [index] = new scbPultTabloCommutatorKmt ( this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit, on_bit, off_bit );
}

void scbPultTablo::Init ()
{
	for ( auto& ptr : this->m_ActiveDevices )
		if ( ptr != nullptr ) 
			ptr->Init ();
}

void scbPultTablo::Recalculate ()
{
	// пустой метод
	this->MarkRecalculated ();
}

void scbPultTablo::SetStatusBit ( int bit )
{
	const int element = ( bit >> 5 ) & 7;
	const int block = ( bit >> 8 );
	const int bit_in_element = bit & 0x1F;
	if ( block >= static_cast<int> ( this->m_PultStatus.size () ) ) return;
	this->m_PultStatus [block].Mask [element] |= ( 1 << bit_in_element );

	for ( const auto& output_index : this->m_OutputOverBlocks [block] )
		this->m_Devices [output_index]->ChangeStatus ( this->m_PultStatus [block] );
}

void scbPultTablo::ResetStatusBit ( int bit )
{
	const int element = ( bit >> 5 ) & 7;
	const int block = ( bit >> 8 );
	const int bit_in_element = bit & 0x1F;
	if ( block >= static_cast<int> ( this->m_PultStatus.size () ) ) return;
	this->m_PultStatus [block].Mask [element] &= ~( 1 << bit_in_element );

	for ( const auto& output : this->m_OutputOverBlocks [block] )
		this->m_Devices [output]->ChangeStatus ( this->m_PultStatus [block] );
}

void scbPultTablo::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
{
	int i;
	if ( id == -1 )
	{
		for ( i = 0; i < 8; i++ )
			this->m_TabloStatus.Mask [i] = ( this->m_TabloStatus.Mask [i] & mask_off.Mask [i] ) | mask_on.Mask [i];
		for ( auto& ptr : this->m_PassiveDevices )
			ptr->ChangeStatus ( this->m_TabloStatus );
	}
	else
		this->m_LampGroups [id]->ChangeStatus ( mask_on );
}
