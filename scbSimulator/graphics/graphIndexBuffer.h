#pragma once

#include <d3d11.h>

class graphIndexBuffer
{
	ID3D11Buffer* m_IndexBuffer;
	int m_IndexCount;

public:
	graphIndexBuffer ();
	~graphIndexBuffer ();

	HRESULT Create ( int num_indices, unsigned short* indices );

	int GetIndexCount () const;
	HRESULT Set ( ID3D11DeviceContext* pContext );
};

inline int graphIndexBuffer::GetIndexCount () const
{
	return this->m_IndexCount;
}
