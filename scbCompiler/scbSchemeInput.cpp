#include "scbSchemeInput.h"

scbSchemeInput::scbSchemeInput ( const wstring& name ) :
	scbSchemeObject ( name )
{

}

scbSchemeInput::~scbSchemeInput ()
{

}

int scbSchemeInput::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}

const scbSchemeObject::ObjectType scbSchemeInput::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Input;
}
