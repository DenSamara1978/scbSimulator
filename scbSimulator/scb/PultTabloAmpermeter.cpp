#include "PultTabloAmpermeter.h"

using namespace scb;

PultTabloAmpermeter::PultTabloAmpermeter(AbstractScheme* ownerScheme, int startBit) :
	AbstractSchemeDevice(ownerScheme)
{
	// TODO ������� ����� ���������� ���� � ������������ ������� �����
}

PultTabloAmpermeter::~PultTabloAmpermeter()
{

}

void PultTabloAmpermeter::initialize()
{
	// ������ �����
}

void PultTabloAmpermeter::changeStatus(const OutputStream& param)
{
	// TODO
}

void PultTabloAmpermeter::idleTimer(unsigned long long time)
{
	// TODO
}
