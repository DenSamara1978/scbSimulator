#pragma once

#include "VisualAbstract.h"

namespace scb
{
	class PultTabloAbstractCommutator;
	class PultTabloScheme;
}

namespace visual
{

	class PultTabloCommutator : public VisualAbstract
	{
	public:
		PultTabloCommutator();
		virtual ~PultTabloCommutator();

		bool assignCommutator(scb::PultTabloScheme* pultTablo, int device);

		void setPosition(float x, float y, float z);
		void setDirection(float dirX, float dirY, float dirZ);

		virtual bool initializeGeometry() override;
		virtual void render() override;

		static bool initializeBuffers();

	private:
		static int mainVB;
		static int plateVB;
		static int mainVS;
		static int mainPS;
		static int mainIB;
		static int plateIB;

		// координаты основания коммутатора
		float x;
		float y;
		float z;

		// направление головки коммутатора
		float dirX;
		float dirY;
		float dirZ;

		XMVECTOR diffuseColor;
		XMVECTOR specularColor;

		scb::PultTabloAbstractCommutator* commutatorLink;
	};
}