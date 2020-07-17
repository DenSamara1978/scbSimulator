#pragma once

#include "..\stdafx.h"

namespace input
{
	class InputServer
	{
	public:
		~InputServer();

		static InputServer* getInstance();

		void putKeyDownEvent(unsigned int scanCode);
		void putKeyUpEvent(unsigned int scanCode);

		float getForwardMovement() const;
		float getLeftMovement() const;
		float getHorizontalAxisMovement() const;
		float getVerticalAxisMovement() const;

		void tick();

	private:
		InputServer();

		static InputServer* instance;

		float forwardVelocity;
		float leftVelocity;
		float forwardMovement;
		float leftMovement;
		float horizontalAxisVelocity;
		float verticalAxisVelocity;
		float horizontalAxisMovement;
		float verticalAxisMovement;

		unsigned long long timeStamp;
		float deltaTime;
	};

	inline InputServer* InputServer::getInstance()
	{
		if (InputServer::instance == nullptr)
			InputServer::instance = new InputServer;
		return InputServer::instance;
	}

	inline float InputServer::getForwardMovement() const
	{
		return this->forwardMovement;
	}

	inline float InputServer::getLeftMovement() const
	{
		return this->leftMovement;
	}

	inline float InputServer::getHorizontalAxisMovement() const
	{
		return this->horizontalAxisMovement;
	}

	inline float InputServer::getVerticalAxisMovement() const
	{
		return this->verticalAxisMovement;
	}
}
