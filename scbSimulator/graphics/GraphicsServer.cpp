#include <dxgi.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexDeclaration.h"
#include "Camera.h"
#include "..\application\Application.h"
#include "..\stdafx.h"
#include "..\util\range.h"

using util::inRange;

using namespace graphics;
using application::Application;

GraphicsServer* GraphicsServer::instance = nullptr;

GraphicsServer::GraphicsServer() :
	driverType(D3D_DRIVER_TYPE_HARDWARE),
	featureLevel(D3D_FEATURE_LEVEL_11_0),
	d3dDevice(nullptr),
	immediateContext(nullptr),
	swapChain(nullptr),
	renderTargetView(nullptr),
	depthStencil(nullptr),
	depthStencilView(nullptr),
	currentCamera(0)
{
	GraphicsServer::instance = this;
	Camera* camera = new Camera;
	this->cameras.push_back(camera);
}

GraphicsServer::~GraphicsServer()
{
	for (auto& ptr : this->vertexDeclarations)
	{
		delete ptr;
		ptr = nullptr;
	}
	for (auto& ptr : this->vertexShaders)
	{
		delete ptr;
		ptr = nullptr;
	}
	for (auto& ptr : this->pixelShaders)
	{
		delete ptr;
		ptr = nullptr;
	}
	for (auto& ptr : this->vertexBuffers)
	{
		delete ptr;
		ptr = nullptr;
	}
	for (auto& ptr : this->indexBuffers)
	{
		delete ptr;
		ptr = nullptr;
	}
	for (auto& ptr : this->cameras)
	{
		delete ptr;
		ptr = nullptr;
	}
	this->cleanupDevice();
	GraphicsServer::instance = nullptr;
}

void GraphicsServer::cleanupDevice()
{
	if (this->immediateContext)
		this->immediateContext->ClearState();

	SafeRelease(&(this->depthStencil));
	SafeRelease(&(this->depthStencilView));
	SafeRelease(&(this->renderTargetView));
	SafeRelease(&(this->swapChain));
	SafeRelease(&(this->immediateContext));
	SafeRelease(&(this->d3dDevice));
}

HRESULT GraphicsServer::initializeDevice()
{
	HRESULT hr = S_OK;
	UINT width = Application::getInstance()->getMainWindowWidth();
	UINT height = Application::getInstance()->getMainWindowHeight();
	UINT createDeviceFlags = 0;
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	const UINT numDriverTypes = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 75;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Application::getInstance()->getHwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	for (unsigned int i = 0; i < numDriverTypes; ++i)
	{
		this->driverType = driverTypes[i];
//		hr = D3D11CreateDeviceAndSwapChain ( nullptr, this->m_DriverType, 0, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &sd, &( this->m_SwapChain ), &( this->m_D3dDevice ), &( this->m_FeatureLevel ), &( this->m_ImmediateContext ) );
		hr = D3D11CreateDevice(nullptr, this->driverType, 0, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &(this->d3dDevice), &(this->featureLevel), &(this->immediateContext));
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	IDXGIDevice* device = nullptr;
	hr = this->d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&device);

	IDXGIAdapter* adapter = nullptr;
	hr = device->GetAdapter(&adapter);

	IDXGIFactory* factory = nullptr;
	adapter->GetParent ( __uuidof(IDXGIFactory), (void**)&factory);

	device->Release();
	adapter->Release();

	hr = factory->CreateSwapChain(this->d3dDevice, &sd, &( this->swapChain ) );
	factory->Release();

	switch (hr)
	{
		case DXGI_ERROR_INVALID_CALL:
			return hr;
			break;
		case DXGI_STATUS_OCCLUDED:
			return hr;
			break;
		case E_OUTOFMEMORY:
			return hr;
			break;
		case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
			return hr;
			break;
		case S_OK:
			break;
	}

	ID3D11Texture2D* backBuffer = nullptr;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &(backBuffer));
	if (FAILED(hr))
		return hr;

	hr = this->d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &(this->renderTargetView));
	backBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Создание буфера глубин
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = this->d3dDevice->CreateTexture2D(&descDepth, NULL, &(this->depthStencil));
	if (FAILED(hr)) 
		return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = this->d3dDevice->CreateDepthStencilView(this->depthStencil, &descDSV, &(this->depthStencilView));
	if (FAILED(hr))
		return hr;

	this->immediateContext->OMSetRenderTargets(1, &(this->renderTargetView), this->depthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	this->immediateContext->RSSetViewports(1, &vp);

	return S_OK;
}

VertexShader* GraphicsServer::getVertexShader(int index)
{
	bool isInRange = inRange(index, this->vertexShaders.size());
	return isInRange ? this->vertexShaders[index] : nullptr;
}

VertexShader* GraphicsServer::findVertexShader(const wchar_t* shaderName)
{
	auto shaderIndex = this->getVertexShaderIndexByName(shaderName);
	return this->getVertexShader(shaderIndex);
}

int GraphicsServer::getVertexShaderIndexByName(const wchar_t* shaderName)
{
	int vs = -1;
	const size_t size = this->vertexShaders.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->vertexShaders [i]->isA(shaderName))
		{
			vs = static_cast<int>(i);
			break;
		}
	}
	return vs;
}

PixelShader* GraphicsServer::getPixelShader(int index)
{
	bool isInRange = inRange (index, this->pixelShaders.size ());
	return isInRange ? this->pixelShaders[index] : nullptr;
}

PixelShader* GraphicsServer::findPixelShader(const wchar_t* shaderName)
{
	auto shaderIndex = this->getPixelShaderIndexByName(shaderName);
	return this->getPixelShader(shaderIndex);
}

int GraphicsServer::getPixelShaderIndexByName(const wchar_t* shaderName)
{
	int ps = -1;
	const size_t size = this->pixelShaders.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->pixelShaders [i]->isA(shaderName))
		{
			ps = static_cast<int>(i);
			break;
		}
	}
	return ps;
}

HRESULT GraphicsServer::loadVertexShader(const wchar_t* fileName, const char* mainFunc, const wchar_t* shaderName, const wchar_t* vertexDeclarationName)
{
	// Поиск вершинной декларации
	int declarationIndex = -1;
	const size_t size = this->vertexDeclarations.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->vertexDeclarations[i]->isA(vertexDeclarationName))
		{
			declarationIndex = static_cast< int >(i);
			break;
		}
	}
	if (declarationIndex == -1)
	{
		// Создание нового описания входной раскладки для вершинного конвейера
		VertexDeclaration* vertexDeclaration = new VertexDeclaration(vertexDeclarationName);
		this->vertexDeclarations.push_back(vertexDeclaration);
		declarationIndex = static_cast<int>( this->vertexDeclarations.size()) - 1;
	}
	VertexShader* vertexShader = new VertexShader(shaderName);
	this->vertexShaders.push_back(vertexShader);
	vertexShader->setVertexDeclaration(this->vertexDeclarations[declarationIndex]);
	HRESULT res = vertexShader->load(fileName, mainFunc);
	return res;
}

HRESULT GraphicsServer::loadPixelShader(const wchar_t* fileName, const char* mainFunc, const wchar_t* shaderName)
{
	PixelShader* pixelShader = new PixelShader(shaderName);
	this->pixelShaders.push_back(pixelShader);
	HRESULT res = this->pixelShaders.back()->load(fileName, mainFunc);
	return res;
}

int GraphicsServer::createIndexBuffer(int nIndices, unsigned short* indices)
{
	IndexBuffer* buffer = new IndexBuffer;
	if (buffer->create(nIndices, indices) == S_OK)
	{
		this->indexBuffers.push_back(buffer);
		return static_cast<int>(this->indexBuffers.size()) - 1;
	}
	else
		return -1;
}

int GraphicsServer::createVertexBuffer(const wchar_t* vertexDeclarationName, int nVertices, TopologyType topology)
{
	// Поиск вершинной декларации
	int declarationIndex = -1;
	const size_t size = this->vertexDeclarations.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->vertexDeclarations[i]->isA(vertexDeclarationName))
		{
			declarationIndex = static_cast<int>(i);
			break;
		}
	}
	if (declarationIndex == -1)
	{
		// Создание вершинной декларации, если еще не создана
		VertexDeclaration* vertexDeclaration = new VertexDeclaration(vertexDeclarationName);
		this->vertexDeclarations.push_back (vertexDeclaration);
		declarationIndex = static_cast<int>(this->vertexDeclarations.size()) - 1;
	}
	VertexBuffer* vertexBuffer = new VertexBuffer(this->vertexDeclarations[declarationIndex], nVertices, topology);
	this->vertexBuffers.push_back(vertexBuffer);
	return static_cast<int>(this->vertexBuffers.size()) - 1;
}

void GraphicsServer::setAmbientColor(float red, float green, float blue)
{
	this->ambientColor = XMVectorSet(red, green, blue, 1.0f);
}

void GraphicsServer::setLightColor(float red, float green, float blue)
{
	this->dirLightColor = XMVectorSet(red, green, blue, 1.0f);
}

void GraphicsServer::setLightDirection(float x, float y, float z)
{
	this->dirLightDirection = XMVectorSet(x, y, z, 0.0f);
}

void GraphicsServer::fillPositionInVertexBuffer(int vertexBuffer, int index, float x, float y, float z)
{
	if (inRange(vertexBuffer, this->vertexBuffers.size()))
		this->vertexBuffers[vertexBuffer]->setPosition(index, x, y, z);
}

void GraphicsServer::fillNormalInVertexBuffer(int vertexBuffer, int index, float x, float y, float z)
{
	if (inRange (vertexBuffer, this->vertexBuffers.size()))
		this->vertexBuffers[vertexBuffer]->setNormal(index, x, y, z);
}

void GraphicsServer::fillDiffuseColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha)
{
	if (inRange (vertexBuffer, this->vertexBuffers.size()))
		this->vertexBuffers[vertexBuffer]->setDiffuseColor(index, red, green, blue, alpha);
}

void GraphicsServer::fillSpecularColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha)
{
	if (inRange (vertexBuffer, this->vertexBuffers.size()))
		this->vertexBuffers[vertexBuffer]->setSpecularColor(index, red, green, blue, alpha);
}

void GraphicsServer::fillEmissiveColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha)
{
	if (inRange (vertexBuffer, this->vertexBuffers.size()))
		this->vertexBuffers[vertexBuffer]->setEmissiveColor(index, red, green, blue, alpha);
}

int GraphicsServer::assignVertexBuffer(int index)
{
	return (this->vertexBuffers[index]->create() == S_OK) ? index : -1;
}

void GraphicsServer::draw(int vertexShader, int pixelShader, int indexBuffer, int vertexBuffer)
{
	VertexShader* pVS = this->vertexShaders[vertexShader];
	Camera* camera = this->cameras[this->currentCamera];
	pVS->setConstant(Shader::ConstantType::ProjectionMatrix, camera->getProjectionMatrix());
	pVS->setConstant(Shader::ConstantType::ViewMatrix, camera->getViewMatrix());
	pVS->set(this->immediateContext);

	PixelShader* pPS = this->pixelShaders[pixelShader];
	pPS->setConstant(Shader::ConstantType::AmbientColor, this->ambientColor);
	pPS->setConstant(Shader::ConstantType::DirectionLightColor, this->dirLightColor);
	pPS->setConstant(Shader::ConstantType::DirectionLightDir, this->dirLightDirection);
	pPS->set(this->immediateContext);

	VertexBuffer* pVB = this->vertexBuffers[vertexBuffer];
	pVB->set(this->immediateContext);
	if (indexBuffer != -1)
	{
		IndexBuffer* pIB = this->indexBuffers[indexBuffer];
		pIB->set(this->immediateContext);
		this->immediateContext->DrawIndexed(pIB->getIndexCount(), 0, 0);
	}
	else
		this->immediateContext->Draw(pVB->getVertexCount(), 0);
}

HRESULT GraphicsServer::setCamera(int index)
{
	auto isInRange = inRange(index, this->cameras.size());
	if (isInRange and (this->cameras[index] != nullptr))
	{
		this->currentCamera = index;
		return S_OK;
	}
	return E_FAIL;
}

int GraphicsServer::addCamera()
{
	size_t i;
	const size_t size = this->cameras.size();
	for (i = 0; i < size; ++i)
	{
		if (this->cameras[i] == nullptr)
		{
			this->cameras[i] = new Camera;
			return static_cast<int>(i);
		}
	}
	this->cameras.emplace_back();
	return static_cast<int>(size);
}

HRESULT GraphicsServer::deleteCamera(int index)
{
	auto isInRange = inRange (index, this->cameras.size ());
	if (!isInRange or (index == 0))
		return E_FAIL;
	if (this->cameras[index] != nullptr)
	{
		delete this->cameras[index];
		this->cameras[index] = nullptr;
		if (this->currentCamera == index)
			this->currentCamera = 0;
	}
	return S_OK;
}

void GraphicsServer::addVisualObject(VisualAbstract* visualObject)
{
	int slot = -1;
	const size_t size = this->visualObjects.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->visualObjects[i] == visualObject)
			return;
		if (this->visualObjects[i] == nullptr)
		{
			slot = static_cast<int>(i);
			break;
		}
	}
	if (slot == -1)
	{
		slot = static_cast<int>(this->visualObjects.size());
		this->visualObjects.resize(slot + 1);
	}
	this->visualObjects[slot] = visualObject;
}

HRESULT GraphicsServer::render()
{
	float clearColor [4] = {0.8f, 0.8f, 1.0f, 1.0f};
	this->immediateContext->ClearRenderTargetView(this->renderTargetView, clearColor);
	this->immediateContext->ClearDepthStencilView(this->depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	for (auto& visualObject : this->visualObjects)
		if (visualObject != nullptr)
			visualObject->render();

	this->swapChain->Present(1, 0);
	return S_OK;
}
