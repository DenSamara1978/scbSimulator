#include "MotorDrive.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\MotorDriveScheme.h"
#include "..\scb\MotorDriveDevice.h"

using namespace visual;

using graphics::GraphicsServer;
using graphics::Shader;

int MotorDrive::autoSwitchVB = -1;
int MotorDrive::autoSwitchIB = -1;
int MotorDrive::autoSwitchVS = -1;
int MotorDrive::autoSwitchPS = -1;

int MotorDrive::gateVB = -1;
int MotorDrive::gateIB = -1;
int MotorDrive::gateVS = -1;
int MotorDrive::gatePS = -1;

int MotorDrive::baseVB = -1;
int MotorDrive::baseIB = -1;
int MotorDrive::baseVS = -1;
int MotorDrive::basePS = -1;

int MotorDrive::leftWedgeVB = -1;
int MotorDrive::leftWedgeIB = -1;
int MotorDrive::leftWedgeVS = -1;
int MotorDrive::leftWedgePS = -1;

int MotorDrive::rightWedgeVB = -1;
int MotorDrive::rightWedgeIB = -1;
int MotorDrive::rightWedgeVS = -1;
int MotorDrive::rightWedgePS = -1;

int MotorDrive::flapVB = -1;
int MotorDrive::flapIB = -1;
int MotorDrive::flapVS = -1;
int MotorDrive::flapPS = -1;

int MotorDrive::motorVB = -1;
int MotorDrive::motorIB = -1;
int MotorDrive::motorVS = -1;
int MotorDrive::motorPS = -1;

int MotorDrive::controlLineVB = -1;
int MotorDrive::controlLineIB = -1;
int MotorDrive::controlLineVS = -1;
int MotorDrive::controlLinePS = -1;

int MotorDrive::reductorVB = -1;
int MotorDrive::reductorIB = -1;
int MotorDrive::reductorVS = -1;
int MotorDrive::reductorPS = -1;

int MotorDrive::swivelCamVB = -1;
int MotorDrive::swivelCamIB = -1;
int MotorDrive::swivelCamVS = -1;
int MotorDrive::swivelCamPS = -1;

void fillBox(GraphicsServer* server, int vertexBuffer, int startIndex, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	int i;

	// Верхняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 0, minX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 1, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 2, maxX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 3, maxX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + i, 0.0f, 1.0f, 0.0f);

	// Нижняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 4, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 5, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 6, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 7, maxX, minY, minZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + 4 + i, 0.0f, -1.0f, 0.0f);

	// Передняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 8, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 9, minX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 10, maxX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 11, maxX, maxY, minZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + 8 + i, 0.0f, 0.0f, -1.0f);

	// Задняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 12, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 13, maxX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 14, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 15, minX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + 12 + i, 0.0f, 0.0f, 1.0f);

	// Левая грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 16, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 17, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 18, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 19, minX, maxY, minZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + 16 + i, -1.0f, 0.0f, 0.0f);

	// Правая грань
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 20, maxX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 21, maxX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 22, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, startIndex + 23, maxX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, startIndex + 20 + i, 1.0f, 0.0f, 0.0f);
}

bool MotorDrive::initializeBuffers()
{
	GraphicsServer* server = GraphicsServer::getInstance();
	int resource = -1;

	int i;

	int vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -0.25f, 0.25f, 0.0f, 2.0f, -1.0f, 1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::autoSwitchVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -3.0f, 3.0f, -0.6f, 0.0f, -0.5f, 0.5f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::controlLineVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 72, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -4.0f, -3.5f, -1.5f, 0.0f, -1.0f, 1.0f);
	fillBox(server, vertexBuffer, 24, 3.5f, 4.0f, -1.5f, 0.0f, -1.0f, 1.0f);
	fillBox(server, vertexBuffer, 48, -3.5f, 3.5f, -1.5f, -1.0f, -1.0f, 1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::baseVB = resource;
	else
		return false;

	XMVECTOR vector;
	vertexBuffer = server->createVertexBuffer(L"PN", 18, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	float minX = -3.5f;
	float minY = -0.6f;
	float minZ = 1.0f;
	float maxX = -2.5f;
	float maxY = 0.0f;
	float maxZ = 4.0f;

	// Верхняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 0, minX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 1, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 2, maxX, maxY, maxZ);
	for (i = 0; i < 3; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 1.0f, 0.0f);

	// Нижняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 3, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 4, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 5, minX, minY, maxZ);
	for (i = 0; i < 3; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 + i, 0.0f, -1.0f, 0.0f);

	// Задняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 6, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 7, maxX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 8, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 9, minX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 6 + i, 0.0f, 0.0f, 1.0f);

	// Левая грань
	server->fillPositionInVertexBuffer(vertexBuffer, 10, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 11, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 12, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 13, minX, maxY, minZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 10 + i, -1.0f, 0.0f, 0.0f);

	// Правая грань
	server->fillPositionInVertexBuffer(vertexBuffer, 14, minX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 15, minX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 16, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 17, maxX, maxY, maxZ);

	vector = XMVector3Normalize(XMVectorSet(maxZ - minZ, 0.0f, minX - maxX, 0.0f));

	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 14 + i, XMVectorGetX(vector), XMVectorGetY(vector), XMVectorGetZ(vector));

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::leftWedgeVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 18, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	minX = 2.5f;
	minY = -0.6f;
	minZ = 1.0f;
	maxX = 3.5f;
	maxY = 0.0f;
	maxZ = 4.0f;

	// Верхняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 0, maxX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 1, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 2, maxX, maxY, maxZ);
	for (i = 0; i < 3; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 1.0f, 0.0f);

	// Нижняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 3, maxX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 4, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 5, minX, minY, maxZ);
	for (i = 0; i < 3; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 + i, 0.0f, -1.0f, 0.0f);

	// Задняя грань
	server->fillPositionInVertexBuffer(vertexBuffer, 6, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 7, maxX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 8, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 9, minX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 6 + i, 0.0f, 0.0f, 1.0f);

	// Левая грань
	server->fillPositionInVertexBuffer(vertexBuffer, 10, minX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 11, minX, maxY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 12, maxX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 13, maxX, maxY, minZ);

	vector = XMVector3Normalize(XMVectorSet(minZ - maxZ, 0.0f, minX - maxX, 0.0f));

	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 10 + i, XMVectorGetX(vector), XMVectorGetY(vector), XMVectorGetZ(vector));

	// Правая грань
	server->fillPositionInVertexBuffer(vertexBuffer, 14, maxX, minY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 15, maxX, maxY, minZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 16, maxX, minY, maxZ);
	server->fillPositionInVertexBuffer(vertexBuffer, 17, maxX, maxY, maxZ);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 14 + i, 1.0f, 0.0f, 0.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::rightWedgeVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -3.0f, 0.0f, -1.5f, 0.0f, -3.2f, -3.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::flapVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -1.0f, 1.0f, 0.0f, 3.0f, -2.0f, -1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::reductorVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -1.0f, 1.0f, -1.0f, 1.0f, -4.0f, -2.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::motorVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -0.2f, 0.2f, 0.0f, 1.0f, -2.5f, -2.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::swivelCamVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 24, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	fillBox(server, vertexBuffer, 0, -3.5f, 3.5f, -2.0f, -1.5f, -1.0f, 1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		MotorDrive::gateVB = resource;
	else
		return false;

	unsigned short indices[108];
	for (i = 0; i < 18; ++i)
	{
		indices[i * 6 + 0] = i * 4;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 3;
		indices[i * 6 + 3] = i * 4;
		indices[i * 6 + 4] = i * 4 + 3;
		indices[i * 6 + 5] = i * 4 + 2;
	}

	resource = server->createIndexBuffer(36, indices);
	if (resource != -1)
	{
		MotorDrive::autoSwitchIB = resource;
		MotorDrive::gateIB = resource;
		MotorDrive::flapIB = resource;
		MotorDrive::motorIB = resource;
		MotorDrive::reductorIB = resource;
		MotorDrive::swivelCamIB = resource;
		MotorDrive::controlLineIB = resource;
	}
	else
		return false;

	resource = server->createIndexBuffer(108, indices);
	if (resource != -1)
		MotorDrive::baseIB = resource;
	else
		return false;

	unsigned short indices1[24];
	for (i = 0; i < 3; ++i)
	{
		indices1[i * 6 + 0] = 6 + i * 4;
		indices1[i * 6 + 1] = 6 + i * 4 + 1;
		indices1[i * 6 + 2] = 6 + i * 4 + 3;
		indices1[i * 6 + 3] = 6 + i * 4;
		indices1[i * 6 + 4] = 6 + i * 4 + 3;
		indices1[i * 6 + 5] = 6 + i * 4 + 2;
	}
	for (i = 0; i < 6; ++i)
		indices1[i + 18] = i;

	resource = server->createIndexBuffer(24, indices1);
	if (resource != -1)
	{
		MotorDrive::leftWedgeIB = resource;
		MotorDrive::rightWedgeIB = resource;
	}
	else
		return false;

	resource = server->getVertexShaderIndexByName(L"vs");
	if (resource != -1)
	{
		MotorDrive::autoSwitchVS = resource;
		MotorDrive::gateVS = resource;
		MotorDrive::baseVS = resource;
		MotorDrive::leftWedgeVS = resource;
		MotorDrive::rightWedgeVS = resource;
		MotorDrive::flapVS = resource;
		MotorDrive::reductorVS = resource;
		MotorDrive::motorVS = resource;
		MotorDrive::swivelCamVS = resource;
		MotorDrive::controlLineVS = resource;
	}
	else
		return false;

	resource = server->getPixelShaderIndexByName(L"ps");
	if (resource != -1)
	{
		MotorDrive::autoSwitchPS = resource;
		MotorDrive::gatePS = resource;
		MotorDrive::basePS = resource;
		MotorDrive::leftWedgePS = resource;
		MotorDrive::rightWedgePS = resource;
		MotorDrive::flapPS = resource;
		MotorDrive::reductorPS = resource;
		MotorDrive::motorPS = resource;
		MotorDrive::swivelCamPS = resource;
		MotorDrive::controlLinePS = resource;
	}
	else
		return false;

	return true;
}

MotorDrive::MotorDrive() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	dirX(0.0f),
	dirY(0.0f),
	dirZ(1.0f)
{
}

MotorDrive::~MotorDrive()
{
}

bool MotorDrive::assignScbMotorDrive(scb::MotorDriveScheme* motorDrive)
{
	if (this->isCompleted or (motorDrive == nullptr))
		return false;

	this->motorDevice = motorDrive->getDriveDevice();
	return this->initializeGeometry();
}

void MotorDrive::setPosition(float x, float y, float z)
{
	if (this->isCompleted)
		return;
	this->x = x;
	this->y = y;
	this->z = z;
}

void MotorDrive::setDirection(float dirX, float dirY, float dirZ)
{
	if (this->isCompleted)
		return;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

bool MotorDrive::initializeGeometry()
{
	this->vertexBuffers.push_back(MotorDrive::autoSwitchVB);
	this->indexBuffers.push_back(MotorDrive::autoSwitchIB);
	this->vertexShaders.push_back(MotorDrive::autoSwitchVS);
	this->pixelShaders.push_back(MotorDrive::autoSwitchPS);

	this->vertexBuffers.push_back(MotorDrive::gateVB);
	this->indexBuffers.push_back(MotorDrive::gateIB);
	this->vertexShaders.push_back(MotorDrive::gateVS);
	this->pixelShaders.push_back(MotorDrive::gatePS);

	this->vertexBuffers.push_back(MotorDrive::baseVB);
	this->indexBuffers.push_back(MotorDrive::baseIB);
	this->vertexShaders.push_back(MotorDrive::baseVS);
	this->pixelShaders.push_back(MotorDrive::basePS);

	this->vertexBuffers.push_back(MotorDrive::leftWedgeVB);
	this->indexBuffers.push_back(MotorDrive::leftWedgeIB);
	this->vertexShaders.push_back(MotorDrive::leftWedgeVS);
	this->pixelShaders.push_back(MotorDrive::leftWedgePS);

	this->vertexBuffers.push_back(MotorDrive::rightWedgeVB);
	this->indexBuffers.push_back(MotorDrive::rightWedgeIB);
	this->vertexShaders.push_back(MotorDrive::rightWedgeVS);
	this->pixelShaders.push_back(MotorDrive::rightWedgePS);

	this->vertexBuffers.push_back(MotorDrive::flapVB);
	this->indexBuffers.push_back(MotorDrive::flapIB);
	this->vertexShaders.push_back(MotorDrive::flapVS);
	this->pixelShaders.push_back(MotorDrive::flapPS);

	this->vertexBuffers.push_back(MotorDrive::reductorVB);
	this->indexBuffers.push_back(MotorDrive::reductorIB);
	this->vertexShaders.push_back(MotorDrive::reductorVS);
	this->pixelShaders.push_back(MotorDrive::reductorPS);

	this->vertexBuffers.push_back(MotorDrive::motorVB);
	this->indexBuffers.push_back(MotorDrive::motorIB);
	this->vertexShaders.push_back(MotorDrive::motorVS);
	this->pixelShaders.push_back(MotorDrive::motorPS);

	this->vertexBuffers.push_back(MotorDrive::swivelCamVB);
	this->indexBuffers.push_back(MotorDrive::swivelCamIB);
	this->vertexShaders.push_back(MotorDrive::swivelCamVS);
	this->pixelShaders.push_back(MotorDrive::swivelCamPS);

	this->vertexBuffers.push_back(MotorDrive::controlLineVB);
	this->indexBuffers.push_back(MotorDrive::controlLineIB);
	this->vertexShaders.push_back(MotorDrive::controlLineVS);
	this->pixelShaders.push_back(MotorDrive::controlLinePS);

	return true;
}

void MotorDrive::render()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX matrixSpin = XMMatrixIdentity();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX matrixTranslate;

	GraphicsServer* server = GraphicsServer::getInstance();

	int vertexShader, pixelShader;

	// Сначала отрисовывается фундамент
	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[2];
	pixelShader = this->pixelShaders[2];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[2], this->vertexBuffers[2]);

	// Затем отрисовывается шибер
	matrixTranslate = XMMatrixTranslation(this->x - 0.5f + this->motorDevice->getGatePosition(), this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[1];
	pixelShader = this->pixelShaders[1];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[1], this->vertexBuffers[1]);

	// Затем отрисовывается левый клин
	vertexShader = this->vertexShaders[3];
	pixelShader = this->pixelShaders[3];

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.0f, 0.0f, 0.8f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.0f, 0.0f, 0.9f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z - 3.0f * this->motorDevice->getLeftWedgePosition());
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[3], this->vertexBuffers[3]);

	// Затем отрисовывается правый клин
	vertexShader = this->vertexShaders[4];
	pixelShader = this->pixelShaders[4];

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.0f, 0.0f, 0.8f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.0f, 0.0f, 0.9f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z - 3.0f * this->motorDevice->getRightWedgePosition());
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[4], this->vertexBuffers[4]);


	// Затем отрисовываются левый и правый автопереключатели
	vertexShader = this->vertexShaders[0];
	pixelShader = this->pixelShaders[0];

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.9f, 0.0f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	// ... сначала левый
	matrixSpin = XMMatrixRotationZ(-this->motorDevice->getAutoSwitch12Position() * 30.0f * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x - 1.0f, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[0], this->vertexBuffers[0]);

	// ... потом правый
	matrixSpin = XMMatrixRotationZ(this->motorDevice->getAutoSwitch34Position() * 30.0f * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x + 1.0f, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[0], this->vertexBuffers[0]);


	// Потом отрисовывается курбельная заслонка
	matrixSpin = XMMatrixRotationZ(this->motorDevice->getFlapPosition() * 20.0f * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[5];
	pixelShader = this->pixelShaders[5];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[5], this->vertexBuffers[5]);


	// Затем отрисовываются шестерня редуктора
	matrixSpin = XMMatrixRotationZ(this->motorDevice->getReductorPhase() * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x, this->y - 3.0f, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[6];
	pixelShader = this->pixelShaders[6];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.0f, 0.8f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.0f, 0.9f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[6], this->vertexBuffers[6]);


	// Потом завершение отрисовывается якорь двигателя
	matrixSpin = XMMatrixRotationZ(this->motorDevice->getMotorPhase() * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x, this->y - 3.0f, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[7];
	pixelShader = this->pixelShaders[7];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.0f, 0.6f, 0.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[7], this->vertexBuffers[7]);

	// Затем отрисовываются левый и правый поворотные кулачки
	vertexShader = this->vertexShaders[8];
	pixelShader = this->pixelShaders[8];

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	// ... сначала левый
	matrixSpin = XMMatrixRotationZ((this->motorDevice->getLeftSwivelCamPosition() * 20.0f - 40.0f) * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x - 1.5f, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[8], this->vertexBuffers[8]);

	// ... потом правый
	matrixSpin = XMMatrixRotationZ((-this->motorDevice->getRightSwivelCamPosition() * 20.0f + 40.0f) * XM_PI / 180.0f);
	matrixTranslate = XMMatrixTranslation(this->x + 1.5f, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->draw(vertexShader, pixelShader, this->indexBuffers[8], this->vertexBuffers[8]);


	// И в завершении отрисовывается контрольная линейка
	matrixSpin = XMMatrixIdentity();
	matrixTranslate = XMMatrixTranslation(this->x - 0.5f + this->motorDevice->getControlLinePosition(), this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[9];
	pixelShader = this->pixelShaders[9];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[9], this->vertexBuffers[9]);

}

