#include "PultTabloBell.h"

using namespace scb;

PultTabloBell::PultTabloBell(AbstractScheme* ownerScheme, int continuouslyBit, int impulseBit) :
	status(0),
	AbstractSchemeDevice(ownerScheme)
{
	if ((continuouslyBit >= 0) && (continuouslyBit <= 255))
	{
		this->continuouslyElement = (continuouslyBit & 0xFE00) >> 5;
		this->continuouslyMask = 1 << (continuouslyBit & 0x1FF);
	}
	else
	{
		this->continuouslyElement = 0;
		this->continuouslyMask = 0;
	}

	if ((impulseBit >= 0) && (impulseBit <= 255))
	{
		this->impulseElement = (impulseBit & 0xFE00) >> 5;
		this->impulseMask = 1 << (impulseBit & 0x1FF);
	}
	else
	{
		this->impulseElement = 0;
		this->impulseMask = 0;
	}
}

PultTabloBell::~PultTabloBell()
{

}

void PultTabloBell::initialize()
{
	// пустой вызов
}

void PultTabloBell::idleTimer(unsigned long long time)
{
	// TODO
}

void PultTabloBell::changeStatus(const OutputStream& param)
{
	/*
	бит 0 - работа звонка
	бит 1 - звонковый импульс // TODO - обработать
	*/
	int newStatus = 0;

	if ((param.mask[this->impulseElement] & this->impulseMask) != 0)
		newStatus += 2;
	if ((param.mask[this->continuouslyElement] & this->continuouslyMask) != 0)
		newStatus += 1;

	if ((this->status == 0) && (newStatus != 0))
	{
		// TODO «апустить проигрывание циклического звука звонка
	}
	else if ((this->status != 0) && (newStatus == 0))
	{
		// TODO ќстановить проигрывание циклического звука звонка
	}
	this->status = newStatus;
}
