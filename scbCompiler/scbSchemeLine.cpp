#include "scbSchemeLine.h"

scbSchemeLine::scbSchemeLine ( const wstring& name ) :
	scbSchemeObject ( name )
{

}

scbSchemeLine::~scbSchemeLine ()
{

}

int scbSchemeLine::SetDescriptor ( const scbComplexName& descriptor )
{
    this->m_Object = descriptor;
    return 0;
}

int scbSchemeLine::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}

const scbSchemeObject::ObjectType scbSchemeLine::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Line;
}
