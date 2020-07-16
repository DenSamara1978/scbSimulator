#pragma once

#include <d3d11.h>
#include "GraphicsServer.h"

namespace graphics
{

	class VertexDeclaration;

	class VertexBuffer
	{
	public:
		VertexBuffer (VertexDeclaration* vertexDeclaration, int nVertices, GraphicsServer::TopologyType topology);
		~VertexBuffer ();

		int getVertexCount () const;
		void setPosition (int index, float x, float y, float z);
		void setNormal (int index, float x, float y, float z);
		void setDiffuseColor (int index, float red, float green, float blue, float alpha);
		void setSpecularColor (int index, float red, float green, float blue, float alpha);
		void setEmissiveColor (int index, float red, float green, float blue, float alpha);
		HRESULT create ();

		HRESULT set (ID3D11DeviceContext* context);

	private:
		void setComponent(int index, int offset, float x, float y, float z);
		void setComponent (int index, int offset, float red, float green, float blue, float alpha);

		int nVertices;
		ID3D11Buffer* vertexBuffer;
		D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;

		VertexDeclaration* vertexDeclaration;
		char* buffer;
	};

	inline int VertexBuffer::getVertexCount () const
	{
		return this->nVertices;
	}
}