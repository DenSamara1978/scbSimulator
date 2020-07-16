#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

using namespace DirectX;
using std::wstring;
using std::vector;

namespace graphics
{

	class Shader
	{
	public:
		enum class ConstantType
		{
			No = 0,
			WorldMatrix,
			ViewMatrix,
			ProjectionMatrix,
			DiffuseColor,
			SpecularColor,
			EmissiveColor,
			DirectionLightDir,
			DirectionLightColor,
			AmbientColor,
		};

		struct Constant
		{
			ConstantType type;
			int offset;
		};

		Shader(const wstring& shaderName);
		~Shader ();

		HRESULT setConstantType(int index, ConstantType type);
		HRESULT createConstantBuffer();
		bool isA(const wstring& description) const;

		HRESULT setConstant(ConstantType type, float* param);
		HRESULT setConstant(ConstantType type, const XMMATRIX& matrix);
		HRESULT setConstant(ConstantType type, const XMFLOAT4& vector);
		HRESULT setConstant(ConstantType type, const XMVECTOR& vector);

	protected:
		ID3D11Buffer* constantBuffer;
		vector<Constant> constants;
		char* buffer;
		int bufferSize;
		wstring name;
		bool isChanged;
	};

	inline bool Shader::isA(const wstring& name) const
	{
		return (this->name == name);
	}
}