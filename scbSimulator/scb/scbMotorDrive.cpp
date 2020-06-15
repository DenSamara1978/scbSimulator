#include "scbMotorDrive.h"
#include "scbMotorDriveDevice.h"
#include "scbSchemeOutput.h"

scbMotorDrive::scbMotorDrive ( const wstring& name ) :
	scbAbstractScheme ( name ),
	m_Status ( 0 ),
	m_ControlStatus ( 0 )
{
	this->m_DriveDevice = new scbMotorDriveDevice ( this );
}

scbMotorDrive::~scbMotorDrive ()
{
	if ( this->m_DriveDevice != nullptr )
	{
		delete [] this->m_DriveDevice;
		this->m_DriveDevice = nullptr;
	}
}


void scbMotorDrive::Init ()
{
	this->m_DriveDevice->Init ();
}

void scbMotorDrive::Recalculate ()
{
	// пустой вызов
	this->MarkRecalculated ();
}

void scbMotorDrive::SetStatusBit ( int bit )
{
	scbOutputStream param;
	param.Mask [0] = ( this->m_Status |= ( 1 << bit ) );
	for ( const auto& output : this->m_Devices )
		output->ChangeStatus ( param );
}

void scbMotorDrive::ResetStatusBit ( int bit )
{
	scbOutputStream param;
	param.Mask [0] = ( this->m_Status &= ~( 1 << bit ) );
	for ( const auto& output : this->m_Devices )
		output->ChangeStatus ( param );
}

void scbMotorDrive::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
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

	this->m_ControlStatus = this->m_ControlStatus & mask_off.Mask [0] | mask_on.Mask [0];
	scbOutputStream param = { this->m_ControlStatus };
	this->m_DriveDevice->ChangeStatus ( param );
}
