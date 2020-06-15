#include "graphPixelShader.h"
#include "graphServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

graphPixelShader::graphPixelShader ( const wstring& name ) :
	graphShader ( name ),
	m_PixelShader ( nullptr )
{

}

graphPixelShader::~graphPixelShader ()
{
	SafeRelease ( &( this->m_PixelShader ) );
}

HRESULT graphPixelShader::Load ( const wstring& filename, const string& mainFunc )
{
	HRESULT hr;
	ID3DBlob* pBlobOut = nullptr;
	ID3DBlob* pErrorBlob;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	hr = D3DCompileFromFile ( filename.c_str (), nullptr, nullptr, mainFunc.c_str (), "ps_5_0", dwShaderFlags, 0, &pBlobOut, &pErrorBlob );
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
		MessageBox ( 0, L"Невозможно скомпилировать файл HLSL. Пожалуйста, запустите данную программу из папки, содержащей файл HLSL.", L"Ошибка", MB_OK );
		return hr;
	}
	hr = graphServer::Instance ()->GetDevice ()->CreatePixelShader ( pBlobOut->GetBufferPointer (), pBlobOut->GetBufferSize (), nullptr, &( this->m_PixelShader ) );
	pBlobOut->Release ();
	return hr;
}

HRESULT graphPixelShader::Set ( ID3D11DeviceContext* pContext )
{
	if ( this->m_IsChanged && ( this->m_ConstantBuffer != nullptr ))
		pContext->UpdateSubresource ( this->m_ConstantBuffer, 0, nullptr, this->m_Buffer, 0, 0 );
	this->m_IsChanged = false;
	pContext->PSSetShader ( this->m_PixelShader, nullptr, 0 );
	if ( this->m_ConstantBuffer != nullptr )
		pContext->PSSetConstantBuffers ( 0, 1, &( this->m_ConstantBuffer ) );
	return S_OK;
}
