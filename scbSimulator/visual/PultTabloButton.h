#pragma once

#include "VisualAbstract.h"

namespace scb
{
	class PultTabloAbstractButton;
	class PultTabloScheme;
}

namespace visual
{

	class PultTabloButton : public VisualAbstract
	{
	public:
		PultTabloButton();
		virtual ~PultTabloButton();

		bool assignButton(scb::PultTabloScheme* pultTablo, int device);

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

		// координаты основания кнопки
		float x;
		float y;
		float z;

		// направление головки кнопки
		float dirX;
		float dirY;
		float dirZ;

		XMVECTOR diffuseColor;
		XMVECTOR specularColor;

		scb::PultTabloAbstractButton* buttonLink;
	};
}