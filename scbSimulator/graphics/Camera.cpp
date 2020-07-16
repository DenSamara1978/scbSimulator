#include "Camera.h"
#include "..\application\Application.h"

using namespace graphics;
using application::Application;

Camera::Camera()
{
	this->viewMatrix = XMMatrixIdentity();
	this->projectionMatrix = XMMatrixIdentity();
	this->eye = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	this->at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	this->up = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	auto width = Application::getInstance()->getMainWindowWidth();
	auto height = Application::getInstance()->getMainWindowHeight();
	this->projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT) height, 0.01f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::setPosition(float x, float y, float z)
{
	this->eye = XMVectorSet(x, y, z, 0.0f);
	this->calculateViewMatrix ();
}

void Camera::setLookPoint(float x, float y, float z)
{
	this->at = XMVectorSet(x, y, z, 0.0f);
	this->calculateViewMatrix ();
}

void Camera::setOrientation(float x, float y, float z)
{
	this->up = XMVectorSet(x, y, z, 0.0f);
	this->calculateViewMatrix ();
}

void Camera::turnLeft(float angle)
{
	auto rotationMatrix = XMMatrixRotationY(angle * XM_PI / 180.0f);
	this->viewMatrix *= rotationMatrix;
}

void Camera::turnRight(float angle)
{
	auto rotationMatrix = XMMatrixRotationY(-angle * XM_PI / 180.0f);
	this->viewMatrix *= rotationMatrix;
}

void Camera::turnUp(float angle)
{
	auto rotationMatrix = XMMatrixRotationX(angle * XM_PI / 180.0f);
	this->viewMatrix *= rotationMatrix;
}

void Camera::turnDown(float angle)
{
	auto rotationMatrix = XMMatrixRotationX(-angle * XM_PI / 180.0f);
	this->viewMatrix *= rotationMatrix;
}

void Camera::moveForward(float distance)
{
	auto translationMatrix = XMMatrixTranslation(0.0f, 0.0f, -distance);
	this->viewMatrix *= translationMatrix;
}

void Camera::moveBackward(float distance)
{
	auto translationMatrix = XMMatrixTranslation(0.0f, 0.0f, distance);
	this->viewMatrix *= translationMatrix;
}

void Camera::moveLeft(float distance)
{
	auto translationMatrix = XMMatrixTranslation(distance, 0.0f, 0.0f);
	this->viewMatrix *= translationMatrix;
}

void Camera::moveRight(float distance)
{
	auto translationMatrix = XMMatrixTranslation(-distance, 0.0f, 0.0f);
	this->viewMatrix *= translationMatrix;
}

