#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "Shader.h"

using namespace DirectX;
using std::string;

namespace graphics
{
	class VertexDeclaration;

	class VertexShader : public Shader
	{
	public:
		VertexShader(const wstring& shaderName);
		~VertexShader();

		HRESULT load(const wstring& fileName, const string& mainFunc);

		HRESULT set(ID3D11DeviceContext* context);

		void setVertexDeclaration(VertexDeclaration* vertexDeclaration);
		VertexDeclaration* getVertexDeclaration();

	private:
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		VertexDeclaration* vertexDeclaration;

	};

	inline VertexDeclaration* VertexShader::getVertexDeclaration()
	{
		return this->vertexDeclaration;
	}
}