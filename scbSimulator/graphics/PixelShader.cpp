#include "PixelShader.h"
#include "GraphicsServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace graphics;

PixelShader::PixelShader(const wstring& shaderName) :
	Shader(shaderName),
	pixelShader(nullptr)
{

}

PixelShader::~PixelShader ()
{
	SafeRelease(&(this->pixelShader));
}

HRESULT PixelShader::load(const wstring& fileName, const string& mainFunc)
{
	HRESULT hr;
	ID3DBlob* pBlobOut = nullptr;
	ID3DBlob* pErrorBlob;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, mainFunc.c_str(), "ps_5_0", dwShaderFlags, 0, &pBlobOut, &pErrorBlob);
	if (pErrorBlob != nullptr)
	{
		if (FAILED(hr))
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		pErrorBlob->Release();
	}
	if (FAILED(hr))
	{
		MessageBox(0, L"Невозможно скомпилировать файл HLSL. Пожалуйста, запустите данную программу из папки, содержащей файл HLSL.", L"Ошибка", MB_OK);
		return hr;
	}
	hr = GraphicsServer::getInstance()->getD3dDevice()->CreatePixelShader(pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), nullptr, &(this->pixelShader));
	pBlobOut->Release();
	return hr;
}

HRESULT PixelShader::set(ID3D11DeviceContext* context)
{
	if (this->isChanged and (this->constantBuffer != nullptr))
		context->UpdateSubresource(this->constantBuffer, 0, nullptr, this->buffer, 0, 0);
	this->isChanged = false;
	context->PSSetShader(this->pixelShader, nullptr, 0);
	if (this->constantBuffer != nullptr)
		context->PSSetConstantBuffers(0, 1, &(this->constantBuffer));
	return S_OK;
}
