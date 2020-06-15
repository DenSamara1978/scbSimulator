#include "scbSchemeBlock.h"
#include "scbDescription.h"

scbSchemeBlock::scbSchemeBlock (const wstring& name) :
	scbSchemeObject (name)
{

}

scbSchemeBlock::~scbSchemeBlock ()
{

}

int scbSchemeBlock::SetPlacement (int id, scbDescription::PlacementType pl_type )
{
	this->m_Placement = id;
	return ( scbDescription::CheckCaseInPlacement ( this->m_Case, pl_type ) ) ? 0 : -1;
}

int scbSchemeBlock::SetLocation ( const wstring& location )
{
	// Проверка возможности установки этого типа блока в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->m_Location = location;
	return 0;
}

int scbSchemeBlock::SetTypeName (const wstring& name)
{
	auto [_case, id] = scbDescription::GetBlockInfo ( name );
	this->m_TypeId = id;
	this->m_Case = _case;
	if ( id != -1 )
		return 0;
	else
		return -1;
}
/*
const wstring scbSchemeBlock::GetTypeName () const
{
	return this->m_TypeName;
}*/

int scbSchemeBlock::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}

bool scbSchemeBlock::CheckLocation ( int block, int placement, const wstring& location ) const
{
	return (( placement == this->m_Placement ) and !location.empty () and ( location == this->m_Location ));
}

const scbSchemeObject::ObjectType scbSchemeBlock::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Block;
}
