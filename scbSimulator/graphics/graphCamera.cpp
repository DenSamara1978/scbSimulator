#include "graphCamera.h"
#include "..\genApplication.h"

graphCamera::graphCamera ()
{
	this->m_ViewMatrix = XMMatrixIdentity ();
	this->m_ProjectionMatrix = XMMatrixIdentity ();
	this->m_Eye = XMVectorSet ( 0.0f, -1.0f, 0.0f, 0.0f );
	this->m_At = XMVectorSet ( 0.0f, 0.0f, 0.0f, 0.0f );
	this->m_Up = XMVectorSet ( 0.0f, 0.0f, 1.0f, 0.0f );
	unsigned int width, height;
	RECT rc;
	GetClientRect ( genApplication::Instance ()->GetHWND (), &rc );
	width = rc.right - rc.left;           // получаем ширину
	height = rc.bottom - rc.top;   // и высоту окна
	this->m_ProjectionMatrix = XMMatrixPerspectiveFovLH ( XM_PIDIV4, width / ( FLOAT ) height, 0.01f, 100.0f );
}

graphCamera::~graphCamera ()
{
}

void graphCamera::SetPosition ( float x, float y, float z )
{
	this->m_Eye = XMVectorSet ( x, y, z, 0.0f );
	this->m_ViewMatrix = XMMatrixLookAtLH ( this->m_Eye, this->m_At, this->m_Up );
}

void graphCamera::SetLookPoint ( float x, float y, float z )
{
	this->m_At = XMVectorSet ( x, y, z, 0.0f );
	this->m_ViewMatrix = XMMatrixLookAtLH ( this->m_Eye, this->m_At, this->m_Up );
}

void graphCamera::SetOrientation ( float x, float y, float z )
{
	this->m_Up = XMVectorSet ( x, y, z, 0.0f );
	this->m_ViewMatrix = XMMatrixLookAtLH ( this->m_Eye, this->m_At, this->m_Up );
}
