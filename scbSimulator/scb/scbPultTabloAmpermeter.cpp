#include "scbPultTabloAmpermeter.h"

scbPultTabloAmpermeter::scbPultTabloAmpermeter ( scbAbstractScheme* ownerScheme, int start_bit ) :
	scbAbstractSchemeDevice ( ownerScheme )
{
	// TODO ������� ����� ���������� ���� � ������������ ������� �����
}

scbPultTabloAmpermeter::~scbPultTabloAmpermeter ()
{

}

void scbPultTabloAmpermeter::Init ()
{
	// ������ �����
}

void scbPultTabloAmpermeter::ChangeStatus ( const scbOutputStream& param )
{
	// TODO
}

void scbPultTabloAmpermeter::IdleTimer ( unsigned long long time )
{
	// TODO
}
