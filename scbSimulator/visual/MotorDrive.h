#pragma once

#include "VisualAbstract.h"

namespace scb
{
	class MotorDriveScheme;
	class MotorDriveDevice;
}

namespace visual
{

	class MotorDrive : public VisualAbstract
	{
	public:
		MotorDrive();
		virtual ~MotorDrive();

		bool assignScbMotorDrive(scb::MotorDriveScheme* motorDriveScheme);

		void setPosition(float x, float y, float z);
		void setDirection(float dirX, float dirY, float dirZ);

		virtual bool initializeGeometry() override;
		virtual void render() override;

		static bool initializeBuffers();

	private:
		static int autoSwitchVB;
		static int autoSwitchIB;
		static int autoSwitchVS;
		static int autoSwitchPS;

		static int gateVB;
		static int gateIB;
		static int gateVS;
		static int gatePS;

		static int baseVB;
		static int baseIB;
		static int baseVS;
		static int basePS;

		static int leftWedgeVB;
		static int leftWedgeIB;
		static int leftWedgeVS;
		static int leftWedgePS;

		static int rightWedgeVB;
		static int rightWedgeIB;
		static int rightWedgeVS;
		static int rightWedgePS;

		static int flapVB;
		static int flapIB;
		static int flapVS;
		static int flapPS;

		static int reductorVB;
		static int reductorIB;
		static int reductorVS;
		static int reductorPS;

		static int motorVB;
		static int motorIB;
		static int motorVS;
		static int motorPS;

		static int controlLineVB;
		static int controlLineIB;
		static int controlLineVS;
		static int controlLinePS;

		static int swivelCamVB;
		static int swivelCamIB;
		static int swivelCamVS;
		static int swivelCamPS;

		// координаты основания привода
		float x;
		float y;
		float z;

		// направление привода
		float dirX;
		float dirY;
		float dirZ;

		scb::MotorDriveDevice* motorDevice;
	};
}