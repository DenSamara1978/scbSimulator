#include "PultTabloLampGroup.h"

using namespace scb;

PultTabloLampGroup::PultTabloLampGroup(AbstractScheme* ownerScheme) :
	AbstractSchemeDevice(ownerScheme)
{
	memset(&(this->lampStatus), 0, sizeof(this->lampStatus));
}

PultTabloLampGroup::~PultTabloLampGroup()
{

}

void PultTabloLampGroup::initialize()
{
	// пустой вызов
}

void PultTabloLampGroup::changeStatus(const OutputStream& param)
{
	memcpy(&(this->lampStatus), &param, sizeof(param));
}

void PultTabloLampGroup::idleTimer(unsigned long long)
{
	// Пустой вызов
}