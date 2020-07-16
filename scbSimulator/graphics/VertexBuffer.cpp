#include "VertexBuffer.h"
#include "VertexDeclaration.h"
#include "..\stdafx.h"

using namespace graphics;

VertexBuffer::VertexBuffer(VertexDeclaration* vertexDeclaration, int nVertices, GraphicsServer::TopologyType topology) :
	vertexBuffer(nullptr),
	nVertices (nVertices),
	vertexDeclaration (vertexDeclaration)
{
	switch ( topology )
	{
		case GraphicsServer::TopologyType::PointList:
			this->primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		case GraphicsServer::TopologyType::LineList:
			this->primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case GraphicsServer::TopologyType::LineStrip:
			this->primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case GraphicsServer::TopologyType::TriangleList:
			this->primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case GraphicsServer::TopologyType::TriangleStrip:
			this->primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
	}
	auto size = nVertices * vertexDeclaration->getVertexSize();
	this->buffer = new char[size];
}

VertexBuffer::~VertexBuffer()
{
	if (this->buffer != nullptr)
	{
		delete[] this->buffer;
		this->buffer = nullptr;
	}
	SafeRelease(&(this->vertexBuffer));
}

void VertexBuffer::setComponent(int index, int offset, float x, float y, float z)
{
	int byteIndex = this->vertexDeclaration->getVertexSize() * index + offset;
	float* ptr = reinterpret_cast<float*>(this->buffer + byteIndex);
	ptr[0] = x;
	ptr[1] = y;
	ptr[2] = z;
}

void VertexBuffer::setComponent(int index, int offset, float red, float green, float blue, float alpha)
{
	int byteIndex = this->vertexDeclaration->getVertexSize() * index + offset;
	float* ptr = reinterpret_cast<float*>(this->buffer + byteIndex);
	ptr[0] = red;
	ptr[1] = green;
	ptr[2] = blue;
	ptr[3] = alpha;
}

void VertexBuffer::setPosition(int index, float x, float y, float z)
{
	this->setComponent(index, vertexDeclaration->getPositionOffset(), x, y, z);
}

void VertexBuffer::setNormal(int index, float x, float y, float z)
{
	this->setComponent(index, vertexDeclaration->getNormalOffset(), x, y, z);
}

void VertexBuffer::setDiffuseColor(int index, float red, float green, float blue, float alpha)
{
	this->setComponent(index, vertexDeclaration->getDiffuseColorOffset(), red, green, blue, alpha);
}

void VertexBuffer::setSpecularColor(int index, float red, float green, float blue, float alpha)
{
	this->setComponent(index, vertexDeclaration->getSpecularColorOffset(), red, green, blue, alpha);
}

void VertexBuffer::setEmissiveColor(int index, float red, float green, float blue, float alpha)
{
	this->setComponent(index, vertexDeclaration->getEmissiveColorOffset(), red, green, blue, alpha);
}

HRESULT VertexBuffer::create()
{
	D3D11_BUFFER_DESC bd;
	GraphicsServer* server = GraphicsServer::getInstance();
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = this->nVertices * this->vertexDeclaration->getVertexSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = this->buffer;
	HRESULT hr =  GraphicsServer::getInstance()->getD3dDevice()->CreateBuffer(&bd, &initData, &(this->vertexBuffer));
	return hr;
}

HRESULT VertexBuffer::set(ID3D11DeviceContext* context)
{
	UINT stride = this->vertexDeclaration->getVertexSize();
	UINT offset = 0;
	context->IASetPrimitiveTopology(this->primitiveTopology);
	context->IASetVertexBuffers(0, 1, &(this->vertexBuffer), &stride, &offset);
	return S_OK;
}
