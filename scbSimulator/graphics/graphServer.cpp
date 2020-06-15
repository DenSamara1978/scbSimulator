#include <dxgi.h>
#include "graphServer.h"
#include "graphVertexShader.h"
#include "graphPixelShader.h"
#include "graphVertexBuffer.h"
#include "graphIndexBuffer.h"
#include "graphVertexDeclaration.h"
#include "graphCamera.h"
#include "..\genApplication.h"
#include "..\stdafx.h"

graphServer* graphServer::m_Instance = nullptr;

graphServer::graphServer () :
	m_DriverType ( D3D_DRIVER_TYPE_HARDWARE ),
	m_FeatureLevel ( D3D_FEATURE_LEVEL_11_0 ),
	m_D3dDevice ( nullptr ),
	m_ImmediateContext ( nullptr ),
	m_SwapChain ( nullptr ),
	m_RenderTargetView ( nullptr ),
	m_DepthStencil ( nullptr ),
	m_DepthStencilView ( nullptr ),
	m_CurrentCamera ( 0 )
{
	graphServer::m_Instance = this;
	graphCamera* pCamera = new graphCamera;
	this->m_Cameras.push_back ( pCamera );
}

graphServer::~graphServer ()
{
	for ( auto& ptr : this->m_VertexDeclarations )
	{
		delete ptr;
		ptr = nullptr;
	}
	for ( auto& ptr : this->m_VertexShaders )
	{
		delete ptr;
		ptr = nullptr;
	}
	for ( auto& ptr : this->m_PixelShaders )
	{
		delete ptr;
		ptr = nullptr;
	}
	for ( auto& ptr : this->m_VertexBuffers )
	{
		delete ptr;
		ptr = nullptr;
	}
	for ( auto& ptr : this->m_IndexBuffers )
	{
		delete ptr;
		ptr = nullptr;
	}
	for ( auto& ptr : this->m_Cameras )
	{
		delete ptr;
		ptr = nullptr;
	}
	this->CleanupDevice ();
	graphServer::m_Instance = nullptr;
}

void graphServer::CleanupDevice ()
{
	if ( this->m_ImmediateContext )
		this->m_ImmediateContext->ClearState ();

	SafeRelease ( &( this->m_DepthStencil ) );
	SafeRelease ( &( this->m_DepthStencilView ) );
	SafeRelease ( &( this->m_RenderTargetView ) );
	SafeRelease ( &( this->m_SwapChain ) );
	SafeRelease ( &( this->m_ImmediateContext ) );
	SafeRelease ( &( this->m_D3dDevice ) );
}

HRESULT graphServer::InitDevice ()
{
	HRESULT hr = S_OK;
	RECT rc;
	const HWND hwnd = genApplication::Instance ()->GetHWND ();
	GetClientRect ( hwnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT createDeviceFlags = 0;
	D3D_DRIVER_TYPE driverTypes [] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE ( driverTypes );
	D3D_FEATURE_LEVEL featureLevels [] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE ( featureLevels );
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory ( &sd, sizeof ( sd ) );
	sd.BufferCount = 2;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 75;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	for ( unsigned int i = 0; i < numDriverTypes; i++ )
	{
		this->m_DriverType = driverTypes [i];
//		hr = D3D11CreateDeviceAndSwapChain ( nullptr, this->m_DriverType, 0, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &sd, &( this->m_SwapChain ), &( this->m_D3dDevice ), &( this->m_FeatureLevel ), &( this->m_ImmediateContext ) );
		hr = D3D11CreateDevice ( nullptr, this->m_DriverType, 0, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &( this->m_D3dDevice ), &( this->m_FeatureLevel ), &( this->m_ImmediateContext ) );
		if ( SUCCEEDED ( hr ) ) break;
	}
	if ( FAILED ( hr ) ) return hr;

	IDXGIDevice* pDevice = nullptr;
	hr = this->m_D3dDevice->QueryInterface ( __uuidof ( IDXGIDevice ), ( void** ) &pDevice );

	IDXGIAdapter* pAdapter = nullptr;
	hr = pDevice->GetAdapter ( &pAdapter );

	IDXGIFactory* pFactory = nullptr;
	pAdapter->GetParent ( __uuidof ( IDXGIFactory ), ( void** ) &pFactory );

	pDevice->Release ();
	pAdapter->Release ();

	hr = pFactory->CreateSwapChain ( this->m_D3dDevice, &sd, &( this->m_SwapChain ) );
	pFactory->Release ();

	switch ( hr )
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

	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = this->m_SwapChain->GetBuffer ( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* ) &( pBackBuffer ) );
	if ( FAILED ( hr ) ) return hr;

	hr = this->m_D3dDevice->CreateRenderTargetView ( pBackBuffer, nullptr, &( this->m_RenderTargetView ) );
	pBackBuffer->Release ();
	if ( FAILED ( hr ) ) return hr;

	// Создание буфера глубин
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory ( &descDepth, sizeof ( descDepth ) );
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
	hr = this->m_D3dDevice->CreateTexture2D ( &descDepth, NULL, &( this->m_DepthStencil ) );
	if ( FAILED ( hr ) ) return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory ( &descDSV, sizeof ( descDSV ) );
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = this->m_D3dDevice->CreateDepthStencilView ( this->m_DepthStencil, &descDSV, &( this->m_DepthStencilView ) );
	if ( FAILED ( hr ) ) return hr;

	this->m_ImmediateContext->OMSetRenderTargets ( 1, &( this->m_RenderTargetView ), this->m_DepthStencilView );

	D3D11_VIEWPORT vp;
	vp.Width = ( FLOAT ) width;
	vp.Height = ( FLOAT ) height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	this->m_ImmediateContext->RSSetViewports ( 1, &vp );

	return S_OK;
}

graphVertexShader* graphServer::GetVertexShader ( int index )
{
	return (( index < 0 ) || ( index >= static_cast < int> ( this->m_VertexShaders.size ()))) ? nullptr : this->m_VertexShaders [index];
}

int graphServer::GetVertexShaderIndex ( const wchar_t* shader_name )
{
	int vs = -1;
	const size_t size = this->m_VertexShaders.size ();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( this->m_VertexShaders [i]->IsA ( shader_name ) )
		{
			vs = static_cast<int> ( i );
			break;
		}
	}
	return vs;
}

graphPixelShader* graphServer::GetPixelShader ( int index )
{
	return ( ( index < 0 ) || ( index >= static_cast < int> ( this->m_PixelShaders.size () ) ) ) ? nullptr : this->m_PixelShaders [index];
}


int graphServer::GetPixelShaderIndex ( const wchar_t* shader_name )
{
	int ps = -1;
	const size_t size = this->m_PixelShaders.size ();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( this->m_PixelShaders [i]->IsA ( shader_name ) )
		{
			ps = static_cast< int > ( i );
			break;
		}
	}
	return ps;
}

HRESULT graphServer::LoadVertexShader ( const wchar_t* filename, const char* mainFunc, const wchar_t* name, const wchar_t* vDecl )
{
	// Поиск вершинной декларации
	int decl = -1;
	const size_t size = this->m_VertexDeclarations.size ();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( this->m_VertexDeclarations [i]->IsA ( vDecl ) )
		{
			decl = static_cast< int > ( i );
			break;
		}
	}
	if ( decl == -1 )
	{
		// Создание нового описания входной раскладки для вершинного конвейера
		graphVertexDeclaration* pVDecl = new graphVertexDeclaration ( vDecl );
		this->m_VertexDeclarations.push_back ( pVDecl );
		decl = static_cast<int> ( this->m_VertexDeclarations.size ()) - 1;
	}
	graphVertexShader* pVS = new graphVertexShader ( name );
	pVS->SetVertexDeclaration ( this->m_VertexDeclarations [decl] );
	HRESULT res = pVS->Load ( filename, mainFunc );
	this->m_VertexShaders.push_back ( pVS );
	return res;
}

HRESULT graphServer::LoadPixelShader ( const wchar_t* filename, const char* mainFunc, const wchar_t* name )
{
	graphPixelShader* pPS = new graphPixelShader ( name );
	HRESULT res = pPS->Load ( filename, mainFunc );
	this->m_PixelShaders.push_back ( pPS );
	return res;
}

int graphServer::CreateIndexBuffer ( int num_indices, unsigned short* indices )
{
	graphIndexBuffer* pBuffer = new graphIndexBuffer;
	if ( pBuffer->Create ( num_indices, indices ) == S_OK )
	{
		this->m_IndexBuffers.push_back ( pBuffer );
		return static_cast<int> ( this->m_IndexBuffers.size ()) - 1;
	}
	else
		return -1;
}

int graphServer::CreateVertexBuffer ( const wchar_t* vDecl, int vCount, TopologyType topology )
{
	// Поиск вершинной декларации
	int decl = -1;
	const size_t size = this->m_VertexDeclarations.size ();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( this->m_VertexDeclarations [i]->IsA ( vDecl ) )
		{
			decl = static_cast< int > ( i );
			break;
		}
	}
	if ( decl == -1 )
	{
		// Создание вершинной декларации, если еще не создана
		this->m_VertexDeclarations.push_back ( new graphVertexDeclaration ( vDecl ) );
	}
	graphVertexBuffer* pBuffer = new graphVertexBuffer ( this->m_VertexDeclarations.at ( decl ), vCount, topology );
	this->m_VertexBuffers.push_back ( pBuffer );
	return static_cast<int> ( this->m_VertexBuffers.size ()) - 1;
}

void graphServer::SetAmbientColor ( float r, float g, float b )
{
	this->m_AmbientColor = XMVectorSet ( r, g, b, 1.0f );
}

void graphServer::SetLightColor ( float r, float g, float b )
{
	this->m_DirLightColor = XMVectorSet ( r, g, b, 1.0f );
}

void graphServer::SetLightDirection ( float x, float y, float z )
{
	this->m_DirLightDirection = XMVectorSet ( x, y, z, 0.0f );
}

void graphServer::FillPositionInVertexBuffer ( int vb, int index, float x, float y, float z )
{
	if (( vb < 0 ) || ( vb >= static_cast < int> ( this->m_VertexBuffers.size ()))) return;

	this->m_VertexBuffers [vb]->SetPosition ( index, x, y, z );
}

void graphServer::FillNormalInVertexBuffer ( int vb, int index, float x, float y, float z )
{
	if ( ( vb < 0 ) || ( vb >= static_cast < int> ( this->m_VertexBuffers.size () ) ) ) return;

	this->m_VertexBuffers [vb]->SetNormal ( index, x, y, z );
}

void graphServer::FillDiffuseColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a )
{
	if ( ( vb < 0 ) || ( vb >= static_cast < int> ( this->m_VertexBuffers.size () ) )) return;

	this->m_VertexBuffers [vb]->SetDiffuseColor ( index, r, g, b, a );
}

void graphServer::FillSpecularColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a )
{
	if ( ( vb < 0 ) || ( vb >= static_cast < int> ( this->m_VertexBuffers.size () ) ) ) return;

	this->m_VertexBuffers [vb]->SetSpecularColor ( index, r, g, b, a );
}

void graphServer::FillEmissiveColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a )
{
	if ( ( vb < 0 ) || ( vb >= static_cast < int> ( this->m_VertexBuffers.size () ) ) ) return;

	this->m_VertexBuffers [vb]->SetEmissiveColor ( index, r, g, b, a );
}

int graphServer::AssignVertexBuffer ( int index )
{
	return ( this->m_VertexBuffers [index]->Create () == S_OK ) ? index : -1;
}

void graphServer::Draw ( int vs, int ps, int ib, int vb )
{
	graphVertexShader* pVS = this->m_VertexShaders [vs];
	pVS->SetConstant ( graphShader::ProjectionMatrix, this->m_Cameras [this->m_CurrentCamera]->GetProjectionMatrix () );
	pVS->SetConstant ( graphShader::ViewMatrix, this->m_Cameras [this->m_CurrentCamera]->GetViewMatrix () );
	pVS->Set ( this->m_ImmediateContext );

	graphPixelShader* pPS = this->m_PixelShaders [ps];
	pPS->SetConstant ( graphShader::AmbientColor, this->m_AmbientColor );
	pPS->SetConstant ( graphShader::DirectionLightColor, this->m_DirLightColor );
	pPS->SetConstant ( graphShader::DirectionLightDir, this->m_DirLightDirection );
	pPS->Set ( this->m_ImmediateContext );

	graphVertexBuffer* pVB = this->m_VertexBuffers [vb];
	pVB->Set ( this->m_ImmediateContext );
	if ( ib != -1 )
	{
		graphIndexBuffer* pIB = this->m_IndexBuffers [ib];
		pIB->Set ( this->m_ImmediateContext );
		this->m_ImmediateContext->DrawIndexed ( pIB->GetIndexCount (), 0, 0 );
	}
	else
		this->m_ImmediateContext->Draw ( pVB->GetVertexCount (), 0 );
}

HRESULT graphServer::SetCamera ( int index )
{
	if (( index < 0 ) || ( index >= static_cast < int > ( this->m_Cameras.size ()))) return E_FAIL;
	if ( this->m_Cameras [index] == nullptr ) return E_FAIL;
	this->m_CurrentCamera = index;
	return S_OK;
}

int graphServer::AddCamera ()
{
	size_t i;
	const size_t size = this->m_Cameras.size ();
	for ( i = 0; i < size; i++ )
	{
		if ( this->m_Cameras [i] == nullptr )
		{
			this->m_Cameras [i] = new graphCamera;
			return static_cast< int > ( i );
		}
	}
	this->m_Cameras.push_back ( new graphCamera );
	return static_cast<int> ( size );
}

HRESULT graphServer::DeleteCamera ( int index )
{
	if (( index >= static_cast < int > ( this->m_Cameras.size ())) || ( index <= 0 )) return E_FAIL;
	if ( this->m_Cameras [index] != nullptr )
	{
		delete this->m_Cameras [index];
		this->m_Cameras [index] = nullptr;
		if ( this->m_CurrentCamera == index )
			this->m_CurrentCamera = 0;
	}
	return S_OK;
}

void graphServer::AddVisualObject ( visualAbstract* visualObject )
{
	int slot = -1;
	const size_t size = this->m_VisualObjects.size ();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( this->m_VisualObjects [i] == visualObject )
			return;
		if ( this->m_VisualObjects [i] == nullptr )
		{
			slot = static_cast< int > ( i );
			break;
		}
	}
	if ( slot == -1 )
	{
		slot = static_cast<int> ( this->m_VisualObjects.size ());
		this->m_VisualObjects.resize ( slot + 1 );
	}
	this->m_VisualObjects [slot] = visualObject;
}

HRESULT graphServer::Render ()
{
	float clearColor [4] = { 0.8f, 0.8f, 1.0f, 1.0f }; // красный, зеленый, синий, альфа-канал
	this->m_ImmediateContext->ClearRenderTargetView ( this->m_RenderTargetView, clearColor );
	this->m_ImmediateContext->ClearDepthStencilView ( this->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	for ( auto& ptr : this->m_VisualObjects )
		if ( ptr )
			ptr->Render ();

	this->m_SwapChain->Present ( 1, 0 );

	return S_OK;
}
