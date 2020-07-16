#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace graphics
{

	class Camera
	{
	public:
		Camera ();
		~Camera ();

		void setPosition (float x, float y, float z);
		void setLookPoint (float x, float y, float z);
		void setOrientation (float x, float y, float z);

		void turnLeft(float angle);
		void turnRight(float angle);
		void turnUp(float angle);
		void turnDown(float angle);
		void moveForward(float distance);
		void moveBackward(float distance);
		void moveLeft(float distance);
		void moveRight(float distance);

		XMMATRIX getViewMatrix () const;
		XMMATRIX getProjectionMatrix () const;

	private:
		void calculateViewMatrix ();

		XMVECTOR eye;
		XMVECTOR at;
		XMVECTOR up;
		XMMATRIX viewMatrix;
		XMMATRIX projectionMatrix;

	};

	inline XMMATRIX Camera::getViewMatrix () const
	{
		return this->viewMatrix;
	}

	inline XMMATRIX Camera::getProjectionMatrix () const
	{
		return this->projectionMatrix;
	}

	inline void Camera::calculateViewMatrix ()
	{
		this->viewMatrix = XMMatrixLookAtLH(this->eye, this->at, this->up);
	}
}