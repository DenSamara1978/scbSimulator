#include "..\genApplication.h"
#include "visualPultTabloButton.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexBuffer.h"
#include "..\graphics\graphVertexShader.h"
#include "..\graphics\graphPixelShader.h"
#include "..\scb\scbPultTabloAbstractButton.h"
#include "..\scb\scbPultTablo.h"

int visualPultTabloButton::m_VB = -1;
int visualPultTabloButton::m_PlateVB = -1;
int visualPultTabloButton::m_VS = -1;
int visualPultTabloButton::m_PS = -1;
int visualPultTabloButton::m_IB = -1;
int visualPultTabloButton::m_PlateIB = -1;

HRESULT visualPultTabloButton::InitBuffers ()
{
	graphServer* server = graphServer::Instance ();
	int resource = -1;

	const int n_sector = 24;
	int i;
	float angle;

	int vb = server->CreateVertexBuffer ( L"PN", n_sector * 3, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	for ( i = 0; i < n_sector; i++ )
	{
		angle = 2.0f * XM_PI * i / n_sector;
		server->FillPositionInVertexBuffer ( vb, i, cos ( angle ) * 0.5f, 0.9f, sin ( angle ) * 0.5f );
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 1.0f, 0.0f );
		server->FillPositionInVertexBuffer ( vb, i + n_sector, cos ( angle ) * 0.5f, 0.9f, sin ( angle ) * 0.5f );
		server->FillNormalInVertexBuffer ( vb, i + n_sector, cos ( angle ), 0.0f, sin ( angle ) );
		server->FillPositionInVertexBuffer ( vb, i + 2 * n_sector, cos ( angle ) * 0.5f, -0.1f, sin ( angle ) * 0.5f );
		server->FillNormalInVertexBuffer ( vb, i + 2 * n_sector, cos ( angle ), 0.0f, sin ( angle ) );
	}

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTabloButton::m_VB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 4, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	server->FillPositionInVertexBuffer ( vb, 0, 1.0f, 0.0f, 1.0f );
	server->FillPositionInVertexBuffer ( vb, 1, 1.0f, 0.0f, -1.0f );
	server->FillPositionInVertexBuffer ( vb, 2, -1.0f, 0.0f, 1.0f );
	server->FillPositionInVertexBuffer ( vb, 3, -1.0f, 0.0f, -1.0f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 1.0f, 0.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTabloButton::m_PlateVB = resource;
	else
		return E_FAIL;

	int num_tris = n_sector - 2;
	unsigned short indices [( n_sector - 2 ) * 3 + n_sector * 6];
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
	for ( i = 0; i < n_sector - 1; i++ )
	{
		indices [( n_sector - 2 ) * 3 + i * 6] = 2 * n_sector + i + 1;
		indices [( n_sector - 2 ) * 3 + i * 6 + 1] = 2 * n_sector + i;
		indices [( n_sector - 2 ) * 3 + i * 6 + 2] = n_sector + i + 1;
		indices [( n_sector - 2 ) * 3 + i * 6 + 3] = 2 * n_sector + i;
		indices [( n_sector - 2 ) * 3 + i * 6 + 4] = n_sector + i;
		indices [( n_sector - 2 ) * 3 + i * 6 + 5] = n_sector + i + 1;
	}
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6] = 2 * n_sector;
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6 + 1] = 3 * n_sector - 1;
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6 + 2] = n_sector;
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6 + 3] = 3 * n_sector - 1;
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6 + 4] = 2 * n_sector - 1;
	indices [( n_sector - 2 ) * 3 + ( n_sector - 1 ) * 6 + 5] = n_sector;

	resource = server->CreateIndexBuffer ( num_tris * 3 + n_sector * 6, indices );
	if ( resource != -1 )
		visualPultTabloButton::m_IB = resource;
	else
		return E_FAIL;

	unsigned short indices1 [] = { 0, 1, 2, 2, 1, 3 };
	resource = server->CreateIndexBuffer ( 6, indices1 );
	if ( resource != -1 )
		visualPultTabloButton::m_PlateIB = resource;
	else
		return E_FAIL;

	resource = server->GetVertexShaderIndex ( L"vs" );
	if ( resource != -1 )
		visualPultTabloButton::m_VS = resource;
	else
		return E_FAIL;

	resource = server->GetPixelShaderIndex ( L"ps" );
	if ( resource != -1 )
		visualPultTabloButton::m_PS = resource;
	else
		return E_FAIL;

	return S_OK;
}

visualPultTabloButton::visualPultTabloButton () :
	m_ButtonLink ( nullptr ),
	m_X ( 0.0f ),
	m_Y ( 0.0f ),
	m_Z ( 0.0f ),
	m_DirX ( 0.0f ),
	m_DirY ( 1.0f ),
	m_DirZ ( 0.0f ),
	m_DiffuseColor ( XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f )),
	m_SpecularColor ( XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) )
{
}

visualPultTabloButton::~visualPultTabloButton ()
{
}

HRESULT visualPultTabloButton::AssignButton ( scbPultTablo* pt, int device )
{
	if ( ( this->m_IsCompleted ) || ( pt == nullptr ) )
		return E_FAIL;

	if (( device < 0 ) || ( device >= pt->GetActiveDeviceCount ()))
		return E_FAIL;

	if ( ( this->m_ButtonLink = dynamic_cast < scbPultTabloAbstractButton* >( pt->GetActiveDevice ( device ))) == nullptr )
		return E_FAIL;

	return this->InitGeometry ();
}

void visualPultTabloButton::SetPosition ( float x, float y, float z )
{
	if ( this->m_IsCompleted )
		return;
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

void visualPultTabloButton::SetDirection ( float dirX, float dirY, float dirZ )
{
	if ( this->m_IsCompleted )
		return;
	this->m_DirX = dirX;
	this->m_DirY = dirY;
	this->m_DirZ = dirZ;
}

HRESULT visualPultTabloButton::InitGeometry ()
{
	switch ( this->m_ButtonLink->GetColor () )
	{
	case scbPultTablo::Color::Black:
		this->m_DiffuseColor = XMVectorSet ( 0.2f, 0.2f, 0.2f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 0.3f, 0.3f, 0.3f, 1.0f );
		break;
	case scbPultTablo::Color::Red:
		this->m_DiffuseColor = XMVectorSet ( 0.9f, 0.0f, 0.0f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 1.0f, 0.1f, 0.1f, 1.0f );
		break;
	case scbPultTablo::Color::White:
		this->m_DiffuseColor = XMVectorSet ( 0.9f, 0.9f, 0.9f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 1.0f, 1.0f, 1.0f, 1.0f );
		break;
	case scbPultTablo::Color::Blue:
		this->m_DiffuseColor = XMVectorSet ( 0.2f, 0.2f, 0.9f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 0.3f, 0.3f, 1.0f, 1.0f );
		break;
	case scbPultTablo::Color::Yellow:
		this->m_DiffuseColor = XMVectorSet ( 0.9f, 0.9f, 0.2f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 1.0f, 1.0f, 0.3f, 1.0f );
		break;
	case scbPultTablo::Color::Green:
		this->m_DiffuseColor = XMVectorSet ( 0.2f, 0.9f, 0.2f, 1.0f );
		this->m_SpecularColor = XMVectorSet ( 0.3f, 1.0f, 0.3f, 1.0f );
		break;
	}
	this->m_VertexBuffers.push_back ( visualPultTabloButton::m_VB );
	this->m_IndexBuffers.push_back ( visualPultTabloButton::m_IB );
	this->m_VertexShaders.push_back ( visualPultTabloButton::m_VS );
	this->m_PixelShaders.push_back ( visualPultTabloButton::m_PS );

	this->m_VertexBuffers.push_back ( visualPultTabloButton::m_PlateVB );
	this->m_IndexBuffers.push_back ( visualPultTabloButton::m_PlateIB );
	this->m_VertexShaders.push_back ( visualPultTabloButton::m_VS );
	this->m_PixelShaders.push_back ( visualPultTabloButton::m_PS );

	return S_OK;
}

void visualPultTabloButton::Render ()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX mSpin = XMMatrixIdentity ();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX mTranslate;

	graphServer* server = graphServer::Instance ();

	int vs, ps;

	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y - 0.8f * this->m_ButtonLink->GetPressPosition (), this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [0];
	ps = this->m_PixelShaders [0];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, this->m_DiffuseColor );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, this->m_SpecularColor );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [0], this->m_VertexBuffers [0] );

	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [1];
	ps = this->m_PixelShaders [1];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.6f, 0.6f, 0.9f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.8f, 0.8f, 1.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [1], this->m_VertexBuffers [1] );
}

