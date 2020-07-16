#include "NeutralRelay.h"
#include "AbstractScheme.h"

using namespace scb;

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit) :
	offContactBit(0),
	onContactBit(onBit),
	offBridgeContactBit(0),
	onBridgeContactBit(0),
	hasOffContact(false),
	hasBridgeContact(false),
	Relay(ownerScheme)
{
}

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit) :
	offContactBit(offBit),
	onContactBit(onBit),
	offBridgeContactBit(0),
	onBridgeContactBit(0),
	hasOffContact(true),
	hasBridgeContact(false),
	Relay(ownerScheme)
{
}

NeutralRelay::NeutralRelay(AbstractScheme* ownerScheme, int onBit, int offBit, int onBridgeBit, int offBridgeBit) :
	offContactBit(offBit),
	onContactBit(onBit),
	offBridgeContactBit(offBridgeBit),
	onBridgeContactBit(onBridgeBit),
	hasOffContact(true),
	hasBridgeContact(true),
	Relay(ownerScheme)
{
}

NeutralRelay::~NeutralRelay()
{
}

void NeutralRelay::initialize()
{
	if (this->hasOffContact)
		this->ownerScheme->setStatusBit(this->offContactBit);
	if (this->hasBridgeContact)
		this->ownerScheme->setStatusBit(this->offBridgeContactBit);
}

void NeutralRelay::setMode(unsigned long mode)
{
	if (this->targetMode == mode)
	{
		// ������� ����� ������������� ������������, ������ �� ������
		return;
	}
	unsigned long long newDelay, time;
	time = this->getWorkingTime();

	int starting = -1;
	int shifting = -1;
	int dir = 0;

	for (const auto& sample : this->timeSamples)
	{
		if ((sample.modeFrom == this->currentMode) && (sample.modeTo == mode))
		{
			starting = sample.starting;
			shifting = sample.shifting;
			dir = 1;
			break;
		}
	}
	if (dir == 0)
	{
		for (const auto& sample : this->timeSamples)
		{
			if ((sample.modeFrom == this->targetMode) && (sample.modeTo == mode))
			{
				starting = sample.starting;
				shifting = sample.shifting;
				dir = -1;
				break;
			}
		}
	}
	if (starting == -1)
	{
		// ��������� ����� ������ �� ������� ��������� ����
		this->currentMode = mode;
		return;
	}

	// dir == 1 ���� �������� ���������� ��� ��� ������������ � ��� �� �����������
	// dir == -1 ���� �������� ������ �����������

	float differenceTime = static_cast<float> (time - this->timeStamp);
	float interval;

	switch (this->status)
	{
		case 0:
			// ������ ������� �������� �� ������
			this->timeStamp = time;
			this->status = 1;
			this->addTimeToWork(starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 1:
			if (dir == 1)
			{
				// ���������� ��������� �� ������ �� ������� �������
				newDelay = static_cast<unsigned long long> (starting * (1.0f - differenceTime / this->starting));
				this->timeStamp = time - starting + newDelay;
				this->changeTimeToWork(newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// ��������� � ��������� ��� ����
				this->timeStamp = 0;
				this->status = 0;
				this->deleteTimeToWork();
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 2:
			interval = shifting * differenceTime / this->shifting;
			newDelay = static_cast<unsigned long long> ((dir == 1) ? shifting - interval : interval);
			if (dir != 1)
				this->status = 5;
			this->timeStamp = time - shifting + newDelay;
			this->changeTimeToWork(newDelay);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 3:
			// ������ ������� �������� �� ����������
			this->timeStamp = time;
			this->status = 4;
			this->addTimeToWork(starting, 0);
			this->starting = starting;
			this->shifting = shifting;
			break;
		case 4:
			if (dir == 1)
			{
				// ���������� ��������� �� ��������� �� ������� �������
				newDelay = static_cast<unsigned long long> (starting * (1.0f - differenceTime / this->starting));
				this->timeStamp = time - starting + newDelay;
				this->changeTimeToWork(newDelay);
				this->starting = starting;
				this->shifting = shifting;
			}
			else
			{
				// ��������� � ��������� ��� �����
				this->timeStamp = 0;
				this->status = 3;
				this->deleteTimeToWork();
				this->starting = 0;
				this->shifting = 0;
			}
			break;
		case 5:
			interval = shifting * differenceTime / this->shifting;
			newDelay = static_cast<unsigned long long> ((dir == 1) ? shifting - interval : interval);
			if (dir != 1)
				this->status = 2;
			this->timeStamp = time - shifting + newDelay;
			this->changeTimeToWork(newDelay);
			this->starting = starting;
			this->shifting = shifting;
			break;
	}
	this->targetMode = mode;
}

void NeutralRelay::timeToWork(int signal, unsigned long long time)
{
	switch (this->status)
	{
		case 1:
			if (this->hasOffContact && (this->offContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->offContactBit);
			if (this->hasBridgeContact && (this->onBridgeContactBit >= 0))
				this->ownerScheme->setStatusBit(this->onBridgeContactBit);
			this->timeStamp = time;
			this->status = 2;
			this->addTimeToWork(this->shifting, 0);
			break;
		case 2:
			if (this->onContactBit >= 0)
				this->ownerScheme->setStatusBit(this->onContactBit);
			if (this->hasBridgeContact && (this->offBridgeContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->offBridgeContactBit);
			this->timeStamp = 0;
			this->status = 3;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
		case 4:
			if (this->onContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->onContactBit);
			if (this->hasBridgeContact && (this->offBridgeContactBit >= 0))
				this->ownerScheme->setStatusBit(this->offBridgeContactBit);
			this->timeStamp = time;
			this->status = 5;
			this->addTimeToWork(this->shifting, 0);
			break;
		case 5:
			if (this->hasOffContact && (this->offContactBit >= 0))
				this->ownerScheme->setStatusBit(this->offContactBit);
			if (this->hasBridgeContact && (this->onBridgeContactBit >= 0))
				this->ownerScheme->resetStatusBit(this->onBridgeContactBit);
			this->timeStamp = 0;
			this->status = 0;
			this->currentMode = this->targetMode;
			this->starting = 0;
			this->shifting = 0;
			break;
	}
}
