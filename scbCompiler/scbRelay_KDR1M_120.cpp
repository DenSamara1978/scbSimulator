#include "scbRelay_KDR1M_120.h"

scbRelay_KDR1M_120::scbRelay_KDR1M_120 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"���1�-120";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::KDR;
}

scbRelay_KDR1M_120::~scbRelay_KDR1M_120 ()
{

}

int scbRelay_KDR1M_120::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}
