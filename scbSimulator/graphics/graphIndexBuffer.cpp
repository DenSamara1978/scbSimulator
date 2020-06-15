#include "graphIndexBuffer.h"
#include "graphServer.h"
#include "..\stdafx.h"

graphIndexBuffer::graphIndexBuffer () :
	m_IndexBuffer ( nullptr ),
	m_IndexCount ( 0 )
{

}

graphIndexBuffer::~graphIndexBuffer ()
{
	SafeRelease ( &( this->m_IndexBuffer ) );
}

HRESULT graphIndexBuffer::Create ( int num_indices, unsigned short* indices )
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory ( &bd, sizeof ( bd ) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof ( unsigned short ) * num_indices;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	this->m_IndexCount = num_indices;
	if ( indices != nullptr )
	{
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory ( &InitData, sizeof ( InitData ) );
		InitData.pSysMem = indices;
		return graphServer::Instance ()->GetDevice ()->CreateBuffer ( &bd, &InitData, &( this->m_IndexBuffer ));
	}
	else
		return graphServer::Instance ()->GetDevice ()->CreateBuffer ( &bd, nullptr, &( this->m_IndexBuffer ));
}

HRESULT graphIndexBuffer::Set ( ID3D11DeviceContext* pContext )
{
	pContext->IASetIndexBuffer ( this->m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	return S_OK;
}
