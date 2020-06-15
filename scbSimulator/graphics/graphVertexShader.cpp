#include "graphVertexShader.h"
#include "graphVertexDeclaration.h"
#include "graphServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

graphVertexShader::graphVertexShader ( const wstring& name ) :
	graphShader ( name ),
	m_VertexShader ( nullptr ),
	m_InputLayout ( nullptr ),
	m_VertexDeclaration ( nullptr )
{
}

graphVertexShader::~graphVertexShader ()
{
	SafeRelease ( &( this->m_InputLayout ) );
	SafeRelease ( &( this->m_VertexShader ) );
}

void graphVertexShader::SetVertexDeclaration ( graphVertexDeclaration* vDecl )
{
	this->m_VertexDeclaration = vDecl;
}

HRESULT graphVertexShader::Load ( const wstring& filename, const string& mainFunc )
{
	if ( this->m_VertexDeclaration == nullptr )
		return E_FAIL;

	HRESULT hr;
	ID3DBlob* pBlobOut = nullptr;
	ID3DBlob* pErrorBlob;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	hr = D3DCompileFromFile ( filename.c_str (), nullptr, nullptr, mainFunc.c_str (), "vs_5_0", dwShaderFlags, 0, &pBlobOut, &pErrorBlob );
	if ( FAILED ( hr ) )
	{
		if ( pErrorBlob != nullptr )
			OutputDebugStringA ( ( char* ) pErrorBlob->GetBufferPointer () );
		if ( pErrorBlob != nullptr )
			pErrorBlob->Release ();
		return hr;
	}
	if ( pErrorBlob != nullptr )
		pErrorBlob->Release ();
	if ( FAILED ( hr ) )
	{
		pBlobOut->Release ();
		MessageBox ( 0, L"Невозможно скомпилировать файл HLSL. Пожалуйста, запустите данную программу из папки, содержащей файл HLSL.", L"Ошибка", MB_OK );
		return hr;
	}
	hr = graphServer::Instance ()->GetDevice ()->CreateVertexShader ( pBlobOut->GetBufferPointer (), pBlobOut->GetBufferSize (), nullptr, &( this->m_VertexShader ) );
	if ( hr != S_OK )
	{
		pBlobOut->Release ();
		return hr;
	}

	int desc_count = this->m_VertexDeclaration->GetDescCount ();
	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC [desc_count];
	for ( int i = 0; i < desc_count; i++ )
	{
		layout [i].SemanticIndex = 0;
		switch ( this->m_VertexDeclaration->GetElementType ( i ) )
		{
		case graphVertexDeclaration::Position:
			layout [i].SemanticName = "POSITION";
			layout [i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case graphVertexDeclaration::Normal:
			layout [i].SemanticName = "NORMAL";
			layout [i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case graphVertexDeclaration::DiffuseColor:
		case graphVertexDeclaration::SpecularColor:
		case graphVertexDeclaration::EmissiveColor:
			layout [i].SemanticName = "COLOR";
			layout [i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}
		layout [i].InputSlot = 0;
		layout [i].AlignedByteOffset = this->m_VertexDeclaration->GetElementOffset ( i );
		layout [i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout [i].InstanceDataStepRate = 0;
	}

	hr = graphServer::Instance ()->GetDevice ()->CreateInputLayout ( layout, desc_count, pBlobOut->GetBufferPointer (), pBlobOut->GetBufferSize (), &( this->m_InputLayout ) );

	delete [] layout;
	pBlobOut->Release ();
	return hr;
}

HRESULT graphVertexShader::Set ( ID3D11DeviceContext* pContext )
{
	if ( this->m_IsChanged && ( this->m_ConstantBuffer != nullptr ))
		pContext->UpdateSubresource ( this->m_ConstantBuffer, 0, nullptr, this->m_Buffer, 0, 0 );
	this->m_IsChanged = false;
	pContext->IASetInputLayout ( this->m_InputLayout );
	pContext->VSSetShader ( this->m_VertexShader, nullptr, 0 );
	if ( this->m_ConstantBuffer != nullptr )
		pContext->VSSetConstantBuffers ( 0, 1, &( this->m_ConstantBuffer ));
	return S_OK;
}
