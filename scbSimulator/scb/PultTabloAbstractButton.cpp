#include "PultTabloAbstractButton.h"
#include "AbstractScheme.h"

using namespace scb;

PultTabloAbstractButton::PultTabloAbstractButton(AbstractScheme* ownerScheme, Color color, int onBit) :
	position(0.0f),
	color(color),
	timeStamp(0),
	status(0),
	contactStatus(0),
	offContactBit(-1),
	onContactBit(onBit),
	PultTabloActiveDevice(ownerScheme)
{

}

PultTabloAbstractButton::PultTabloAbstractButton(AbstractScheme* ownerScheme, Color color, int onBit, int offBit) :
	position(0.0f),
	color(color),
	timeStamp(0),
	status(0),
	contactStatus(0),
	offContactBit(offBit),
	onContactBit(onBit),
	PultTabloActiveDevice(ownerScheme)
{

}

PultTabloAbstractButton::~PultTabloAbstractButton()
{

}
