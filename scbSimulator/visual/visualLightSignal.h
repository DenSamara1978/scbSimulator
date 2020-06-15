#pragma once

#include <vector>
#include <DirectXMath.h>
#include "visualAbstract.h"

using std::vector;
using namespace DirectX;

class scbLightSignal;
class scbLightSignalLamp;

class visualLightSignal : public visualAbstract
{
	static int m_GenVB;
	static int m_GenVS;
	static int m_GenPS;
	static int m_LensVB;
	static int m_LensVS;
	static int m_LensPS;
	static int m_IB;

	// координаты основания светофора
	float m_X;
	float m_Y;
	float m_Z;

	// направление светофора
	float m_DirX;
	float m_DirY;
	float m_DirZ;

	struct LampDesc
	{
		XMVECTOR Color;
		scbLightSignalLamp* Link;
		float X;
		float Y;
		float Z;
		float DirX;
		float DirY;
		float DirZ;
	};

	vector<LampDesc> m_Lamps;

public:
	visualLightSignal ();
	virtual ~visualLightSignal ();

	HRESULT AssignScbLightSignal ( scbLightSignal* ls );

	void SetPosition ( float x, float y, float z );
	void SetDirection ( float dirX, float dirY, float dirZ );

	virtual HRESULT InitGeometry () override;
	virtual void Render () override;

	static HRESULT InitBuffers ();
};
