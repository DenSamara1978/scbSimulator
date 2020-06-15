#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class graphCamera
{
	XMVECTOR m_Eye;
	XMVECTOR m_At;
	XMVECTOR m_Up;
	XMMATRIX m_ViewMatrix;
	XMMATRIX m_ProjectionMatrix;

public:
	graphCamera ();
	~graphCamera ();

	void SetPosition ( float x, float y, float z );
	void SetLookPoint ( float x, float y, float z );
	void SetOrientation ( float x, float y, float z );

	XMMATRIX GetViewMatrix () const;
	XMMATRIX GetProjectionMatrix () const;
};

inline XMMATRIX graphCamera::GetViewMatrix () const
{
	return this->m_ViewMatrix;
}

inline XMMATRIX graphCamera::GetProjectionMatrix () const
{
	return this->m_ProjectionMatrix;
}
