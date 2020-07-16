#pragma once

#include <vector>
#include <DirectXMath.h>
#include "VisualAbstract.h"

using std::vector;
using namespace DirectX;

namespace scb
{
	class LightSignalScheme;
	class LightSignalLamp;
}

namespace visual
{
	class LightSignal : public VisualAbstract
	{
	public:
		LightSignal();
		virtual ~LightSignal();

		bool assignScbLightSignal(scb::LightSignalScheme* lightSignalScheme);

		void setPosition(float x, float y, float z);
		void setDirection(float dirX, float dirY, float dirZ);

		virtual bool initializeGeometry() override;
		virtual void render() override;

		static bool initializeBuffers();

	private:
		static int genVB;
		static int genVS;
		static int genPS;
		static int lensVB;
		static int lensVS;
		static int lensPS;
		static int mainIB;

		// координаты основания светофора
		float x;
		float y;
		float z;

		// направление светофора
		float dirX;
		float dirY;
		float dirZ;

		struct LampDescription
		{
			XMVECTOR color;
			scb::LightSignalLamp* lampLink;
			float x;
			float y;
			float z;
			float dirX;
			float dirY;
			float dirZ;
		};

		vector<LampDescription> lamps;
	};
}