#include "PultTabloButton.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\PultTabloAbstractButton.h"
#include "..\scb\PultTabloScheme.h"
#include "..\util\range.h"
#include "..\util\Color.h"

using namespace visual;

using graphics::GraphicsServer;
using graphics::Shader;

int PultTabloButton::mainVB = -1;
int PultTabloButton::plateVB = -1;
int PultTabloButton::mainVS = -1;
int PultTabloButton::mainPS = -1;
int PultTabloButton::mainIB = -1;
int PultTabloButton::plateIB = -1;

bool PultTabloButton::initializeBuffers()
{
	GraphicsServer* server = GraphicsServer::getInstance();
	int resource = -1;

	const int nSectors = 24;
	int i;
	float angle, sine, cosine;

	int vertexBuffer = server->createVertexBuffer(L"PN", nSectors * 3, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	for (i = 0; i < nSectors; ++i)
	{
		angle = 2.0f * XM_PI * i / nSectors;
		cosine = cosf(angle);
		sine = sinf(angle);
		server->fillPositionInVertexBuffer(vertexBuffer, i, cosine * 0.5f, 0.9f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 1.0f, 0.0f);
		server->fillPositionInVertexBuffer(vertexBuffer, i + nSectors, cosine * 0.5f, 0.9f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i + nSectors, cosine, 0.0f, sine);
		server->fillPositionInVertexBuffer(vertexBuffer, i + 2 * nSectors, cosine * 0.5f, -0.1f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i + 2 * nSectors, cosine, 0.0f, sine);
	}

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTabloButton::mainVB = resource;
	else
		return false;

	vertexBuffer = server->createVertexBuffer(L"PN", 4, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	server->fillPositionInVertexBuffer(vertexBuffer, 0, 1.0f, 0.0f, 1.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 1, 1.0f, 0.0f, -1.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 2, -1.0f, 0.0f, 1.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3, -1.0f, 0.0f, -1.0f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 1.0f, 0.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTabloButton::plateVB = resource;
	else
		return false;

	int nTriangles = nSectors - 2;
	unsigned short indices[(nSectors - 2) * 3 + nSectors * 6];
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
	for (i = 0; i < nSectors - 1; ++i)
	{
		indices[(nSectors - 2) * 3 + i * 6] = 2 * nSectors + i + 1;
		indices[(nSectors - 2) * 3 + i * 6 + 1] = 2 * nSectors + i;
		indices[(nSectors - 2) * 3 + i * 6 + 2] = nSectors + i + 1;
		indices[(nSectors - 2) * 3 + i * 6 + 3] = 2 * nSectors + i;
		indices[(nSectors - 2) * 3 + i * 6 + 4] = nSectors + i;
		indices[(nSectors - 2) * 3 + i * 6 + 5] = nSectors + i + 1;
	}
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6] = 2 * nSectors;
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6 + 1] = 3 * nSectors - 1;
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6 + 2] = nSectors;
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6 + 3] = 3 * nSectors - 1;
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6 + 4] = 2 * nSectors - 1;
	indices[(nSectors - 2) * 3 + (nSectors - 1) * 6 + 5] = nSectors;

	resource = server->createIndexBuffer(nTriangles * 3 + nSectors * 6, indices);
	if (resource != -1)
		PultTabloButton::mainIB = resource;
	else
		return false;

	unsigned short indices1[] = {0, 1, 2, 2, 1, 3};
	resource = server->createIndexBuffer(6, indices1);
	if (resource != -1)
		PultTabloButton::plateIB = resource;
	else
		return false;

	resource = server->getVertexShaderIndexByName(L"vs");
	if (resource != -1)
		PultTabloButton::mainVS = resource;
	else
		return false;

	resource = server->getPixelShaderIndexByName(L"ps");
	if (resource != -1)
		PultTabloButton::mainPS = resource;
	else
		return false;

	return true;
}

PultTabloButton::PultTabloButton() :
	buttonLink(nullptr),
	x(0.0f),
	y(0.0f),
	z(0.0f),
	dirX(0.0f),
	dirY(1.0f),
	dirZ(0.0f),
	diffuseColor(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
	specularColor(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f))
{
}

PultTabloButton::~PultTabloButton()
{
}

bool PultTabloButton::assignButton(scb::PultTabloScheme* pultTabloScheme, int device)
{
	if (this->isCompleted or (pultTabloScheme == nullptr))
		return false;

	auto isInRange = inRange(device, pultTabloScheme->getActiveDeviceCount());
	if (!isInRange)
		return false;

	if ((this->buttonLink = dynamic_cast<scb::PultTabloAbstractButton*>(pultTabloScheme->getActiveDevice(device))) == nullptr)
		return false;

	return this->initializeGeometry();
}

void PultTabloButton::setPosition(float x, float y, float z)
{
	if (this->isCompleted)
		return;
	this->x = x;
	this->y = y;
	this->z = z;
}

void PultTabloButton::setDirection(float dirX, float dirY, float dirZ)
{
	if (this->isCompleted)
		return;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

bool PultTabloButton::initializeGeometry()
{
	auto color = this->buttonLink->getColor();
	this->diffuseColor = this->getD3dColor(color);
	this->specularColor = this->getD3dColor(color);
	this->specularColor += XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f);
	XMVectorClamp(this->specularColor, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertexBuffers.push_back(PultTabloButton::mainVB);
	this->indexBuffers.push_back(PultTabloButton::mainIB);
	this->vertexShaders.push_back(PultTabloButton::mainVS);
	this->pixelShaders.push_back(PultTabloButton::mainPS);

	this->vertexBuffers.push_back(PultTabloButton::plateVB);
	this->indexBuffers.push_back(PultTabloButton::plateIB);
	this->vertexShaders.push_back(PultTabloButton::mainVS);
	this->pixelShaders.push_back(PultTabloButton::mainPS);

	return true;
}

void PultTabloButton::render()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX matrixSpin = XMMatrixIdentity();
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX matrixTranslate;

	GraphicsServer* server = GraphicsServer::getInstance();

	int vertexShader, pixelShader;

	matrixTranslate = XMMatrixTranslation(this->x, this->y - 0.8f * this->buttonLink->getPressPosition(), this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[0];
	pixelShader = this->pixelShaders[0];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, this->diffuseColor);
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, this->specularColor);
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[0], this->vertexBuffers[0]);

	matrixTranslate = XMMatrixTranslation(this->x, this->y, this->z);
	this->worldMatrix = matrixSpin * matrixTranslate;

	vertexShader = this->vertexShaders[1];
	pixelShader = this->pixelShaders[1];

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, XMFLOAT4(0.6f, 0.6f, 0.9f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f));
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[1], this->vertexBuffers[1]);
}

