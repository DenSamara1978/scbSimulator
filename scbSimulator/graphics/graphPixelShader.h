#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "graphShader.h"

using namespace DirectX;
using std::string;

class graphPixelShader : public graphShader
{
	ID3D11PixelShader * m_PixelShader;

public:
	graphPixelShader ( const wstring& name );
	~graphPixelShader ();

	HRESULT Load ( const wstring& filename, const string& mainFunc );

	HRESULT Set ( ID3D11DeviceContext* pContext );
};
