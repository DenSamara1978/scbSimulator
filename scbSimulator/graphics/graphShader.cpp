#include "graphShader.h"
#include "graphServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

graphShader::graphShader ( const wstring& name ) :
	m_Buffer ( nullptr ),
	m_ConstantBuffer ( nullptr ),
	m_Name ( name ),
	m_BufferSize ( 0 ),
	m_IsChanged ( true )
{
}

graphShader::~graphShader ()
{
	if ( this->m_Buffer != nullptr )
	{
		delete [] this->m_Buffer;
		this->m_Buffer = nullptr;
	}
	this->m_BufferSize = 0;
	SafeRelease ( &( this->m_ConstantBuffer ) );
}

HRESULT graphShader::SetConstantType ( int index, ConstantType type )
{
	if ( ( this->m_ConstantBuffer != nullptr ) || ( index < 0 ) )
		return E_FAIL;
	if ( index >= static_cast < int > ( this->m_Constants.size () ) )
		this->m_Constants.resize ( index + 1, { No, 0 } );
	if ( this->m_Constants [index].Type != No )
		return E_FAIL;
	for ( auto& element : this->m_Constants )
		if ( element.Type == type ) return E_FAIL;
	this->m_Constants [index].Type = type;
	this->m_Constants [index].Offset = 0;
	return S_OK;
}

HRESULT graphShader::CreateConstantBuffer ()
{
	int offset = 0;
	for ( size_t i = 0; i < this->m_Constants.size (); i++ )
	{
		this->m_Constants [i].Offset = offset;
		switch ( this->m_Constants [i].Type )
		{
		case No:
			return E_FAIL;
			break;
		case WorldMatrix:
		case ViewMatrix:
		case ProjectionMatrix:
			offset += 64;
			break;
		case EmissiveColor:
		case DiffuseColor:
		case SpecularColor:
		case AmbientColor:
		case DirectionLightColor:
		case DirectionLightDir:
			offset += 16;
			break;
		}
	}
	if ( this->m_BufferSize != offset )
	{
		if ( this->m_Buffer != nullptr )
			delete [] this->m_Buffer;
		this->m_Buffer = new char [offset];
		this->m_BufferSize = offset;
	}
	D3D11_BUFFER_DESC bd;
	ZeroMemory ( &bd, sizeof ( bd ) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = this->m_BufferSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	SafeRelease ( &( this->m_ConstantBuffer ) );
	this->m_IsChanged = true;
	return graphServer::Instance ()->GetDevice ()->CreateBuffer ( &bd, nullptr, &( this->m_ConstantBuffer ) );
}

HRESULT graphShader::SetConstant ( ConstantType type, void* param )
{
	if ( ( type == No ) || ( param == nullptr ) ) return E_FAIL;

	for ( auto& element : this->m_Constants )
		if ( element.Type == type )
			return S_OK;
	return E_FAIL;
}

HRESULT graphShader::SetConstant ( ConstantType type, const XMMATRIX& matrix )
{
	if ( type == No ) return E_FAIL;

	int offset = 0;
	for ( auto& element : this->m_Constants )
	{
		if ( element.Type == type )
		{
			offset = element.Offset;
			switch ( type )
			{
			case WorldMatrix:
			case ViewMatrix:
			case ProjectionMatrix:

				this->m_IsChanged = true;
				*( reinterpret_cast < XMMATRIX* > ( this->m_Buffer + offset ) ) = XMMatrixTranspose ( matrix );
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT graphShader::SetConstant ( ConstantType type, const XMFLOAT4& vector )
{
	if ( type == No ) return E_FAIL;

	int offset = 0;
	for ( auto& element : this->m_Constants )
	{
		if ( element.Type == type )
		{
			offset = element.Offset;
			switch ( type )
			{
			case DiffuseColor:
			case SpecularColor:
			case AmbientColor:
			case EmissiveColor:
			case DirectionLightColor:
			case DirectionLightDir:

				this->m_IsChanged = true;
				*( reinterpret_cast < XMFLOAT4* > ( this->m_Buffer + offset ) ) = vector;
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT graphShader::SetConstant ( ConstantType type, const XMVECTOR& vector )
{
	if ( type == No ) return E_FAIL;

	int offset = 0;
	for ( auto& element : this->m_Constants )
	{
		if ( element.Type == type )
		{
			offset = element.Offset;
			switch ( type )
			{
			case DiffuseColor:
			case SpecularColor:
			case AmbientColor:
			case EmissiveColor:
			case DirectionLightColor:
			case DirectionLightDir:

				this->m_IsChanged = true;
				*( reinterpret_cast < XMVECTOR* > ( this->m_Buffer + offset ) ) = vector;
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}
