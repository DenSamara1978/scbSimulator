#pragma once

#include <DirectXMath.h>
#include <vector>

using namespace DirectX;
using std::vector;

class visualAbstract
{
protected:
	vector<int> m_VertexBuffers;
	vector<int> m_IndexBuffers; // -1 если не индексированный буфер
	vector<int> m_VertexShaders;
	vector<int> m_PixelShaders;

	XMMATRIX m_WorldMatrix;
	bool m_IsCompleted;

public:
	visualAbstract ();
	virtual ~visualAbstract ();

	virtual HRESULT InitGeometry () abstract;
	virtual void Render () abstract;
};
