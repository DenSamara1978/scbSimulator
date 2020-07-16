#include "VertexShader.h"
#include "VertexDeclaration.h"
#include "GraphicsServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace graphics;

VertexShader::VertexShader(const wstring& shaderName) :
	Shader(shaderName),
	vertexShader(nullptr),
	inputLayout(nullptr),
	vertexDeclaration(nullptr)
{
}

VertexShader::~VertexShader()
{
	SafeRelease(&(this->inputLayout));
	SafeRelease(&(this->vertexShader));
}

void VertexShader::setVertexDeclaration(VertexDeclaration* vertexDeclaration)
{
	this->vertexDeclaration = vertexDeclaration;
}

HRESULT VertexShader::load(const wstring& fileName, const string& mainFunc)
{
	if (this->vertexDeclaration == nullptr)
		return E_FAIL;

	HRESULT hr;
	ID3DBlob* pBlobOut = nullptr;
	ID3DBlob* pErrorBlob;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, mainFunc.c_str(), "vs_5_0", dwShaderFlags, 0, &pBlobOut, &pErrorBlob);
	if (pErrorBlob != nullptr)
	{
		if (FAILED(hr))
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		pErrorBlob->Release();
	}
	if (FAILED(hr))
	{
		pBlobOut->Release();
		MessageBox(0, L"Невозможно скомпилировать файл HLSL. Пожалуйста, запустите данную программу из папки, содержащей файл HLSL.", L"Ошибка", MB_OK);
		return hr;
	}
	hr = GraphicsServer::getInstance()->getD3dDevice()->CreateVertexShader(pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), nullptr, &(this->vertexShader));
	if (hr != S_OK)
	{
		pBlobOut->Release();
		return hr;
	}

	int descriptorCount = static_cast<int>(this->vertexDeclaration->getDescriptorCount());
	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[descriptorCount];
	for (int i = 0; i < descriptorCount; i++)
	{
		layout[i].SemanticIndex = 0;
		switch (this->vertexDeclaration->getElementType(i))
		{
			case VertexDeclaration::Type::Position:
				layout[i].SemanticName = "POSITION";
				layout[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case VertexDeclaration::Type::Normal:
				layout[i].SemanticName = "NORMAL";
				layout[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case VertexDeclaration::Type::DiffuseColor:
			case VertexDeclaration::Type::SpecularColor:
			case VertexDeclaration::Type::EmissiveColor:
				layout[i].SemanticName = "COLOR";
				layout[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
		}
		layout[i].InputSlot = 0;
		layout[i].AlignedByteOffset = this->vertexDeclaration->getElementOffset(i);
		layout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout[i].InstanceDataStepRate = 0;
	}

	hr = GraphicsServer::getInstance()->getD3dDevice()->CreateInputLayout(layout, descriptorCount, pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), &(this->inputLayout));

	delete[] layout;
	pBlobOut->Release();
	return hr;
}

HRESULT VertexShader::set(ID3D11DeviceContext* context)
{
	if (this->isChanged and (this->constantBuffer != nullptr))
		context->UpdateSubresource(this->constantBuffer, 0, nullptr, this->buffer, 0, 0);
	this->isChanged = false;
	context->IASetInputLayout(this->inputLayout);
	context->VSSetShader(this->vertexShader, nullptr, 0);
	if (this->constantBuffer != nullptr)
		context->VSSetConstantBuffers(0, 1, &(this->constantBuffer));
	return S_OK;
}
