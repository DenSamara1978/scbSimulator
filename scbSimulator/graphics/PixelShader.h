#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "Shader.h"

using namespace DirectX;
using std::string;

namespace graphics
{

	class PixelShader : public Shader
	{
	public:
		PixelShader (const wstring& name);
		~PixelShader ();

		HRESULT load (const wstring& fileName, const string& mainFunc);

		HRESULT set (ID3D11DeviceContext* context);

	private:
		ID3D11PixelShader* pixelShader;
	};
}