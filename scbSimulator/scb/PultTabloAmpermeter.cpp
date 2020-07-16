#include "PultTabloAmpermeter.h"

using namespace scb;

PultTabloAmpermeter::PultTabloAmpermeter(AbstractScheme* ownerScheme, int startBit) :
	AbstractSchemeDevice(ownerScheme)
{
	// TODO Принять номер стартового бита и сформировать рабочую маску
}

PultTabloAmpermeter::~PultTabloAmpermeter()
{

}

void PultTabloAmpermeter::initialize()
{
	// пустой вызов
}

void PultTabloAmpermeter::changeStatus(const OutputStream& param)
{
	// TODO
}

void PultTabloAmpermeter::idleTimer(unsigned long long time)
{
	// TODO
}
