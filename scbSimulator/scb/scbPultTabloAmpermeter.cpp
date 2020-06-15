#include "scbPultTabloAmpermeter.h"

scbPultTabloAmpermeter::scbPultTabloAmpermeter ( scbAbstractScheme* ownerScheme, int start_bit ) :
	scbAbstractSchemeDevice ( ownerScheme )
{
	// TODO Принять номер стартового бита и сформировать рабочую маску
}

scbPultTabloAmpermeter::~scbPultTabloAmpermeter ()
{

}

void scbPultTabloAmpermeter::Init ()
{
	// пустой вызов
}

void scbPultTabloAmpermeter::ChangeStatus ( const scbOutputStream& param )
{
	// TODO
}

void scbPultTabloAmpermeter::IdleTimer ( unsigned long long time )
{
	// TODO
}
