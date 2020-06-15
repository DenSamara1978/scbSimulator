#include "scbRelay_NMSHM1_11.h"

scbRelay_NMSHM1_11::scbRelay_NMSHM1_11 ( const wstring& name, bool plugable ) :
	scbSchemeRelay ( name )
{
	if ( this->m_IsPlugable = plugable )
	{
		this->m_TypeName = L"����1-11";
		this->m_Case = scbDescription::DeviceCase::NMSH;
	}
	else
	{
		this->m_TypeName = L"���1-11";
		this->m_Case = scbDescription::DeviceCase::NM;
	}
}

scbRelay_NMSHM1_11::~scbRelay_NMSHM1_11 ()
{

}

int scbRelay_NMSHM1_11::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}
