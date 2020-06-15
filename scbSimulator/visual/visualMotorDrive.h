#pragma once

#include "visualAbstract.h"

class scbMotorDrive;
class scbMotorDriveDevice;

class visualMotorDrive : public visualAbstract
{
	static int m_AutoSwitchVB;
	static int m_AutoSwitchIB;
	static int m_AutoSwitchVS;
	static int m_AutoSwitchPS;

	static int m_GateVB;
	static int m_GateIB;
	static int m_GateVS;
	static int m_GatePS;

	static int m_BaseVB;
	static int m_BaseIB;
	static int m_BaseVS;
	static int m_BasePS;

	static int m_LeftWedgeVB;
	static int m_LeftWedgeIB;
	static int m_LeftWedgeVS;
	static int m_LeftWedgePS;

	static int m_RightWedgeVB;
	static int m_RightWedgeIB;
	static int m_RightWedgeVS;
	static int m_RightWedgePS;

	static int m_FlapVB;
	static int m_FlapIB;
	static int m_FlapVS;
	static int m_FlapPS;

	static int m_ReductorVB;
	static int m_ReductorIB;
	static int m_ReductorVS;
	static int m_ReductorPS;

	static int m_MotorVB;
	static int m_MotorIB;
	static int m_MotorVS;
	static int m_MotorPS;

	static int m_ControlLineVB;
	static int m_ControlLineIB;
	static int m_ControlLineVS;
	static int m_ControlLinePS;

	static int m_SwivelCamVB;
	static int m_SwivelCamIB;
	static int m_SwivelCamVS;
	static int m_SwivelCamPS;

	// координаты основания привода
	float m_X;
	float m_Y;
	float m_Z;

	// направление привода
	float m_DirX;
	float m_DirY;
	float m_DirZ;

	scbMotorDriveDevice* m_MotorDevice;

public:
	visualMotorDrive ();
	virtual ~visualMotorDrive ();

	HRESULT AssignScbMotorDrive ( scbMotorDrive* md );

	void SetPosition ( float x, float y, float z );
	void SetDirection ( float dirX, float dirY, float dirZ );

	virtual HRESULT InitGeometry () override;
	virtual void Render () override;

	static HRESULT InitBuffers ();
};
