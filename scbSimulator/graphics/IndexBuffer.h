#pragma once

#include <d3d11.h>

namespace graphics
{
	class IndexBuffer
	{
	public:
		IndexBuffer ();
		~IndexBuffer ();

		HRESULT create (int nIndices, unsigned short* indices);

		int getIndexCount () const;
		HRESULT set (ID3D11DeviceContext* context);

	private:
		ID3D11Buffer* indexBuffer;
		int nIndices;
	};

	inline int IndexBuffer::getIndexCount() const
	{
		return this->nIndices;
	}
}
