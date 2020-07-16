#include "PultTabloAbstractCommutator.h"

using namespace scb;

PultTabloAbstractCommutator::PultTabloAbstractCommutator(AbstractScheme* ownerScheme, Color color, int leftPosOnBit, int leftPosOffBit, int rightPosOnBit, int rightPosOffBit) :
	PultTabloActiveDevice(ownerScheme),
	pressable(false),
	pressOnContactBit(-1),
	pressOffContactBit(-1),
	switchLeftOnContactBit(leftPosOnBit),
	switchLeftOffContactBit(leftPosOffBit),
	switchRightOnContactBit(rightPosOnBit),
	switchRightOffContactBit(rightPosOffBit),
	pressStatus(0),
	pressContactStatus(0),
	switchStatus(0),
	switchContactStatus(0),
	pressPosition(0.0f),
	switchPosition(0.0f),
	color(color),
	timeStamp(0)
{

}

PultTabloAbstractCommutator::PultTabloAbstractCommutator(AbstractScheme* ownerScheme, Color color, int leftPosOnBit, int leftPosOffBit, int rightPosOnBit, int rightPosOffBit, int onBit, int offBit) :
	PultTabloActiveDevice(ownerScheme),
	pressable(true),
	pressOnContactBit(onBit),
	pressOffContactBit(offBit),
	switchLeftOnContactBit(leftPosOnBit),
	switchLeftOffContactBit(leftPosOffBit),
	switchRightOnContactBit(rightPosOnBit),
	switchRightOffContactBit(rightPosOffBit),
	pressStatus(0),
	pressContactStatus(0),
	switchStatus(0),
	switchContactStatus(0),
	pressPosition(0.0f),
	switchPosition(0.0f),
	color(color),
	timeStamp(0)
{

}

PultTabloAbstractCommutator::~PultTabloAbstractCommutator()
{

}

void PultTabloAbstractCommutator::press()
{
	if (!this->pressable) return;
	switch (this->pressStatus)
	{
		case 0:
			// инициировать нажатие
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->pressStatus = 1;
			this->addIdleTimer();
			break;
		case 3:
			// прекратить отпускание и с этого места начать нажатие
			this->pressStatus = 1;
			break;
	}
}

void PultTabloAbstractCommutator::release()
{
	if (!this->pressable) return;
	switch (this->pressStatus)
	{
		case 1:
			// прекратить нажатие и с этого места начать отпускание
			this->pressStatus = 3;
			break;
		case 2:
			// инициировать отпускание
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->pressStatus = 3;
			this->addIdleTimer();
			break;
	}
}
