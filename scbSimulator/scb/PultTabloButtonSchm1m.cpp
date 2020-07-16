#include "PultTabloButtonSchm1m.h"

using namespace scb;

PultTabloButtonSchm1m::PultTabloButtonSchm1m(AbstractScheme* ownerScheme, Color color, int onBit, int offBit) :
	PultTabloButtonKmd(ownerScheme, color, onBit, offBit )
{
}

PultTabloButtonSchm1m::~PultTabloButtonSchm1m()
{

}

void PultTabloButtonSchm1m::press()
{
	PultTabloButtonKmd::press();
}

void PultTabloButtonSchm1m::release()
{
	PultTabloButtonKmd::release();
}

void PultTabloButtonSchm1m::idleTimer(unsigned long long time)
{
	// TODO
}
