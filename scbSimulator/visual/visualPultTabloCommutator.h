#pragma once

#include "visualAbstract.h"

class scbPultTabloAbstractCommutator;
class scbPultTablo;

class visualPultTabloCommutator : public visualAbstract
{
	static int m_VB;
	static int m_PlateVB;
	static int m_VS;
	static int m_PS;
	static int m_IB;
	static int m_PlateIB;

	// координаты основания коммутатора
	float m_X;
	float m_Y;
	float m_Z;

	// направление головки коммутатора
	float m_DirX;
	float m_DirY;
	float m_DirZ;

	XMVECTOR m_DiffuseColor;
	XMVECTOR m_SpecularColor;

	scbPultTabloAbstractCommutator* m_CommutatorLink;

public:
	visualPultTabloCommutator ();
	virtual ~visualPultTabloCommutator ();

	HRESULT AssignCommutator ( scbPultTablo* pt, int device );

	void SetPosition ( float x, float y, float z );
	void SetDirection ( float dirX, float dirY, float dirZ );

	virtual HRESULT InitGeometry () override;
	virtual void Render () override;

	static HRESULT InitBuffers ();
};
