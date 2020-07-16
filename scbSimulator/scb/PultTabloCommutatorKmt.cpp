#include "PultTabloCommutatorKmt.h"
#include "AbstractScheme.h"

using namespace scb;

PultTabloCommutatorKmt::PultTabloCommutatorKmt(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit) :
	PultTabloAbstractCommutator(ownerScheme, color, leftPositionOnBit, leftPositionOffBit, rightPositionOnBit, rightPositionOffBit)
{

}

PultTabloCommutatorKmt::PultTabloCommutatorKmt(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit) :
	PultTabloAbstractCommutator(ownerScheme, color, leftPositionOnBit, leftPositionOffBit, rightPositionOnBit, rightPositionOffBit, onBit, offBit)
{

}

PultTabloCommutatorKmt::~PultTabloCommutatorKmt()
{

}

void PultTabloCommutatorKmt::initialize()
{
	if (this->switchRightOffContactBit >= 0)
		this->ownerScheme->setStatusBit(this->switchRightOffContactBit);
	if (this->switchLeftOffContactBit >= 0)
		this->ownerScheme->setStatusBit(this->switchLeftOffContactBit);
	if (this->pressOffContactBit >= 0)
		this->ownerScheme->setStatusBit(this->pressOffContactBit);
}

void PultTabloCommutatorKmt::turnCw()
{
	switch (this->switchStatus)
	{
		case 0:
			// ������ ������� ������� �� ������
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->switchStatus = 4;
			this->addIdleTimer();
			break;
		case 1:
			// ���������� ������� ������ � ������ � ����� ����� ������� �������
			this->switchStatus = 3;
			break;
		case 2:
			// ������ ������� ������� �� ������
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->switchStatus = 3;
			this->addIdleTimer();
			break;
		case 6:
			// ���������� ������� ������ � ������ � ����� ����� ������� �������
			this->switchStatus = 4;
			break;
	}
}

void PultTabloCommutatorKmt::turnCcw()
{
	switch (this->switchStatus)
	{
		case 0:
			// ������ ������� ������ �� ������
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->switchStatus = 1;
			this->addIdleTimer();
			break;
		case 3:
			// ���������� ������� ������� � ������ � ����� ����� ������� ������
			this->switchStatus = 1;
			break;
		case 4:
			// ���������� ������� ������� � ������ � ����� ����� ������� ������
			this->switchStatus = 6;
			break;
		case 5:
			// ������ ������� ������ �� �������
			if (this->timeStamp == 0)
				this->timeStamp = this->getWorkingTime();
			this->switchStatus = 6;
			this->addIdleTimer();
			break;
	}
}

void PultTabloCommutatorKmt::idleTimer(unsigned long long time)
{
	int markToDelete = 0xFF;
	float delta = static_cast <float> (time - this->timeStamp);

	// ������� ��������� ����� �������
	if (this->pressStatus == 1)
	{
		this->pressPosition += delta / this->pressTime;
		if ((this->pressContactStatus == 0) && (this->pressPosition > this->pressOffBorder))
		{
			if (this->pressOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->pressOffContactBit);
			this->pressContactStatus = 1;
		}
		if ((this->pressContactStatus == 1) && (this->pressPosition > this->pressOnBorder))
		{
			if (this->pressOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->pressOnContactBit);
			this->pressContactStatus = 2;
		}
		if (this->pressPosition >= 1.0f)
		{
			this->pressPosition = 1.0f;
			this->pressStatus = 2;
		}
		else
			markToDelete &= 0xFE;
	}
	else if (this->pressStatus == 3)
	{
		this->pressPosition -= delta / this->pressTime;
		if ((this->pressContactStatus == 2) && (this->pressPosition < this->pressOnBorder))
		{
			if (this->pressOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->pressOnContactBit);
			this->pressContactStatus = 1;
		}
		if ((this->pressContactStatus == 1) && (this->pressPosition < this->pressOffBorder))
		{
			if (this->pressOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->pressOffContactBit);
			this->pressContactStatus = 0;
		}
		if (this->pressPosition <= 0.0f)
		{
			this->pressPosition = 0.0f;
			this->pressStatus = 0;
		}
		else
			markToDelete &= 0xFE;
	}

	// ����� ��������� ����� ��������
	if (this->switchStatus == 3)
	{
		this->switchPosition += delta / this->switchTime;
		if ((this->switchContactStatus == 2) && (this->switchPosition > -this->switchOnBorder))
		{
			if (this->switchLeftOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchLeftOnContactBit);
			this->switchContactStatus = 1;
		}
		if ((this->switchContactStatus == 1) && (this->switchPosition > -this->switchOffBorder))
		{
			if (this->switchLeftOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchLeftOffContactBit);
			this->switchContactStatus = 0;
		}
		if (this->switchPosition >= 0.0f)
		{
			this->switchPosition = 0.0f;
			this->switchStatus = 0;
		}
		else
			markToDelete &= 0xFD;
	}
	else if (this->switchStatus == 4)
	{
		this->switchPosition += delta / this->switchTime;
		if ((this->switchContactStatus == 0) && (this->switchPosition > this->switchOffBorder))
		{
			if (this->switchRightOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchRightOffContactBit);
			this->switchContactStatus = 3;
		}
		if ((this->switchContactStatus == 3) && (this->switchPosition > this->switchOnBorder))
		{
			if (this->switchRightOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchRightOnContactBit);
			this->switchContactStatus = 4;
		}
		if (this->switchPosition >= 1.0f)
		{
			this->switchPosition = 1.0f;
			this->switchStatus = 5;
		}
		else
			markToDelete &= 0xFD;
	}
	else if (this->switchStatus == 6)
	{
		this->switchPosition -= delta / this->switchTime;
		if ((this->switchContactStatus == 4) && (this->switchPosition < this->switchOnBorder))
		{
			if (this->switchRightOnContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchRightOnContactBit);
			this->switchContactStatus = 3;
		}
		if ((this->switchContactStatus == 3) && (this->switchPosition < this->switchOffBorder))
		{
			if (this->switchRightOffContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchRightOffContactBit);
			this->switchContactStatus = 0;
		}
		if (this->switchPosition <= 0.0f)
		{
			this->switchPosition = 0.0f;
			this->switchStatus = 0;
		}
		else
			markToDelete &= 0xFD;
	}
	else if (this->switchStatus == 1)
	{
		this->switchPosition -= delta / this->switchTime;
		if ((this->switchContactStatus == 0) && (this->switchPosition < -this->switchOffBorder))
		{
			if (this->switchLeftOffContactBit >= 0)
				this->ownerScheme->resetStatusBit(this->switchLeftOffContactBit);
			this->switchContactStatus = 1;
		}
		if ((this->switchContactStatus == 1) && (this->switchPosition < -this->switchOnBorder))
		{
			if (this->switchLeftOnContactBit >= 0)
				this->ownerScheme->setStatusBit(this->switchLeftOnContactBit);
			this->switchContactStatus = 2;
		}
		if (this->switchPosition <= -1.0f)
		{
			this->switchPosition = -1.0f;
			this->switchStatus = 2;
		}
		else
			markToDelete &= 0xFD;
	}

	// ������� ���� �� ������ ��������� ��������
	if (markToDelete == 0xFF)
	{
		this->deleteIdleTimer();
		this->timeStamp = 0;
	}
	else
		this->timeStamp = time;
}
