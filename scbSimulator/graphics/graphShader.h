#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

using namespace DirectX;
using std::wstring;
using std::vector;

class graphShader
{
public:
	enum ConstantType
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
		ConstantType Type;
		int Offset;
	};

protected:
	ID3D11Buffer* m_ConstantBuffer;
	vector<Constant> m_Constants;
	char* m_Buffer;
	int m_BufferSize;
	wstring m_Name;
	bool m_IsChanged;

public:
	graphShader ( const wstring& name );
	~graphShader ();

	HRESULT SetConstantType ( int index, ConstantType type );
	HRESULT CreateConstantBuffer ();
	bool IsA ( const wstring& description ) const;

	HRESULT SetConstant ( ConstantType type, void* param );
	HRESULT SetConstant ( ConstantType type, const XMMATRIX& matrix );
	HRESULT SetConstant ( ConstantType type, const XMFLOAT4& vector );
	HRESULT SetConstant ( ConstantType type, const XMVECTOR& vector );
};

inline bool graphShader::IsA ( const wstring& name ) const
{
	return ( this->m_Name == name );
}
