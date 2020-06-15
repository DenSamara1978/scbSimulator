#include "scbRelay_DSSH13A.h"

scbRelay_DSSH13A::scbRelay_DSSH13A ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"ДСШ-13А";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::DSSH;
}

scbRelay_DSSH13A::~scbRelay_DSSH13A ()
{

}

int scbRelay_DSSH13A::FixDescription ()
{
	// Нет ошибок завершения описания
	return 0;
}
