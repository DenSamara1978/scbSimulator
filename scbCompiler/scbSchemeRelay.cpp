#include "scbSchemeRelay.h"

scbSchemeRelay::scbSchemeRelay ( const wstring& name ) :
	scbSchemeObject ( name )
{

}

scbSchemeRelay::~scbSchemeRelay ()
{

}

int scbSchemeRelay::SetBlock ( int id )
{
	this->m_Block = id;
	return 0;
}

int scbSchemeRelay::SetLocation ( const wstring& name )
{
	// Проверка возможности установки этого типа реле в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->m_Location = name;
	return 0;
}

int scbSchemeRelay::SetPlacement ( int id, scbDescription::PlacementType pl_type )
{
	this->m_Placement = id;
	return ( scbDescription::CheckCaseInPlacement ( this->m_Case, pl_type ) ) ? 0 : -1;
}

const scbSchemeObject::ObjectType scbSchemeRelay::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Relay;
}

const wstring scbSchemeRelay::GetTypeName () const
{
	return this->m_TypeName;
}

bool scbSchemeRelay::CheckLocation ( int block, int placement, const wstring& location ) const
{
	if ( location.empty () or ( this->m_Location != location ))
		return false;
	else
		return ( ( ( block == -1 ) and ( placement == this->m_Placement ) ) or
				( ( placement == -1 ) and ( block == this->m_Block ) ));
}
