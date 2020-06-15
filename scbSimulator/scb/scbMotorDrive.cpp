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
	// ������ �����
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

	this->m_ControlStatus = this->m_ControlStatus & mask_off.Mask [0] | mask_on.Mask [0];
	scbOutputStream param = { this->m_ControlStatus };
	this->m_DriveDevice->ChangeStatus ( param );
}
