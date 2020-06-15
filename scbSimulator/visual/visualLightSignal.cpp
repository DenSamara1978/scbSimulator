#include "..\genApplication.h"
#include "visualLightSignal.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexBuffer.h"
#include "..\graphics\graphVertexShader.h"
#include "..\graphics\graphPixelShader.h"
#include "..\scb\scbLightSignal.h"
#include "..\scb\scbLightSignalLamp.h"

int visualLightSignal::m_GenVB = -1;
int visualLightSignal::m_GenVS = -1;
int visualLightSignal::m_GenPS = -1;
int visualLightSignal::m_LensVB = -1;
int visualLightSignal::m_LensVS = -1;
int visualLightSignal::m_LensPS = -1;
int visualLightSignal::m_IB = -1;

HRESULT visualLightSignal::InitBuffers ()
{
	graphServer* server = graphServer::Instance ();
	int resource = -1;

	const int n_sector = 24;
	int i;
	float angle;

	int vb = server->CreateVertexBuffer ( L"PN", n_sector, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	for ( i = 0; i < n_sector; i++ )
	{
		angle = 2.0f * XM_PI * i / n_sector;
		server->FillPositionInVertexBuffer ( vb, i, cos ( angle ) * 0.98f, sin ( angle ) * 0.98f, 0.01f );
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 0.0f, -1.0f );
	}

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualLightSignal::m_GenVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", n_sector, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	for ( i = 0; i < n_sector; i++ )
	{
		angle = 2.0f * XM_PI * i / n_sector;
		server->FillPositionInVertexBuffer ( vb, i, cos ( angle ) * 0.85f, sin ( angle ) * 0.85f, 0.0f );
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 0.0f, -1.0f );
	}

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualLightSignal::m_LensVB = resource;
	else
		return E_FAIL;

	int num_tris = n_sector - 2;
	unsigned short indices [( n_sector - 2 ) * 3];
	for ( i = 0; i < n_sector - 2; i++ )
	{
		if ( i < n_sector / 2 - 1 )
		{
			indices [i * 3] = i + 1;
			indices [i * 3 + 1] = i;
			indices [i * 3 + 2] = n_sector - 1 - i;
		}
		else
		{
			indices [i * 3] = i + 2;
			indices [i * 3 + 1] = i + 1;
			indices [i * 3 + 2] = n_sector - 2 - i;
		}
	}

	resource = server->CreateIndexBuffer ( num_tris * 3, indices );
	if ( resource != -1 )
		visualLightSignal::m_IB = resource;
	else
		return E_FAIL;

	resource = server->GetVertexShaderIndex ( L"vs" );
	if ( resource != -1 )
	{
		visualLightSignal::m_GenVS = resource;
		visualLightSignal::m_LensVS = resource;
	}
	else
		return E_FAIL;

	resource = server->GetPixelShaderIndex ( L"ps" );
	if ( resource != -1 )
	{
		visualLightSignal::m_GenPS = resource;
		visualLightSignal::m_LensPS = resource;
	}
	else
		return E_FAIL;

	return S_OK;
}

visualLightSignal::visualLightSignal () :
	m_X ( 0.0f ),
	m_Y ( 0.0f ),
	m_Z ( 0.0f ),
	m_DirX ( 0.0f ),
	m_DirY ( 0.0f ),
	m_DirZ ( 1.0f )
{
}

visualLightSignal::~visualLightSignal ()
{
}

HRESULT visualLightSignal::AssignScbLightSignal ( scbLightSignal* ls )
{
	if (( this->m_IsCompleted ) || ( ls == nullptr ))
		return E_FAIL;

	this->m_Lamps.clear ();
	const auto count = ls->GetDeviceCount ();
	for ( int i = 0; i < count; i++ )
	{
		LampDesc desc;
		desc.Link = dynamic_cast < scbLightSignalLamp* > ( ls->GetDevice ( i ) );
		switch ( desc.Link->GetColor () )
		{
		case scbLightSignalLamp::LampColor::Red:
			desc.Color = DirectX::XMVectorSet ( 1.0f, 0.0f, 0.0f, 1.0f );
			break;
		case scbLightSignalLamp::LampColor::Blue:
			desc.Color = DirectX::XMVectorSet ( 0.0f, 0.0f, 1.0f, 1.0f );
			break;
		case scbLightSignalLamp::LampColor::White:
			desc.Color = DirectX::XMVectorSet ( 1.0f, 1.0f, 1.0f, 1.0f );
			break;
		case scbLightSignalLamp::LampColor::Yellow:
			desc.Color = DirectX::XMVectorSet ( 1.0f, 1.0f, 0.0f, 1.0f );
			break;
		case scbLightSignalLamp::LampColor::Green:
			desc.Color = DirectX::XMVectorSet ( 0.0f, 1.0f, 0.0f, 1.0f );
			break;
		case scbLightSignalLamp::LampColor::Milk:
			desc.Color = DirectX::XMVectorSet ( 1.0f, 1.0f, 0.5f, 1.0f );
			break;
		}
		this->m_Lamps.push_back ( desc );
	}

	return this->InitGeometry ();
}

void visualLightSignal::SetPosition ( float x, float y, float z )
{
	if ( this->m_IsCompleted )
		return;
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

void visualLightSignal::SetDirection ( float dirX, float dirY, float dirZ )
{
	if ( this->m_IsCompleted )
		return;
	this->m_DirX = dirX;
	this->m_DirY = dirY;
	this->m_DirZ = dirZ;
}

HRESULT visualLightSignal::InitGeometry ()
{
	const auto count = this->m_Lamps.size ();
	for ( int i = 0; i < count; i++ )
	{
		this->m_VertexBuffers.push_back ( visualLightSignal::m_GenVB );
		this->m_IndexBuffers.push_back ( visualLightSignal::m_IB );
		this->m_VertexShaders.push_back ( visualLightSignal::m_GenVS );
		this->m_PixelShaders.push_back ( visualLightSignal::m_GenPS );

		this->m_VertexBuffers.push_back ( visualLightSignal::m_LensVB );
		this->m_IndexBuffers.push_back ( visualLightSignal::m_IB );
		this->m_VertexShaders.push_back ( visualLightSignal::m_LensVS );
		this->m_PixelShaders.push_back ( visualLightSignal::m_LensPS );
	}

	return S_OK;
}

void visualLightSignal::Render ()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX mSpin = XMMatrixIdentity ();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX mTranslate;

	graphServer* server = graphServer::Instance ();

	int vs, ps;

	const auto count = this->m_Lamps.size ();
	for ( int i = 0; i < count; i++ )
	{
		mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y - 1.0f + 2.0f * ( count - i ), this->m_Z );
		this->m_WorldMatrix = mSpin * mTranslate;

		vs = this->m_VertexShaders [i * 2];
		ps = this->m_PixelShaders [i * 2];

		server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

		server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.1f, 0.1f, 0.1f, 1.0f ) );
		server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.2f, 0.2f, 0.2f, 1.0f ) );
		server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

		server->Draw ( vs, ps, this->m_IndexBuffers [i * 2], this->m_VertexBuffers [i * 2] );

		vs = this->m_VertexShaders [i * 2 + 1];
		ps = this->m_PixelShaders [i * 2 + 1];

		server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

		server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.1f, 0.1f, 0.1f, 1.0f ) );
		server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.2f, 0.2f, 0.2f, 1.0f ) );
		if ( this->m_Lamps [i].Link != nullptr )
			server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorLerp ( DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ), this->m_Lamps [i].Color, this->m_Lamps [i].Link->GetBright () ));
		else
			server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

		server->Draw ( vs, ps, this->m_IndexBuffers [i * 2 + 1], this->m_VertexBuffers [i * 2 + 1] );
	}
}

