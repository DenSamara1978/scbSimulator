#include "LightSignal.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\LightSignalScheme.h"
#include "..\scb\LightSignalLamp.h"

using namespace visual;
using graphics::GraphicsServer;
using scb::LightSignalScheme;
using scb::LightSignalLamp;

int LightSignal::genVB = -1;
int LightSignal::genVS = -1;
int LightSignal::genPS = -1;
int LightSignal::lensVB = -1;
int LightSignal::lensVS = -1;
int LightSignal::lensPS = -1;
int LightSignal::mainIB = -1;

bool LightSignal::initializeBuffers()
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
		server->fillPositionInVertexBuffer(vertexBuffer, i, cosf(angle) * 0.98f, sinf(angle) * 0.98f, 0.0f);
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 0.0f, -1.0f);
	}

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		LightSignal::genVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", nSectors, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	for (i = 0; i < nSectors; ++i)
	{
		angle = 2.0f * XM_PI * i / nSectors;
		server->fillPositionInVertexBuffer(vertexBuffer, i, cosf(angle) * 0.85f, sinf(angle) * 0.85f, -0.01f);
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 0.0f, -1.0f);
	}

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		LightSignal::lensVB = resource;
	else
		return false;

	const int nTris = nSectors - 2;
	const int nIndices = nTris * 3;
	unsigned short indices[nIndices];
	for (i = 0; i < nTris; i++)
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

	resource = server->createIndexBuffer(nIndices * 3, indices);
	if (resource != -1)
		LightSignal::mainIB = resource;
	else
		return false;

	resource = server->getVertexShaderIndexByName(L"vs");
	if (resource != -1)
	{
		LightSignal::genVS = resource;
		LightSignal::lensVS = resource;
	}
	else
		return false;

	resource = server->getPixelShaderIndexByName(L"ps");
	if (resource != -1)
	{
		LightSignal::genPS = resource;
		LightSignal::lensPS = resource;
	}
	else
		return false;

	return true;
}

LightSignal::LightSignal() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	dirX(0.0f),
	dirY(0.0f),
	dirZ(1.0f)
{
}

LightSignal::~LightSignal()
{
}

bool LightSignal::assignScbLightSignal(LightSignalScheme* lightSignalScheme)
{
	if (this->isCompleted or (lightSignalScheme == nullptr))
		return false;

	this->lamps.clear();
	const auto count = lightSignalScheme->getDeviceCount();
	for (int i = 0; i < count; ++i)
	{
		LampDescription description;
		description.lampLink = dynamic_cast<scb::LightSignalLamp*>(lightSignalScheme->getDevice(i));
		description.color = this->getD3dColor(description.lampLink->getColor());
		this->lamps.push_back(description);
	}

	return this->initializeGeometry();
}

void LightSignal::setPosition(float x, float y, float z)
{
	if (this->isCompleted)
		return;
	this->x = x;
	this->y = y;
	this->z = z;
}

void LightSignal::setDirection(float dirX, float dirY, float dirZ)
{
	if (this->isCompleted)
		return;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

bool LightSignal::initializeGeometry()
{
	const auto count = this->lamps.size();
	for (int i = 0; i < count; ++i)
	{
		this->vertexBuffers.push_back(LightSignal::genVB);
		this->indexBuffers.push_back(LightSignal::mainIB);
		this->vertexShaders.push_back(LightSignal::genVS);
		this->pixelShaders.push_back(LightSignal::genPS);

		this->vertexBuffers.push_back(LightSignal::lensVB);
		this->indexBuffers.push_back(LightSignal::mainIB);
		this->vertexShaders.push_back(LightSignal::lensVS);
		this->pixelShaders.push_back(LightSignal::lensPS);
	}

	return true;
}

void LightSignal::render()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX matrixSpin = XMMatrixIdentity();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX matrixTranslate;

	GraphicsServer* server = GraphicsServer::getInstance();

	int vertexShader, pixelShader;

	const auto count = this->lamps.size();
	for (int i = 0; i < count; ++i)
	{
		matrixTranslate = XMMatrixTranslation(this->x, this->y - 1.0f + 2.0f * (count - i), this->z);
		this->worldMatrix = matrixSpin * matrixTranslate;


		auto index = i * 2;

		vertexShader = this->vertexShaders[index];
		pixelShader = this->pixelShaders[index];

		server->getVertexShader(vertexShader)->setConstant(graphics::Shader::ConstantType::WorldMatrix, this->worldMatrix);

		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::DiffuseColor, XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::SpecularColor, XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

		server->draw(vertexShader, pixelShader, this->indexBuffers[index], this->vertexBuffers[index]);


		++index;

		vertexShader = this->vertexShaders[index];
		pixelShader = this->pixelShaders[index];

		server->getVertexShader(vertexShader)->setConstant(graphics::Shader::ConstantType::WorldMatrix, this->worldMatrix);

		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::DiffuseColor, XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::SpecularColor, XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
		if (this->lamps[i].lampLink != nullptr)
			server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, DirectX::XMVectorLerp(DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), this->lamps[i].color, this->lamps[i].lampLink->getBright()));
		else
			server->getPixelShader(pixelShader)->setConstant(graphics::Shader::ConstantType::EmissiveColor, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));


		server->draw(vertexShader, pixelShader, this->indexBuffers[index], this->vertexBuffers[index]);
	}
}

