#include "..\genApplication.h"
#include "visualPultTabloCommutator.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexBuffer.h"
#include "..\graphics\graphVertexShader.h"
#include "..\graphics\graphPixelShader.h"
#include "..\scb\scbPultTabloAbstractCommutator.h"
#include "..\scb\scbPultTablo.h"

int visualPultTabloCommutator::m_VB = -1;
int visualPultTabloCommutator::m_PlateVB = -1;
int visualPultTabloCommutator::m_VS = -1;
int visualPultTabloCommutator::m_PS = -1;
int visualPultTabloCommutator::m_IB = -1;
int visualPultTabloCommutator::m_PlateIB = -1;

HRESULT visualPultTabloCommutator::InitBuffers ()
{
	graphServer* server = graphServer::Instance ();
	int resource = -1;

	const int n_sector = 24;
	int i;
	float angle;

	int vb = server->CreateVertexBuffer ( L"PN", n_sector * 3 + 16, graphServer::TriangleList );
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

	server->FillPositionInVertexBuffer ( vb, 3 * n_sector, -0.2f, 0.9f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 1, -0.2f, 0.9f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 2, 0.2f, 0.9f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 3, 0.2f, 0.9f, 1.5f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 * n_sector + i, 0.0f, 1.0f, 0.0f );

	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 4, -0.2f, 0.6f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 5, -0.2f, 0.6f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 6, -0.2f, 0.9f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 7, -0.2f, 0.9f, 1.5f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 * n_sector + 4 + i, -1.0f, 0.0f, 0.0f );

	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 8, 0.2f, 0.9f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 9, 0.2f, 0.9f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 10, 0.2f, 0.6f, 0.0f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 11, 0.2f, 0.6f, 1.5f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 * n_sector + 8 + i, 1.0f, 0.0f, 0.0f );

	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 12, -0.2f, 0.9f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 13, -0.2f, 0.6f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 14, 0.2f, 0.9f, 1.5f );
	server->FillPositionInVertexBuffer ( vb, 3 * n_sector + 15, 0.2f, 0.6f, 1.5f );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 * n_sector + 12 + i, 0.0f, 0.0f, 1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualPultTabloCommutator::m_VB = resource;
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
		visualPultTabloCommutator::m_PlateVB = resource;
	else
		return E_FAIL;

	const int num_tris = n_sector - 2;
	const int num_indices = ( n_sector - 2 ) * 3 + n_sector * 6;
	unsigned short indices [num_indices + 24];
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

	for ( i = 0; i < 4; i++ )
	{
		indices [num_indices + 6 * i + 0] = n_sector * 3 + 4 * i + 0;
		indices [num_indices + 6 * i + 1] = n_sector * 3 + 4 * i + 1;
		indices [num_indices + 6 * i + 2] = n_sector * 3 + 4 * i + 3;
		indices [num_indices + 6 * i + 3] = n_sector * 3 + 4 * i + 0;
		indices [num_indices + 6 * i + 4] = n_sector * 3 + 4 * i + 3;
		indices [num_indices + 6 * i + 5] = n_sector * 3 + 4 * i + 2;
	}

	resource = server->CreateIndexBuffer ( num_indices + 24, indices );
	if ( resource != -1 )
		visualPultTabloCommutator::m_IB = resource;
	else
		return E_FAIL;

	unsigned short indices1 [] = { 0, 1, 2, 2, 1, 3 };
	resource = server->CreateIndexBuffer ( 6, indices1 );
	if ( resource != -1 )
		visualPultTabloCommutator::m_PlateIB = resource;
	else
		return E_FAIL;

	resource = server->GetVertexShaderIndex ( L"vs" );
	if ( resource != -1 )
		visualPultTabloCommutator::m_VS = resource;
	else
		return E_FAIL;

	resource = server->GetPixelShaderIndex ( L"ps" );
	if ( resource != -1 )
		visualPultTabloCommutator::m_PS = resource;
	else
		return E_FAIL;

	return S_OK;
}

visualPultTabloCommutator::visualPultTabloCommutator () :
	m_CommutatorLink ( nullptr ),
	m_X ( 0.0f ),
	m_Y ( 0.0f ),
	m_Z ( 0.0f ),
	m_DirX ( 0.0f ),
	m_DirY ( 1.0f ),
	m_DirZ ( 0.0f )
{
}

visualPultTabloCommutator::~visualPultTabloCommutator ()
{
}

HRESULT visualPultTabloCommutator::AssignCommutator ( scbPultTablo* pt, int device )
{
	if ( ( this->m_IsCompleted ) || ( pt == nullptr ) )
		return E_FAIL;

	if ( ( device < 0 ) || ( device >= pt->GetActiveDeviceCount () ) )
		return E_FAIL;

	if ( ( this->m_CommutatorLink = dynamic_cast < scbPultTabloAbstractCommutator* >( pt->GetActiveDevice ( device ) ) ) == nullptr )
		return E_FAIL;

	return this->InitGeometry ();
}

void visualPultTabloCommutator::SetPosition ( float x, float y, float z )
{
	if ( this->m_IsCompleted )
		return;
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

void visualPultTabloCommutator::SetDirection ( float dirX, float dirY, float dirZ )
{
	if ( this->m_IsCompleted )
		return;
	this->m_DirX = dirX;
	this->m_DirY = dirY;
	this->m_DirZ = dirZ;
}

HRESULT visualPultTabloCommutator::InitGeometry ()
{
	switch ( this->m_CommutatorLink->GetColor () )
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
	this->m_VertexBuffers.push_back ( visualPultTabloCommutator::m_VB );
	this->m_IndexBuffers.push_back ( visualPultTabloCommutator::m_IB );
	this->m_VertexShaders.push_back ( visualPultTabloCommutator::m_VS );
	this->m_PixelShaders.push_back ( visualPultTabloCommutator::m_PS );

	this->m_VertexBuffers.push_back ( visualPultTabloCommutator::m_PlateVB );
	this->m_IndexBuffers.push_back ( visualPultTabloCommutator::m_PlateIB );
	this->m_VertexShaders.push_back ( visualPultTabloCommutator::m_VS );
	this->m_PixelShaders.push_back ( visualPultTabloCommutator::m_PS );

	return S_OK;
}

void visualPultTabloCommutator::Render ()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX mSpin;
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX mTranslate;

	mSpin = XMMatrixRotationY ( 30.0f * XM_PI / 180.0f  * this->m_CommutatorLink->GetSwitchPosition ());
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y - 0.8f * this->m_CommutatorLink->GetPressPosition (), this->m_Z );

	graphServer* server = graphServer::Instance ();
	int vs, ps;
	
	vs = this->m_VertexShaders [0];
	ps = this->m_PixelShaders [0];

	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, this->m_DiffuseColor );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, this->m_SpecularColor );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [0], this->m_VertexBuffers [0] );

	mSpin = XMMatrixIdentity ();
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

