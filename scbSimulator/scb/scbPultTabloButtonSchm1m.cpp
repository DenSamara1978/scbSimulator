#include "scbPultTabloButtonSchm1m.h"

scbPultTabloButtonSchm1m::scbPultTabloButtonSchm1m ( scbAbstractScheme* ownerScheme, scbPultTablo::Color color, int on_bit, int off_bit ) :
	scbPultTabloButtonKmd ( ownerScheme, color, on_bit, off_bit )
{
}

scbPultTabloButtonSchm1m::~scbPultTabloButtonSchm1m ()
{

}

void scbPultTabloButtonSchm1m::Press ()
{
	scbPultTabloButtonKmd::Press ();
}

void scbPultTabloButtonSchm1m::Release ()
{
	scbPultTabloButtonKmd::Release ();
}

void scbPultTabloButtonSchm1m::IdleTimer ( unsigned long long time )
{
	// TODO
}
