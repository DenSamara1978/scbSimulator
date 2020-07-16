#include "MotorDriveScheme.h"
#include "MotorDriveDevice.h"
#include "SchemeOutput.h"

using namespace scb;

MotorDriveScheme::MotorDriveScheme(const wstring& name) :
	AbstractScheme(name),
	status(0),
	controlStatus(0)
{
	this->driveDevice = new MotorDriveDevice(this);
}

MotorDriveScheme::~MotorDriveScheme()
{
	if (this->driveDevice != nullptr)
	{
		delete[] this->driveDevice;
		this->driveDevice = nullptr;
	}
}


void MotorDriveScheme::initialize()
{
	this->driveDevice->initialize();
}

void MotorDriveScheme::recalculate()
{
	// ������ �����
	this->markRecalculated();
}

void MotorDriveScheme::setStatusBit(int bit)
{
	OutputStream param;
	param.mask[0] = (this->status |= (1 << bit));
	for (const auto& output : this->devices)
		output->changeStatus(param);
}

void MotorDriveScheme::resetStatusBit(int bit)
{
	OutputStream param;
	param.mask[0] = (this->status &= ~(1 << bit));
	for (const auto& output : this->devices)
		output->changeStatus(param);
}

void MotorDriveScheme::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	/* �� ����������� ���� ������������� ������� �����

	�� ������� �� - ����������:
	0 - ������� ��������� ��� �������� ������ ������
	1 - ������� ��������� ��� �������� ������ �����
	2 - ������� �������

	� ������� �� - ��������
	0 - ����������������� 1-2 � ����������� ���������
	1 - ����������������� 1-2 � ������� ���������
	2 - ����������������� 3-4 � ����������� ���������
	3 - ����������������� 3-4 � ������� ���������
	4 - ����������� ������� ���
	5 - ����������� ���� �������
	6 - ���������� ���� �� ��������� ����������������� ������ 1
	7 - ���������� ���� �� ��������� ����������������� ������ 2
	8 - ���������� ���� �� ��������� ����������������� ������ 3
	9 - ���������� ���� �� ��������� ����������������� ������ 4
	10 - ������������� �����������
	*/


	// ������������ ������ ������� ������� ���������

	this->controlStatus = this->controlStatus & maskOff.mask[0] | maskOn.mask[0];
	OutputStream param = {this->controlStatus};
	this->driveDevice->changeStatus(param);
}
