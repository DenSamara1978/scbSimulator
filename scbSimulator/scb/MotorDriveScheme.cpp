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
	// пустой вызов
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
	/* По устройствам есть фиксированные битовые карты

	Со стороны ЭЦ - управление:
	0 - питание двигателя дял движения шибера вправо
	1 - питание двигателя дял движения шибера влево
	2 - обогрев привода

	В сторону ЭЦ - контроль
	0 - автопереключатель 1-2 в контрольном положении
	1 - автопереключатель 1-2 в рабочем положении
	2 - автопереключатель 3-4 в контрольном положении
	3 - автопереключатель 3-4 в рабочем положении
	4 - потребление рабочий ток
	5 - потребление тока фрикции
	6 - отсутствие инея на контактах автопереключателя группы 1
	7 - отсутствие инея на контактах автопереключателя группы 2
	8 - отсутствие инея на контактах автопереключателя группы 3
	9 - отсутствие инея на контактах автопереключателя группы 4
	10 - блокировочный выключатель
	*/


	// Используется только нулевой элемент состояния

	this->controlStatus = this->controlStatus & maskOff.mask[0] | maskOn.mask[0];
	OutputStream param = {this->controlStatus};
	this->driveDevice->changeStatus(param);
}
