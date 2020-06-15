#pragma once

#include <d3d11.h>
#include "graphServer.h"

class graphVertexDeclaration;

class graphVertexBuffer
{
	int m_VertexCount;
	ID3D11Buffer* m_VertexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;

	graphVertexDeclaration* m_VertexDeclaration;
	char* m_Buffer;

public:
	graphVertexBuffer ( graphVertexDeclaration* vDecl, int vCount, graphServer::TopologyType topology );
	~graphVertexBuffer ();

	int GetVertexCount () const;
	void SetPosition ( int index, float x, float y, float z );
	void SetNormal ( int index, float x, float y, float z );
	void SetDiffuseColor ( int index, float r, float g, float b, float a );
	void SetSpecularColor ( int index, float r, float g, float b, float a );
	void SetEmissiveColor ( int index, float r, float g, float b, float a );
	HRESULT Create ();

	HRESULT Set ( ID3D11DeviceContext* pContext );
};

inline int graphVertexBuffer::GetVertexCount () const
{
	return this->m_VertexCount;
}
