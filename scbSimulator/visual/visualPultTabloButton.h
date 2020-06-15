#pragma once

#include "visualAbstract.h"

class scbPultTabloAbstractButton;
class scbPultTablo;

class visualPultTabloButton : public visualAbstract
{
	static int m_VB;
	static int m_PlateVB;
	static int m_VS;
	static int m_PS;
	static int m_IB;
	static int m_PlateIB;

	// координаты основания кнопки
	float m_X;
	float m_Y;
	float m_Z;

	// направление головки кнопки
	float m_DirX;
	float m_DirY;
	float m_DirZ;

	XMVECTOR m_DiffuseColor;
	XMVECTOR m_SpecularColor;

	scbPultTabloAbstractButton* m_ButtonLink;

public:
	visualPultTabloButton ();
	virtual ~visualPultTabloButton ();

	HRESULT AssignButton ( scbPultTablo* pt, int device );

	void SetPosition ( float x, float y, float z );
	void SetDirection ( float dirX, float dirY, float dirZ );

	virtual HRESULT InitGeometry () override;
	virtual void Render () override;

	static HRESULT InitBuffers ();
};
