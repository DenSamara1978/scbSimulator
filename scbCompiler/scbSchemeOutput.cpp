#include "scbSchemeOutput.h"

scbSchemeOutput::scbSchemeOutput ( const wstring& name, Type type ) :
	scbSchemeObject ( name ),
    m_Type ( type )
{
}

scbSchemeOutput::~scbSchemeOutput ()
{
}

int scbSchemeOutput::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}

const scbSchemeObject::ObjectType scbSchemeOutput::GetObjectType () const
{
	return scbSchemeObject::ObjectType::Output;
}
