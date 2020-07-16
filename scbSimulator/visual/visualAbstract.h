#pragma once

#include <DirectXMath.h>
#include <vector>
#include "..\util\Color.h"

using namespace DirectX;
using std::vector;

using util::Color;

namespace visual
{
	class VisualAbstract
	{
	public:
		VisualAbstract ();
		virtual ~VisualAbstract ();

		virtual bool initializeGeometry() abstract;
		virtual void render() abstract;

	protected:
		XMVECTOR getD3dColor(Color color) const;

		vector<int> vertexBuffers;
		vector<int> indexBuffers; // -1 если не индексированный буфер
		vector<int> vertexShaders;
		vector<int> pixelShaders;

		XMMATRIX worldMatrix;
		bool isCompleted;
	};

	inline XMVECTOR VisualAbstract::getD3dColor(Color color) const
	{
		XMVECTOR vectorColor;
		switch (color)
		{
			case Color::Black:
				vectorColor = XMVectorSet(0.2f, 0.2f, 0.2f, 1.0f);
				break;
			case Color::Red:
				vectorColor = XMVectorSet(0.9f, 0.0f, 0.0f, 1.0f);
				break;
			case Color::White:
				vectorColor = XMVectorSet(0.9f, 0.9f, 0.9f, 1.0f);
				break;
			case Color::Blue:
				vectorColor = XMVectorSet(0.2f, 0.2f, 0.9f, 1.0f);
				break;
			case Color::Yellow:
				vectorColor = XMVectorSet(0.9f, 0.9f, 0.2f, 1.0f);
				break;
			case Color::Green:
				vectorColor = XMVectorSet(0.2f, 0.9f, 0.2f, 1.0f);
				break;
			case Color::Milk:
				vectorColor = XMVectorSet(0.9f, 0.9f, 0.5f, 1.0f);
				break;

			default:
				vectorColor = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
				break;
		}
		return vectorColor;
	}
}
