#include "scbRelay_DSSH13A.h"

scbRelay_DSSH13A::scbRelay_DSSH13A ( const wstring& name ) :
	scbSchemeRelay ( name )
{
	this->m_TypeName = L"���-13�";
	this->m_IsPlugable = false;
	this->m_Case = scbDescription::DeviceCase::DSSH;
}

scbRelay_DSSH13A::~scbRelay_DSSH13A ()
{

}

int scbRelay_DSSH13A::FixDescription ()
{
	// ��� ������ ���������� ��������
	return 0;
}
