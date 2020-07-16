#include "PultTablo.h"
#include "..\util\range.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\PultTabloScheme.h"
#include "..\scb\PultTabloLampGroup.h"

using namespace visual;
using graphics::GraphicsServer;
using util::inRange;

int PultTablo::ledCellVB = -1;
int PultTablo::ledCellIB = -1;
int PultTablo::ledRoundVB = -1;
int PultTablo::ledRoundIB = -1;
int PultTablo::ledVS = -1;
int PultTablo::ledPS = -1;
int PultTablo::plateVB = -1;
int PultTablo::plateIB = -1;
int PultTablo::plateVS = -1;
int PultTablo::platePS = -1;

bool PultTablo::initializeBuffers()
{
	GraphicsServer* server = GraphicsServer::getInstance();
	int resource = -1;

	const int nSectors = 24;
	int i;
	float angle;

	int vertexBuffer = server->createVertexBuffer(L"PN", nSectors, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	for (i = 0; i < nSectors; ++i)
	{
		angle = 2.0f * XM_PI * i / nSectors;
		server->fillPositionInVertexBuffer(vertexBuffer, i, cosf(angle) * 0.3f, sinf(angle) * 0.3f, -0.01f);
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 0.0f, -1.0f);
	}

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTablo::ledRoundVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 4, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	server->fillPositionInVertexBuffer(vertexBuffer, 0, -0.5f, -0.2f, -0.01f);
	server->fillPositionInVertexBuffer(vertexBuffer, 1, -0.5f, 0.2f, -0.01f);
	server->fillPositionInVertexBuffer(vertexBuffer, 2, 0.5f, -0.2f, -0.01f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3, 0.5f, 0.2f, -0.01f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 0.0f, -1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTablo::ledCellVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 4, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	server->fillPositionInVertexBuffer(vertexBuffer, 0, -6.0f, -6.0f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 1, -6.0f, 6.0f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 2, 6.0f, -6.0f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3, 6.0f, 6.0f, 0.0f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 0.0f, -1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTablo::plateVB = resource;
	else
		return false;

	const int num_tris = nSectors - 2;
	unsigned short indices[(nSectors - 2) * 3];
	for (i = 0; i < nSectors - 2; ++i)
	{
		if (i < nSectors / 2 - 1)
		{
			indices[i * 3] = i + 1;
			indices[i * 3 + 1] = i;
			indices[i * 3 + 2] = nSectors - 1 - i;
		}
		else
		{
			indices[i * 3] = i + 2;
			indices[i * 3 + 1] = i + 1;
			indices[i * 3 + 2] = nSectors - 2 - i;
		}
	}

	resource = server->createIndexBuffer(num_tris * 3, indices);
	if (resource != -1)
		PultTablo::ledRoundIB = resource;
	else
		return false;

	unsigned short indices1[] = {0, 1, 3, 0, 3, 2};
	resource = server->createIndexBuffer(6, indices1);
	if (resource != -1)
	{
		PultTablo::plateIB = resource;
		PultTablo::ledCellIB = resource;
	}
	else
		return false;

	resource = server->getVertexShaderIndexByName(L"vs");
	if (resource != -1)
	{
		PultTablo::ledVS = resource;
		PultTablo::plateVS = resource;
	}
	else
		return false;

	resource = server->getPixelShaderIndexByName(L"ps");
	if (resource != -1)
	{
		PultTablo::ledPS = resource;
		PultTablo::platePS = resource;
	}
	else
		return false;

	return true;
}

PultTablo::PultTablo() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	dirX(0.0f),
	dirY(1.0f),
	dirZ(0.0f),
	pultTabloScheme(nullptr)
{
}

PultTablo::~PultTablo()
{
}

bool PultTablo::assignPultTablo(scb::PultTabloScheme* pultTabloScheme)
{
	if (this->isCompleted or (pultTabloScheme == nullptr))
		return false;

	this->pultTabloScheme = pultTabloScheme;
	return this->initializeGeometry();
}

void PultTablo::addCellLamp(int group, int bit, float x, float y, int angle, Color color)
{
	bool isInRange = inRange(group, this->pultTabloScheme->getLampGroupCount());
	if (!isInRange)
		return;

	PultTablo::LampInfo info;
	info.group = group;
	info.bit = bit;
	info.x = x;
	info.y = y;
	info.type = 0;
	info.angle = (XM_PI / 180.f) * angle;
	info.color = this->getD3dColor(color);
	this->lamps.push_back(info);
}

void PultTablo::addRoundLamp(int group, int bit, float x, float y, Color color)
{
	bool isInRange = inRange(group, this->pultTabloScheme->getLampGroupCount());
	if (!isInRange)
		return;

	PultTablo::LampInfo info;
	info.group = group;
	info.bit = bit;
	info.x = x;
	info.y = y;
	info.type = 1;
	info.angle = 0.0f;
	info.color = this->getD3dColor(color);
	this->lamps.push_back(info);
}

void PultTablo::setPosition(float x, float y, float z)
{
	if (this->isCompleted)
		return;
	this->x = x;
	this->y = y;
	this->z = z;
}

void PultTablo::setDirection(float dirX, float dirY, float dirZ)
{
	if (this->isCompleted)
		return;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

bool PultTablo::initializeGeometry()
{
	this->vertexBuffers.push_back(PultTablo::ledCellVB);
	this->indexBuffers.push_back(PultTablo::ledCellIB);
	this->vertexShaders.push_back(PultTablo::ledVS);
	this->pixelShaders.push_back(PultTablo::ledPS);

	this->vertexBuffers.push_back(PultTablo::ledRoundVB);
	this->indexBuffers.push_back(PultTablo::ledRoundIB);
	this->vertexShaders.push_back(PultTablo::ledVS);
	this->pixelShaders.push_back(PultTablo::ledPS);

	this->vertexBuffers.push_back(PultTablo::plateVB);
	this->indexBuffers.push_back(PultTablo::plateIB);
	this->vertexShaders.push_back(PultTablo::plateVS);
	this->pixelShaders.push_back(PultTablo::platePS);

	return true;
}

void PultTablo::render()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX matrixSpin;
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX matrixTranslate;


	GraphicsServer* server = GraphicsServer::getInstance();
	int vertexShader, pixelShader;

	for (const auto& info : this->lamps)
	{
		vertexShader = this->vertexShaders[info.type];
		pixelShader = this->pixelShaders[info.type];

		matrixSpin = XMMatrixRotationZ(info.angle);
		matrixTranslate = XMMatrixTranslation(info.x + this->x, info.y + this->y, this->z);
		this->worldMatrix = matrixSpin * matrixTranslate;

		server->getVertexShader(vertexShader)->setConstant(graphics::Shader::ConstantType::WorldMatrix, this->worldMatrix);
		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::DiffuseColor, XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::SpecularColor, XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

		if (this->pultTabloScheme->getLampGroup(info.group)->getLampStatus(info.bit))
			server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, info.color);
		else
			server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

		server->draw(vertexShader, pixelShader, this->indexBuffers[info.type], this->vertexBuffers[info.type]);
	}

	matrixSpin = XMMatrixIdentity();
	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[2];
	pixelShader = this->pixelShaders[2];

	server->getVertexShader(vertexShader)->setConstant(graphics::Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::DiffuseColor, XMFLOAT4(0.6f, 0.6f, 0.9f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::SpecularColor, XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[2], this->vertexBuffers[2]);
}
