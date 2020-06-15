#include "..\genApplication.h"
#include "visualPultTablo.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexShader.h"
#include "..\graphics\graphPixelShader.h"
#include "..\scb\scbPultTablo.h"
#include "..\scb\scbPultTabloLampGroup.h"

int visualPultTablo::m_LedCellVB = -1;
int visualPultTablo::m_LedCellIB = -1;
int visualPultTablo::m_LedRoundVB = -1;
int visualPultTablo::m_LedRoundIB = -1;
int visualPultTablo::m_LedVS = -1;
int visualPultTablo::m_LedPS = -1;
int visualPultTablo::m_PlateVB = -1;
int visualPultTablo::m_PlateIB = -1;
int visualPultTablo::m_PlateVS = -1;
int visualPultTablo::m_PlatePS = -1;

HRESULT visualPultTablo::InitBuffers ()
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
		server->FillPositionInVertexBuffer ( vb, i, cos ( angle ) * 0.3f, sin ( angle ) * 0.3f, -0.01f );
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 0.0f, -1.0f );
	}

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTablo::m_LedRoundVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 4, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	server->FillPositionInVertexBuffer ( vb, 0, -0.5f, -0.2f, -0.01f );
	server->FillPositionInVertexBuffer ( vb, 1, -0.5f, 0.2f, -0.01f );
	server->FillPositionInVertexBuffer ( vb, 2, 0.5f, -0.2f, -0.01f );
	server->FillPositionInVertexBuffer ( vb, 3, 0.5f, 0.2f, -0.01f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 0.0f, -1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTablo::m_LedCellVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 4, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	server->FillPositionInVertexBuffer ( vb, 0, -6.0f, -6.0f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 1, -6.0f, 6.0f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 2, 6.0f, -6.0f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3, 6.0f, 6.0f, 0.0f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 0.0f, -1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTablo::m_PlateVB = resource;
	else
		return E_FAIL;

	const int num_tris = n_sector - 2;
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
		visualPultTablo::m_LedRoundIB = resource;
	else
		return E_FAIL;

	unsigned short indices1 [] = { 0, 1, 3, 0, 3, 2 };
	resource = server->CreateIndexBuffer ( 6, indices1 );
	if ( resource != -1 )
	{
		visualPultTablo::m_PlateIB = resource;
		visualPultTablo::m_LedCellIB = resource;
	}
	else
		return E_FAIL;

	resource = server->GetVertexShaderIndex ( L"vs" );
	if ( resource != -1 )
	{
		visualPultTablo::m_LedVS = resource;
		visualPultTablo::m_PlateVS = resource;
	}
	else
		return E_FAIL;

	resource = server->GetPixelShaderIndex ( L"ps" );
	if ( resource != -1 )
	{
		visualPultTablo::m_LedPS = resource;
		visualPultTablo::m_PlatePS = resource;
	}
	else
		return E_FAIL;

	return S_OK;
}

visualPultTablo::visualPultTablo () :
	m_X ( 0.0f ),
	m_Y ( 0.0f ),
	m_Z ( 0.0f ),
	m_DirX ( 0.0f ),
	m_DirY ( 1.0f ),
	m_DirZ ( 0.0f ),
	m_PultTablo ( nullptr )
{
}

visualPultTablo::~visualPultTablo ()
{
}

HRESULT visualPultTablo::AssignPultTablo ( scbPultTablo* pt )
{
	if ( ( this->m_IsCompleted ) || ( pt == nullptr ) )
		return E_FAIL;

	this->m_PultTablo = pt;

	return this->InitGeometry ();
}

void visualPultTablo::AddCellLamp ( int group, int bit, float x, float y, int angle, scbPultTablo::Color color )
{
	if ( ( group < 0 ) || ( group >= this->m_PultTablo->GetLampGroupCount () )) return;

	visualPultTablo::LampInfo info;
	info.Group = group;
	info.Bit = bit;
	info.X = x;
	info.Y = y;
	info.Type = 0;
	info.Angle = ( XM_PI / 180.f ) * angle;
	switch ( color )
	{
	case scbPultTablo::Color::Black:
		info.Color = XMVectorSet ( 0.2f, 0.2f, 0.2f, 1.0f );
		break;
	case scbPultTablo::Color::Red:
		info.Color = XMVectorSet ( 0.9f, 0.0f, 0.0f, 1.0f );
		break;
	case scbPultTablo::Color::White:
		info.Color = XMVectorSet ( 0.9f, 0.9f, 0.9f, 1.0f );
		break;
	case scbPultTablo::Color::Blue:
		info.Color = XMVectorSet ( 0.2f, 0.2f, 0.9f, 1.0f );
		break;
	case scbPultTablo::Color::Yellow:
		info.Color = XMVectorSet ( 0.9f, 0.9f, 0.2f, 1.0f );
		break;
	case scbPultTablo::Color::Green:
		info.Color = XMVectorSet ( 0.2f, 0.9f, 0.2f, 1.0f );
		break;
	}

	this->m_Lamps.push_back ( info );
}

void visualPultTablo::AddRoundLamp ( int group, int bit, float x, float y, scbPultTablo::Color color )
{
	if ( ( group < 0 ) || ( group >= this->m_PultTablo->GetLampGroupCount () )) return;

	visualPultTablo::LampInfo info;
	info.Group = group;
	info.Bit = bit;
	info.X = x;
	info.Y = y;
	info.Type = 1;
	info.Angle = 0.0f;
	switch ( color )
	{
	case scbPultTablo::Color::Black:
		info.Color = XMVectorSet ( 0.2f, 0.2f, 0.2f, 1.0f );
		break;
	case scbPultTablo::Color::Red:
		info.Color = XMVectorSet ( 0.9f, 0.0f, 0.0f, 1.0f );
		break;
	case scbPultTablo::Color::White:
		info.Color = XMVectorSet ( 0.9f, 0.9f, 0.9f, 1.0f );
		break;
	case scbPultTablo::Color::Blue:
		info.Color = XMVectorSet ( 0.2f, 0.2f, 0.9f, 1.0f );
		break;
	case scbPultTablo::Color::Yellow:
		info.Color = XMVectorSet ( 0.9f, 0.9f, 0.2f, 1.0f );
		break;
	case scbPultTablo::Color::Green:
		info.Color = XMVectorSet ( 0.2f, 0.9f, 0.2f, 1.0f );
		break;
	}

	this->m_Lamps.push_back ( info );
}

void visualPultTablo::SetPosition ( float x, float y, float z )
{
	if ( this->m_IsCompleted )
		return;
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

void visualPultTablo::SetDirection ( float dirX, float dirY, float dirZ )
{
	if ( this->m_IsCompleted )
		return;
	this->m_DirX = dirX;
	this->m_DirY = dirY;
	this->m_DirZ = dirZ;
}

HRESULT visualPultTablo::InitGeometry ()
{
	this->m_VertexBuffers.push_back ( visualPultTablo::m_LedCellVB );
	this->m_IndexBuffers.push_back ( visualPultTablo::m_LedCellIB );
	this->m_VertexShaders.push_back ( visualPultTablo::m_LedVS );
	this->m_PixelShaders.push_back ( visualPultTablo::m_LedPS );

	this->m_VertexBuffers.push_back ( visualPultTablo::m_LedRoundVB );
	this->m_IndexBuffers.push_back ( visualPultTablo::m_LedRoundIB );
	this->m_VertexShaders.push_back ( visualPultTablo::m_LedVS );
	this->m_PixelShaders.push_back ( visualPultTablo::m_LedPS );

	this->m_VertexBuffers.push_back ( visualPultTablo::m_PlateVB );
	this->m_IndexBuffers.push_back ( visualPultTablo::m_PlateIB );
	this->m_VertexShaders.push_back ( visualPultTablo::m_PlateVS );
	this->m_PixelShaders.push_back ( visualPultTablo::m_PlatePS );

	return S_OK;
}

void visualPultTablo::Render ()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX mSpin;
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX mTranslate;


	graphServer* server = graphServer::Instance ();
	int vs, ps;

	for ( const auto& info : this->m_Lamps )
	{
		vs = this->m_VertexShaders [info.Type];
		ps = this->m_PixelShaders [info.Type];

		mSpin = XMMatrixRotationZ ( info.Angle );
		mTranslate = XMMatrixTranslation ( info.X + this->m_X, info.Y + this->m_Y, +this->m_Z );
		this->m_WorldMatrix = mSpin * mTranslate;

		server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );
		server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.1f, 0.1f, 0.1f, 1.0f ) );

		server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.2f, 0.2f, 0.2f, 1.0f ) );

		if ( this->m_PultTablo->GetLampGroup ( info.Group )->GetLampStatus ( info.Bit ) )
			server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, info.Color );
		else
			server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

		server->Draw ( vs, ps, this->m_IndexBuffers [info.Type], this->m_VertexBuffers [info.Type] );
	}

	mSpin = XMMatrixIdentity ();
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [2];
	ps = this->m_PixelShaders [2];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.6f, 0.6f, 0.9f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.8f, 0.8f, 1.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [2], this->m_VertexBuffers [2] );
}
