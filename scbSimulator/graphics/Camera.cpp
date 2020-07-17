#include "Camera.h"
#include "..\application\Application.h"
#include "..\input\InputServer.h"

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

void Camera::moveByInput()
{
	auto inputServer = input::InputServer::getInstance();
	float pitch = inputServer->getHorizontalAxisMovement();
	float yaw = inputServer->getVerticalAxisMovement();
	auto matrixRotation = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
	this->viewMatrix *= matrixRotation;
	float left = inputServer->getLeftMovement();
	float forward = inputServer->getForwardMovement();
	auto matrixTranslation = XMMatrixTranslation(-left, 0.0, forward);
	this->viewMatrix *= matrixTranslation;
}
