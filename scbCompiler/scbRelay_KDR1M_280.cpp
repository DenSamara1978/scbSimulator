#include "scbRelay_KDR1M_280.h"

scbRelay_KDR1M_280::scbRelay_KDR1M_280 ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"���1�-280";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::KDR;
}

scbRelay_KDR1M_280::~scbRelay_KDR1M_280 ()
{

}

int scbRelay_KDR1M_280::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}
