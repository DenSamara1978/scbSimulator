#include "scbRelay_KDR1_200.h"

scbRelay_KDR1_200::scbRelay_KDR1_200 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"���1-200";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::KDR;
}

scbRelay_KDR1_200::~scbRelay_KDR1_200 ()
{

}

int scbRelay_KDR1_200::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}
