#include "IndexBuffer.h"
#include "GraphicsServer.h"
#include "..\stdafx.h"

using namespace graphics;

IndexBuffer::IndexBuffer() :
	indexBuffer(nullptr),
	nIndices(0)
{

}

IndexBuffer::~IndexBuffer()
{
	SafeRelease(&( this->indexBuffer));
}

HRESULT IndexBuffer::create(int nIndices, unsigned short* indices)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned short) * nIndices;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	this->nIndices = nIndices;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof (D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = indices;
	HRESULT hr = GraphicsServer::getInstance()->getD3dDevice()->CreateBuffer(&bd, &initData, &(this->indexBuffer));
	return hr;
}

HRESULT IndexBuffer::set(ID3D11DeviceContext* context)
{
	context->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	return S_OK;
}
