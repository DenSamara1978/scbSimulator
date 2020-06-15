#pragma once

#include <vector>
#include "visualAbstract.h"
#include "..\scb\scbPultTablo.h"

using namespace DirectX;
using std::vector;

class visualPultTablo : public visualAbstract
{
	// Пока - простенькое табло без кнопок и активных элементов, только светодиоды
	static int m_LedCellVB;
	static int m_LedCellIB;
	static int m_LedRoundVB;
	static int m_LedRoundIB;
	static int m_LedVS;
	static int m_LedPS;

	static int m_PlateVB;
	static int m_PlateIB;
	static int m_PlateVS;
	static int m_PlatePS;

	// координаты центра табло
	float m_X;
	float m_Y;
	float m_Z;

	// ориентация табло "на оператора"
	float m_DirX;
	float m_DirY;
	float m_DirZ;

	struct LampInfo
	{
		int Group;
		int Bit;
		int Type; // 0 - прямоугольная, 1 - круглая
		float X; // координата по оси X ( ноль слева ) 
		float Y; // координата по оси Y ( ноль снизу )
		float Angle; // ориентация ( 0 - направо и далее против часовой )
		XMVECTOR Color; // Цвет
	};

	scbPultTablo* m_PultTablo;
	vector<LampInfo> m_Lamps;

public:
	visualPultTablo ();
	virtual ~visualPultTablo ();

	HRESULT AssignPultTablo ( scbPultTablo* pt );
	void AddCellLamp ( int group, int bit, float x, float y, int angle, scbPultTablo::Color color );
	void AddRoundLamp ( int group, int bit, float x, float y, scbPultTablo::Color color );

	void SetPosition ( float x, float y, float z );
	void SetDirection ( float dirX, float dirY, float dirZ );

	virtual HRESULT InitGeometry () override;
	virtual void Render () override;

	static HRESULT InitBuffers ();
};
