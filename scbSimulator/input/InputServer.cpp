#include "InputServer.h"
#include "..\application\Application.h"
#include "..\time\TimeServer.h"

constexpr float pi = 3.14159265358979323846f;

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
	this->horizontalAxisMovement = 10.0f * pi / 180.0f * this->deltaTime * this->horizontalAxisVelocity;
	this->verticalAxisMovement = 10.0f * pi / 180.0f * this->deltaTime * this->verticalAxisVelocity;
}

void InputServer::putKeyDownEvent(unsigned int scanCode)
{
	auto application = application::Application::getInstance();
	switch (scanCode)
	{
		case 2: // клавиша 1
			application->action1();
			break;
		case 3: // клавиша 2
			application->action3();
			break;
		case 4: // клавиша 3
			application->action8();
			break;
		case 5: // клавиша 4
			application->action5();
			break;
		case 6: // клавиша 5
			application->action7();
			break;

		case 0x11: // клавиша W
			this->forwardVelocity = -1.0f;
			break;
		case 0x1F: // клавиша S
			this->forwardVelocity = 1.0f;
			break;
		case 0x1E: // клавиша A
			this->leftVelocity = -1.0f;
			break;
		case 0x20: // клавиша D
			this->leftVelocity = 1.0f;
			break;
		case 0x48: // клавиша Up
			this->horizontalAxisVelocity = 1.0f;
			break;
		case 0x50: // клавиша Down
			this->horizontalAxisVelocity = -1.0f;
			break;
		case 0x4B: // клавиша Left
			this->verticalAxisVelocity = 1.0f;
			break;
		case 0x4D: // клавиша Right
			this->verticalAxisVelocity = -1.0f;
			break;

		case 0x3B: // клавиша F1
			application->action9();
			break;
		case 0x3C: // клавиша F2
			application->action10();
			break;
		case 0x3D: // клавиша F3
			application->action11();
			break;
		case 0x3E: // клавиша F4
			application->action12();
			break;
		case 0x3F: // клавиша F5
			application->action13();
			break;
		case 0x40: // клавиша F6
			application->action14();
			break;
		case 0x41: // клавиша F7
			application->getStatistic();
			break;
	}
}

void InputServer::putKeyUpEvent(unsigned int scanCode)
{
	auto application = application::Application::getInstance();
	switch (scanCode)
	{
		case 2: // клавиша 1
			application->action2();
			break;
		case 3: // клавиша 2
			application->action4();
			break;
		case 5: // клавиша 4
			application->action6();
			break;

		case 0x11: // клавиша W
		case 0x1F: // клавиша S
			this->forwardVelocity = 0.0f;
			break;
		case 0x1E: // клавиша A
		case 0x20: // клавиша D
			this->leftVelocity = 0.0f;
			break;
		case 0x48: // клавиша Up
		case 0x50: // клавиша Down
			this->horizontalAxisVelocity = 0.0f;
			break;
		case 0x4B: // клавиша Left
		case 0x4D: // клавиша Right
			this->verticalAxisVelocity = 0.0f;
			break;
	}
}
