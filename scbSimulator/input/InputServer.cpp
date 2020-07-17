#include "InputServer.h"
#include "..\application\Application.h"
#include "..\time\TimeServer.h"

using namespace input;

InputServer* InputServer::instance = nullptr;

InputServer::InputServer() :
	deltaTime(0.0f),
	forwardVelocity(0.0f),
	forwardMovement(0.0f),
	leftVelocity(0.0f),
	leftMovement(0.0f),
	horizontalAxisVelocity(0.0f),
	verticalAxisVelocity(0.0f),
	horizontalAxisMovement(0.0f),
	verticalAxisMovement(0.0f)
{
	this->timeStamp = time::TimeServer::getInstance()->getWorkingTime();
}

InputServer::~InputServer()
{
}

void InputServer::tick()
{
	auto newTimeStamp = time::TimeServer::getInstance()->getWorkingTime();
	this->deltaTime = (newTimeStamp - this->timeStamp) / 1000.0f;
	this->timeStamp = newTimeStamp;

	this->forwardMovement = 4.0f * this->deltaTime * this->forwardVelocity;
	this->leftMovement = 4.0f * this->deltaTime * this->leftVelocity;
	this->horizontalAxisMovement = 10.0f * XM_PI / 180.0f * this->deltaTime * this->horizontalAxisVelocity;
	this->verticalAxisMovement = 10.0f * XM_PI / 180.0f * this->deltaTime * this->verticalAxisVelocity;
}

void InputServer::putKeyDownEvent(unsigned int scanCode)
{
	auto application = application::Application::getInstance();
	switch (scanCode)
	{
		case 2: // ������� 1
			application->action1();
			break;
		case 3: // ������� 2
			application->action3();
			break;
		case 4: // ������� 3
			application->action8();
			break;
		case 5: // ������� 4
			application->action5();
			break;
		case 6: // ������� 5
			application->action7();
			break;

		case 0x11: // ������� W
			this->forwardVelocity = -1.0f;
			break;
		case 0x1F: // ������� S
			this->forwardVelocity = 1.0f;
			break;
		case 0x1E: // ������� A
			this->leftVelocity = -1.0f;
			break;
		case 0x20: // ������� D
			this->leftVelocity = 1.0f;
			break;
		case 0x48: // ������� Up
			this->horizontalAxisVelocity = 1.0f;
			break;
		case 0x50: // ������� Down
			this->horizontalAxisVelocity = -1.0f;
			break;
		case 0x4B: // ������� Left
			this->verticalAxisVelocity = 1.0f;
			break;
		case 0x4D: // ������� Right
			this->verticalAxisVelocity = -1.0f;
			break;

		case 0x3B: // ������� F1
			application->action9();
			break;
		case 0x3C: // ������� F2
			application->action10();
			break;
		case 0x3D: // ������� F3
			application->action11();
			break;
		case 0x3E: // ������� F4
			application->action12();
			break;
		case 0x3F: // ������� F5
			application->action13();
			break;
		case 0x40: // ������� F6
			application->action14();
			break;
	}
}

void InputServer::putKeyUpEvent(unsigned int scanCode)
{
	auto application = application::Application::getInstance();
	switch (scanCode)
	{
		case 2: // ������� 1
			application->action2();
			break;
		case 3: // ������� 2
			application->action4();
			break;
		case 5: // ������� 4
			application->action6();
			break;

		case 0x11: // ������� W
		case 0x1F: // ������� S
			this->forwardVelocity = 0.0f;
			break;
		case 0x1E: // ������� A
		case 0x20: // ������� D
			this->leftVelocity = 0.0f;
			break;
		case 0x48: // ������� Up
		case 0x50: // ������� Down
			this->horizontalAxisVelocity = 0.0f;
			break;
		case 0x4B: // ������� Left
		case 0x4D: // ������� Right
			this->verticalAxisVelocity = 0.0f;
			break;
	}
}
