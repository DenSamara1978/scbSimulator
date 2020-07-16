#pragma once

#include <vector>
#include "VisualAbstract.h"
#include "..\scb\PultTabloScheme.h"

using namespace DirectX;
using std::vector;

namespace visual
{
	class PultTablo : public VisualAbstract
	{
	public:
		PultTablo();
		virtual ~PultTablo();

		bool assignPultTablo(scb::PultTabloScheme* pultTabloScheme);
		void addCellLamp(int group, int bit, float x, float y, int angle, Color color);
		void addRoundLamp(int group, int bit, float x, float y, Color color);

		void setPosition(float x, float y, float z);
		void setDirection(float dirX, float dirY, float dirZ);

		virtual bool initializeGeometry() override;
		virtual void render() override;

		static bool initializeBuffers();

	private:
		// Пока - простенькое табло без кнопок и активных элементов, только светодиоды
		static int ledCellVB;
		static int ledCellIB;
		static int ledRoundVB;
		static int ledRoundIB;
		static int ledVS;
		static int ledPS;

		static int plateVB;
		static int plateIB;
		static int plateVS;
		static int platePS;

		// координаты центра табло
		float x;
		float y;
		float z;

		// ориентация табло "на оператора"
		float dirX;
		float dirY;
		float dirZ;

		struct LampInfo
		{
			int group;
			int bit;
			int type; // 0 - прямоугольная, 1 - круглая
			float x; // координата по оси X ( ноль слева ) 
			float y; // координата по оси Y ( ноль снизу )
			float angle; // ориентация ( 0 - направо и далее против часовой )
			XMVECTOR color; // Цвет
		};

		scb::PultTabloScheme* pultTabloScheme;
		vector<LampInfo> lamps;
	};
}