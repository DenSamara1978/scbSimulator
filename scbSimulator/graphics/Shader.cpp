#include "Shader.h"
#include "GraphicsServer.h"
#include "..\stdafx.h"

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace graphics;

Shader::Shader(const wstring& name) :
	buffer(nullptr),
	constantBuffer(nullptr),
	name(name),
	bufferSize(0),
	isChanged(true)
{
}

Shader::~Shader()
{
	if (this->buffer != nullptr)
	{
		delete[] this->buffer;
		this->buffer = nullptr;
	}
	this->bufferSize = 0;
	SafeRelease(&( this->constantBuffer));
}

HRESULT Shader::setConstantType(int index, ConstantType type)
{
	if ((this->constantBuffer != nullptr) or (index < 0))
		return E_FAIL;
	if (index >= static_cast<int>( this->constants.size()))
		this->constants.resize(index + 1, {ConstantType::No, 0});
	if ( this->constants[index].type != ConstantType::No)
		return E_FAIL;
	for (auto& element : this->constants)
		if (element.type == type)
			return E_FAIL;
	this->constants[index].type = type;
	this->constants[index].offset = 0;
	return S_OK;
}

HRESULT Shader::createConstantBuffer()
{
	int offset = 0;
	const auto length = this->constants.size();
	for (size_t i = 0; i < length; ++i)
	{
		this->constants[i].offset = offset;
		switch (this->constants [i].type)
		{
			case ConstantType::No:
				return E_FAIL;
				break;
			case ConstantType::WorldMatrix:
			case ConstantType::ViewMatrix:
			case ConstantType::ProjectionMatrix:
				offset += 64;
				break;
			case ConstantType::EmissiveColor:
			case ConstantType::DiffuseColor:
			case ConstantType::SpecularColor:
			case ConstantType::AmbientColor:
			case ConstantType::DirectionLightColor:
			case ConstantType::DirectionLightDir:
				offset += 16;
				break;
		}
	}
	if (this->bufferSize != offset)
	{
		if (this->buffer != nullptr)
			delete[] this->buffer;
		this->buffer = new char[offset];
		this->bufferSize = offset;
	}
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = this->bufferSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	SafeRelease(&(this->constantBuffer));
	this->isChanged = true;
	return GraphicsServer::getInstance()->getD3dDevice()->CreateBuffer(&bd, nullptr, &(this->constantBuffer));
}

HRESULT Shader::setConstant(ConstantType type, float* param)
{
	if ((type == ConstantType::No ) or (param == nullptr))
		return E_FAIL;

	for (auto& element : this->constants)
	{
		if (element.type == type)
		{
			auto offset = element.offset;
			this->isChanged = true;
			*(reinterpret_cast<float*>(this->buffer + offset)) = *param;
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT Shader::setConstant(ConstantType type, const XMMATRIX& matrix)
{
	if (type == ConstantType::No)
		return E_FAIL;

	for (auto& element : this->constants)
	{
		if (element.type == type)
		{
			auto offset = element.offset;
			switch (type)
			{
			case ConstantType::WorldMatrix:
			case ConstantType::ViewMatrix:
			case ConstantType::ProjectionMatrix:
				this->isChanged = true;
				*(reinterpret_cast<XMMATRIX*>(this->buffer + offset)) = XMMatrixTranspose(matrix);
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT Shader::setConstant(ConstantType type, const XMFLOAT4& vector)
{
	if (type == ConstantType::No) 
		return E_FAIL;

	for (auto& element : this->constants)
	{
		if (element.type == type)
		{
			auto offset = element.offset;
			switch (type)
			{
			case ConstantType::DiffuseColor:
			case ConstantType::SpecularColor:
			case ConstantType::AmbientColor:
			case ConstantType::EmissiveColor:
			case ConstantType::DirectionLightColor:
			case ConstantType::DirectionLightDir:
				this->isChanged = true;
				*(reinterpret_cast<XMFLOAT4*>(this->buffer + offset)) = vector;
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT Shader::setConstant(ConstantType type, const XMVECTOR& vector)
{
	if (type == ConstantType::No) 
		return E_FAIL;

	for (auto& element : this->constants)
	{
		if (element.type == type)
		{
			auto offset = element.offset;
			switch (type)
			{
			case ConstantType::DiffuseColor:
			case ConstantType::SpecularColor:
			case ConstantType::AmbientColor:
			case ConstantType::EmissiveColor:
			case ConstantType::DirectionLightColor:
			case ConstantType::DirectionLightDir:
				this->isChanged = true;
				*(reinterpret_cast<XMVECTOR*>(this->buffer + offset)) = vector;
				break;
			}
			return S_OK;
		}
	}
	return E_FAIL;
}
