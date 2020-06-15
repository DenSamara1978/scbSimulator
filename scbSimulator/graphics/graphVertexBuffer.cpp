#include "graphVertexBuffer.h"
#include "graphVertexDeclaration.h"
#include "..\stdafx.h"

graphVertexBuffer::graphVertexBuffer ( graphVertexDeclaration* vDecl, int vCount, graphServer::TopologyType topology ) :
	m_VertexBuffer ( nullptr ),
	m_VertexCount ( vCount ),
	m_VertexDeclaration ( vDecl )
{
	switch ( topology )
	{
	case graphServer::PointList:
		this->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case graphServer::LineList:
		this->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case graphServer::LineStrip:
		this->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		break;
	case graphServer::TriangleList:
		this->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case graphServer::TriangleStrip:
		this->m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	}
	this->m_Buffer = new char [vCount * vDecl->GetVertexSize ()];
}

graphVertexBuffer::~graphVertexBuffer ()
{
	if ( this->m_Buffer != nullptr )
	{
		delete [] this->m_Buffer;
		this->m_Buffer = nullptr;
	}
	SafeRelease ( &( this->m_VertexBuffer ) );
}

void graphVertexBuffer::SetPosition ( int index, float x, float y, float z )
{
	int byteIndex = this->m_VertexDeclaration->GetVertexSize () * index + this->m_VertexDeclaration->GetPositionOffset ();

	float* ptr = reinterpret_cast < float* > ( this->m_Buffer + byteIndex );
	ptr [0] = x;
	ptr [1] = y;
	ptr [2] = z;
}

void graphVertexBuffer::SetNormal ( int index, float x, float y, float z )
{
	int byteIndex = this->m_VertexDeclaration->GetVertexSize () * index + this->m_VertexDeclaration->GetNormalOffset ();

	float* ptr = reinterpret_cast < float* > ( this->m_Buffer + byteIndex );
	ptr [0] = x;
	ptr [1] = y;
	ptr [2] = z;
}

void graphVertexBuffer::SetDiffuseColor ( int index, float r, float g, float b, float a )
{
	int byteIndex = this->m_VertexDeclaration->GetVertexSize () * index + this->m_VertexDeclaration->GetDiffuseColorOffset ();

	float* ptr = reinterpret_cast < float* > ( this->m_Buffer + byteIndex );
	ptr [0] = r;
	ptr [1] = g;
	ptr [2] = b;
	ptr [3] = a;
}

void graphVertexBuffer::SetSpecularColor ( int index, float r, float g, float b, float a )
{
	int byteIndex = this->m_VertexDeclaration->GetVertexSize () * index + this->m_VertexDeclaration->GetSpecularColorOffset ();

	float* ptr = reinterpret_cast < float* > ( this->m_Buffer + byteIndex );
	ptr [0] = r;
	ptr [1] = g;
	ptr [2] = b;
	ptr [3] = a;
}

void graphVertexBuffer::SetEmissiveColor ( int index, float r, float g, float b, float a )
{
	int byteIndex = this->m_VertexDeclaration->GetVertexSize () * index + this->m_VertexDeclaration->GetEmissiveColorOffset ();

	float* ptr = reinterpret_cast < float* > ( this->m_Buffer + byteIndex );
	ptr [0] = r;
	ptr [1] = g;
	ptr [2] = b;
	ptr [3] = a;
}

HRESULT graphVertexBuffer::Create ()
{
	D3D11_BUFFER_DESC bd;
	graphServer* server = graphServer::Instance ();
	ZeroMemory ( &bd, sizeof ( bd ) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = this->m_VertexCount * this->m_VertexDeclaration->GetVertexSize ();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	if ( this->m_Buffer != nullptr )
	{
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory ( &InitData, sizeof ( InitData ) );
		InitData.pSysMem = this->m_Buffer;
		HRESULT hr = graphServer::Instance ()->GetDevice ()->CreateBuffer ( &bd, &InitData, &( this->m_VertexBuffer ));
		delete [] this->m_Buffer;
		this->m_Buffer = nullptr;
		return hr;
	}
	else
		return graphServer::Instance ()->GetDevice ()->CreateBuffer ( &bd, nullptr, &( this->m_VertexBuffer ));
}

HRESULT graphVertexBuffer::Set ( ID3D11DeviceContext* pContext )
{
	UINT stride = this->m_VertexDeclaration->GetVertexSize ();
	UINT offset = 0;
	pContext->IASetPrimitiveTopology ( this->m_PrimitiveTopology );
	pContext->IASetVertexBuffers ( 0, 1, &( this->m_VertexBuffer ), &stride, &offset );
	return S_OK;
}
