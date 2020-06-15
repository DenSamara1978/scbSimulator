#include "..\genApplication.h"
#include "visualMotorDrive.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexBuffer.h"
#include "..\graphics\graphVertexShader.h"
#include "..\graphics\graphPixelShader.h"
#include "..\scb\scbMotorDrive.h"
#include "..\scb\scbMotorDriveDevice.h"

int visualMotorDrive::m_AutoSwitchVB = -1;
int visualMotorDrive::m_AutoSwitchIB = -1;
int visualMotorDrive::m_AutoSwitchVS = -1;
int visualMotorDrive::m_AutoSwitchPS = -1;

int visualMotorDrive::m_GateVB = -1;
int visualMotorDrive::m_GateIB = -1;
int visualMotorDrive::m_GateVS = -1;
int visualMotorDrive::m_GatePS = -1;

int visualMotorDrive::m_BaseVB = -1;
int visualMotorDrive::m_BaseIB = -1;
int visualMotorDrive::m_BaseVS = -1;
int visualMotorDrive::m_BasePS = -1;

int visualMotorDrive::m_LeftWedgeVB = -1;
int visualMotorDrive::m_LeftWedgeIB = -1;
int visualMotorDrive::m_LeftWedgeVS = -1;
int visualMotorDrive::m_LeftWedgePS = -1;

int visualMotorDrive::m_RightWedgeVB = -1;
int visualMotorDrive::m_RightWedgeIB = -1;
int visualMotorDrive::m_RightWedgeVS = -1;
int visualMotorDrive::m_RightWedgePS = -1;

int visualMotorDrive::m_FlapVB = -1;
int visualMotorDrive::m_FlapIB = -1;
int visualMotorDrive::m_FlapVS = -1;
int visualMotorDrive::m_FlapPS = -1;

int visualMotorDrive::m_MotorVB = -1;
int visualMotorDrive::m_MotorIB = -1;
int visualMotorDrive::m_MotorVS = -1;
int visualMotorDrive::m_MotorPS = -1;

int visualMotorDrive::m_ControlLineVB = -1;
int visualMotorDrive::m_ControlLineIB = -1;
int visualMotorDrive::m_ControlLineVS = -1;
int visualMotorDrive::m_ControlLinePS = -1;

int visualMotorDrive::m_ReductorVB = -1;
int visualMotorDrive::m_ReductorIB = -1;
int visualMotorDrive::m_ReductorVS = -1;
int visualMotorDrive::m_ReductorPS = -1;

int visualMotorDrive::m_SwivelCamVB = -1;
int visualMotorDrive::m_SwivelCamIB = -1;
int visualMotorDrive::m_SwivelCamVS = -1;
int visualMotorDrive::m_SwivelCamPS = -1;

void FillBox ( graphServer* server, int vb, int start_index, float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	int i;

	// Верхняя грань
	server->FillPositionInVertexBuffer ( vb, start_index + 0, minX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 1, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 2, maxX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 3, maxX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + i, 0.0f, 1.0f, 0.0f );

	// Нижняя грань
	server->FillPositionInVertexBuffer ( vb, start_index + 4, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 5, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 6, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 7, maxX, minY, minZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + 4 + i, 0.0f, -1.0f, 0.0f );

	// Передняя грань
	server->FillPositionInVertexBuffer ( vb, start_index + 8, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 9, minX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 10, maxX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 11, maxX, maxY, minZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + 8 + i, 0.0f, 0.0f, -1.0f );

	// Задняя грань
	server->FillPositionInVertexBuffer ( vb, start_index + 12, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 13, maxX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 14, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 15, minX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + 12 + i, 0.0f, 0.0f, 1.0f );

	// Левая грань
	server->FillPositionInVertexBuffer ( vb, start_index + 16, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 17, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 18, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 19, minX, maxY, minZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + 16 + i, -1.0f, 0.0f, 0.0f );

	// Правая грань
	server->FillPositionInVertexBuffer ( vb, start_index + 20, maxX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 21, maxX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 22, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, start_index + 23, maxX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, start_index + 20 + i, 1.0f, 0.0f, 0.0f );
}

HRESULT visualMotorDrive::InitBuffers ()
{
	graphServer* server = graphServer::Instance ();
	int resource = -1;

	int i;

	int vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -0.25f, 0.25f, 0.0f, 2.0f, -1.0f, 1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_AutoSwitchVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -3.0f, 3.0f, -0.6f, 0.0f, -0.5f, 0.5f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_ControlLineVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 72, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -4.0f, -3.5f, -1.5f, 0.0f, -1.0f, 1.0f );
	FillBox ( server, vb, 24, 3.5f, 4.0f, -1.5f, 0.0f, -1.0f, 1.0f );
	FillBox ( server, vb, 48, -3.5f, 3.5f, -1.5f, -1.0f, -1.0f, 1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_BaseVB = resource;
	else
		return E_FAIL;

	XMVECTOR vector;
	vb = server->CreateVertexBuffer ( L"PN", 18, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	float minX = -3.5f;
	float minY = -0.6f;
	float minZ = 1.0f;
	float maxX = -2.5f;
	float maxY = 0.0f;
	float maxZ = 4.0f;

	// Верхняя грань
	server->FillPositionInVertexBuffer ( vb, 0, minX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, 1, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 2, maxX, maxY, maxZ );
	for ( i = 0; i < 3; i++ )
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 1.0f, 0.0f );

	// Нижняя грань
	server->FillPositionInVertexBuffer ( vb, 3, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 4, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 5, minX, minY, maxZ );
	for ( i = 0; i < 3; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 + i, 0.0f, -1.0f, 0.0f );

	// Задняя грань
	server->FillPositionInVertexBuffer ( vb, 6, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 7, maxX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 8, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 9, minX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 6 + i, 0.0f, 0.0f, 1.0f );

	// Левая грань
	server->FillPositionInVertexBuffer ( vb, 10, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 11, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 12, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 13, minX, maxY, minZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 10 + i, -1.0f, 0.0f, 0.0f );

	// Правая грань
	server->FillPositionInVertexBuffer ( vb, 14, minX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 15, minX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, 16, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 17, maxX, maxY, maxZ );

	vector = XMVector3Normalize ( XMVectorSet ( maxZ - minZ, 0.0f, minX - maxX, 0.0f ));
	
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 14 + i, XMVectorGetX ( vector ), XMVectorGetY ( vector ), XMVectorGetZ ( vector ) );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_LeftWedgeVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 18, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	minX = 2.5f;
	minY = -0.6f;
	minZ = 1.0f;
	maxX = 3.5f;
	maxY = 0.0f;
	maxZ = 4.0f;

	// Верхняя грань
	server->FillPositionInVertexBuffer ( vb, 0, maxX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, 1, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 2, maxX, maxY, maxZ );
	for ( i = 0; i < 3; i++ )
		server->FillNormalInVertexBuffer ( vb, i, 0.0f, 1.0f, 0.0f );

	// Нижняя грань
	server->FillPositionInVertexBuffer ( vb, 3, maxX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 4, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 5, minX, minY, maxZ );
	for ( i = 0; i < 3; i++ )
		server->FillNormalInVertexBuffer ( vb, 3 + i, 0.0f, -1.0f, 0.0f );

	// Задняя грань
	server->FillPositionInVertexBuffer ( vb, 6, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 7, maxX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 8, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 9, minX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 6 + i, 0.0f, 0.0f, 1.0f );

	// Левая грань
	server->FillPositionInVertexBuffer ( vb, 10, minX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 11, minX, maxY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 12, maxX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 13, maxX, maxY, minZ );

	vector = XMVector3Normalize ( XMVectorSet ( minZ - maxZ, 0.0f, minX - maxX, 0.0f ) );

	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 10 + i, XMVectorGetX ( vector ), XMVectorGetY ( vector ), XMVectorGetZ ( vector ) );

	// Правая грань
	server->FillPositionInVertexBuffer ( vb, 14, maxX, minY, minZ );
	server->FillPositionInVertexBuffer ( vb, 15, maxX, maxY, minZ );
	server->FillPositionInVertexBuffer ( vb, 16, maxX, minY, maxZ );
	server->FillPositionInVertexBuffer ( vb, 17, maxX, maxY, maxZ );
	for ( i = 0; i < 4; i++ )
		server->FillNormalInVertexBuffer ( vb, 14 + i, 1.0f, 0.0f, 0.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_RightWedgeVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -3.0f, 0.0f, -1.5f, 0.0f, -3.2f, -3.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_FlapVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -1.0f, 1.0f, 0.0f, 3.0f, -2.0f, -1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_ReductorVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -1.0f, 1.0f, -1.0f, 1.0f, -4.0f, -2.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_MotorVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -0.2f, 0.2f, 0.0f, 1.0f, -2.5f, -2.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_SwivelCamVB = resource;
	else
		return E_FAIL;

	vb = server->CreateVertexBuffer ( L"PN", 24, graphServer::TriangleList );
	if ( vb == -1 )
		return E_FAIL;

	FillBox ( server, vb, 0, -3.5f, 3.5f, -2.0f, -1.5f, -1.0f, 1.0f );

	resource = server->AssignVertexBuffer ( vb );
	if ( resource != -1 )
		visualMotorDrive::m_GateVB = resource;
	else
		return E_FAIL;

	unsigned short indices [108];
	for ( i = 0; i < 18; i++ )
	{
		indices [i * 6 + 0] = i * 4;
		indices [i * 6 + 1] = i * 4 + 1;
		indices [i * 6 + 2] = i * 4 + 3;
		indices [i * 6 + 3] = i * 4;
		indices [i * 6 + 4] = i * 4 + 3;
		indices [i * 6 + 5] = i * 4 + 2;
	}

	resource = server->CreateIndexBuffer ( 36, indices );
	if ( resource != -1 )
	{
		visualMotorDrive::m_AutoSwitchIB = resource;
		visualMotorDrive::m_GateIB = resource;
		visualMotorDrive::m_FlapIB = resource;
		visualMotorDrive::m_MotorIB = resource;
		visualMotorDrive::m_ReductorIB = resource;
		visualMotorDrive::m_SwivelCamIB = resource;
		visualMotorDrive::m_ControlLineIB = resource;
	}
	else
		return E_FAIL;

	resource = server->CreateIndexBuffer ( 108, indices );
	if ( resource != -1 )
		visualMotorDrive::m_BaseIB = resource;
	else
		return E_FAIL;

	unsigned short indices1 [24];
	for ( i = 0; i < 3; i++ )
	{
		indices1 [i * 6 + 0] = 6 + i * 4;
		indices1 [i * 6 + 1] = 6 + i * 4 + 1;
		indices1 [i * 6 + 2] = 6 + i * 4 + 3;
		indices1 [i * 6 + 3] = 6 + i * 4;
		indices1 [i * 6 + 4] = 6 + i * 4 + 3;
		indices1 [i * 6 + 5] = 6 + i * 4 + 2;
	}
	for ( i = 0; i < 6; i++ )
		indices1 [i + 18] = i;

	resource = server->CreateIndexBuffer ( 24, indices1 );
	if ( resource != -1 )
	{
		visualMotorDrive::m_LeftWedgeIB = resource;
		visualMotorDrive::m_RightWedgeIB = resource;
	}
	else
		return E_FAIL;

	resource = server->GetVertexShaderIndex ( L"vs" );
	if ( resource != -1 )
	{
		visualMotorDrive::m_AutoSwitchVS = resource;
		visualMotorDrive::m_GateVS = resource;
		visualMotorDrive::m_BaseVS = resource;
		visualMotorDrive::m_LeftWedgeVS = resource;
		visualMotorDrive::m_RightWedgeVS = resource;
		visualMotorDrive::m_FlapVS = resource;
		visualMotorDrive::m_ReductorVS = resource;
		visualMotorDrive::m_MotorVS = resource;
		visualMotorDrive::m_SwivelCamVS = resource;
		visualMotorDrive::m_ControlLineVS = resource;
	}
	else
		return E_FAIL;

	resource = server->GetPixelShaderIndex ( L"ps" );
	if ( resource != -1 )
	{
		visualMotorDrive::m_AutoSwitchPS = resource;
		visualMotorDrive::m_GatePS = resource;
		visualMotorDrive::m_BasePS = resource;
		visualMotorDrive::m_LeftWedgePS = resource;
		visualMotorDrive::m_RightWedgePS = resource;
		visualMotorDrive::m_FlapPS = resource;
		visualMotorDrive::m_ReductorPS = resource;
		visualMotorDrive::m_MotorPS = resource;
		visualMotorDrive::m_SwivelCamPS = resource;
		visualMotorDrive::m_ControlLinePS = resource;
	}
	else
		return E_FAIL;

	return S_OK;
}

visualMotorDrive::visualMotorDrive () :
	m_X ( 0.0f ),
	m_Y ( 0.0f ),
	m_Z ( 0.0f ),
	m_DirX ( 0.0f ),
	m_DirY ( 0.0f ),
	m_DirZ ( 1.0f )
{
}

visualMotorDrive::~visualMotorDrive ()
{
}

HRESULT visualMotorDrive::AssignScbMotorDrive ( scbMotorDrive* md )
{
	if ( ( this->m_IsCompleted ) || ( md == nullptr ) )
		return E_FAIL;

	this->m_MotorDevice = md->GetDriveDevice ();

	return this->InitGeometry ();
}

void visualMotorDrive::SetPosition ( float x, float y, float z )
{
	if ( this->m_IsCompleted )
		return;
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

void visualMotorDrive::SetDirection ( float dirX, float dirY, float dirZ )
{
	if ( this->m_IsCompleted )
		return;
	this->m_DirX = dirX;
	this->m_DirY = dirY;
	this->m_DirZ = dirZ;
}

HRESULT visualMotorDrive::InitGeometry ()
{
	this->m_VertexBuffers.push_back ( visualMotorDrive::m_AutoSwitchVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_AutoSwitchIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_AutoSwitchVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_AutoSwitchPS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_GateVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_GateIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_GateVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_GatePS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_BaseVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_BaseIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_BaseVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_BasePS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_LeftWedgeVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_LeftWedgeIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_LeftWedgeVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_LeftWedgePS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_RightWedgeVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_RightWedgeIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_RightWedgeVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_RightWedgePS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_FlapVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_FlapIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_FlapVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_FlapPS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_ReductorVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_ReductorIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_ReductorVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_ReductorPS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_MotorVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_MotorIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_MotorVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_MotorPS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_SwivelCamVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_SwivelCamIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_SwivelCamVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_SwivelCamPS );

	this->m_VertexBuffers.push_back ( visualMotorDrive::m_ControlLineVB );
	this->m_IndexBuffers.push_back ( visualMotorDrive::m_ControlLineIB );
	this->m_VertexShaders.push_back ( visualMotorDrive::m_ControlLineVS );
	this->m_PixelShaders.push_back ( visualMotorDrive::m_ControlLinePS );

	return S_OK;
}

void visualMotorDrive::Render ()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX mSpin = XMMatrixIdentity ();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX mTranslate;

	graphServer* server = graphServer::Instance ();

	int vs, ps;

	// Сначала отрисовывается фундамент
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [2];
	ps = this->m_PixelShaders [2];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.1f, 0.1f, 0.1f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.2f, 0.2f, 0.2f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, XMFLOAT4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [2], this->m_VertexBuffers [2] );

	// Затем отрисовывается шибер
	mTranslate = XMMatrixTranslation ( this->m_X - 0.5f + this->m_MotorDevice->GetGatePosition (), this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [1];
	ps = this->m_PixelShaders [1];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.5f, 0.5f, 0.5f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.6f, 0.6f, 0.6f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [1], this->m_VertexBuffers [1] );

	// Затем отрисовывается левый клин
	vs = this->m_VertexShaders [3];
	ps = this->m_PixelShaders [3];

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.0f, 0.0f, 0.8f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.0f, 0.0f, 0.9f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z - 3.0f * this->m_MotorDevice->GetLeftWedgePosition () );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [3], this->m_VertexBuffers [3] );

	// Затем отрисовывается правый клин
	vs = this->m_VertexShaders [4];
	ps = this->m_PixelShaders [4];

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.0f, 0.0f, 0.8f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.0f, 0.0f, 0.9f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z - 3.0f * this->m_MotorDevice->GetRightWedgePosition () );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [4], this->m_VertexBuffers [4] );


	// Затем отрисовываются левый и правый автопереключатели
	vs = this->m_VertexShaders [0];
	ps = this->m_PixelShaders [0];

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.9f, 0.0f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 1.0f, 0.0f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	// ... сначала левый
	mSpin = XMMatrixRotationZ ( - this->m_MotorDevice->GetAutoSwitch12Position () * 30.0f * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X - 1.0f , this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [0], this->m_VertexBuffers [0] );

	// ... потом правый
	mSpin = XMMatrixRotationZ ( this->m_MotorDevice->GetAutoSwitch34Position () * 30.0f * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X + 1.0f, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [0], this->m_VertexBuffers [0] );


	// Потом отрисовывается курбельная заслонка
	mSpin = XMMatrixRotationZ ( this->m_MotorDevice->GetFlapPosition () * 20.0f * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [5];
	ps = this->m_PixelShaders [5];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.3f, 0.3f, 0.3f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.4f, 0.4f, 0.4f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [5], this->m_VertexBuffers [5] );


	// Затем отрисовываются шестерня редуктора
	mSpin = XMMatrixRotationZ ( this->m_MotorDevice->GetReductorPhase () * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y - 3.0f, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [6];
	ps = this->m_PixelShaders [6];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.0f, 0.8f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.0f, 0.9f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [6], this->m_VertexBuffers [6] );


	// Потом завершение отрисовывается якорь двигателя
	mSpin = XMMatrixRotationZ ( this->m_MotorDevice->GetMotorPhase () * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X, this->m_Y - 3.0f, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [7];
	ps = this->m_PixelShaders [7];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.0f, 0.5f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.0f, 0.6f, 0.0f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [7], this->m_VertexBuffers [7] );

	// Затем отрисовываются левый и правый поворотные кулачки
	vs = this->m_VertexShaders [8];
	ps = this->m_PixelShaders [8];

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.7f, 0.7f, 0.7f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.8f, 0.8f, 0.8f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	// ... сначала левый
	mSpin = XMMatrixRotationZ ( ( this->m_MotorDevice->GetLeftSwivelCamPosition () * 20.0f - 40.0f ) * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X - 1.5f, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [8], this->m_VertexBuffers [8] );

	// ... потом правый
	mSpin = XMMatrixRotationZ ( ( - this->m_MotorDevice->GetRightSwivelCamPosition () * 20.0f + 40.0f ) * XM_PI / 180.0f );
	mTranslate = XMMatrixTranslation ( this->m_X + 1.5f, this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->Draw ( vs, ps, this->m_IndexBuffers [8], this->m_VertexBuffers [8] );


	// И в завершении отрисовывается контрольная линейка
	mSpin = XMMatrixIdentity ();
	mTranslate = XMMatrixTranslation ( this->m_X - 0.5f + this->m_MotorDevice->GetControlLinePosition (), this->m_Y, this->m_Z );
	this->m_WorldMatrix = mSpin * mTranslate;

	vs = this->m_VertexShaders [9];
	ps = this->m_PixelShaders [9];

	server->GetVertexShader ( vs )->SetConstant ( graphShader::WorldMatrix, this->m_WorldMatrix );

	server->GetPixelShader ( ps )->SetConstant ( graphShader::DiffuseColor, XMFLOAT4 ( 0.5f, 0.5f, 0.5f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::SpecularColor, XMFLOAT4 ( 0.6f, 0.6f, 0.6f, 1.0f ) );
	server->GetPixelShader ( ps )->SetConstant ( graphShader::EmissiveColor, DirectX::XMVectorSet ( 0.0f, 0.0f, 0.0f, 1.0f ) );

	server->Draw ( vs, ps, this->m_IndexBuffers [9], this->m_VertexBuffers [9] );

}

