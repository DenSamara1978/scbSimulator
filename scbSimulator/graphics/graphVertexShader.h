#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "graphShader.h"

using namespace DirectX;
using std::string;

class graphVertexDeclaration;

class graphVertexShader : public graphShader
{
	ID3D11InputLayout* m_InputLayout;
	ID3D11VertexShader* m_VertexShader;
	graphVertexDeclaration* m_VertexDeclaration;

public:
	graphVertexShader ( const wstring& name );
	~graphVertexShader ();

	HRESULT Load ( const wstring& filename, const string& mainFunc );

	HRESULT Set ( ID3D11DeviceContext* pContext );

	void SetVertexDeclaration ( graphVertexDeclaration* vDecl );
	graphVertexDeclaration* GetVertexDeclaration ();
};

inline graphVertexDeclaration* graphVertexShader::GetVertexDeclaration ()
{
	return this->m_VertexDeclaration;
}
