#include "PultTabloCommutator.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\PultTabloAbstractCommutator.h"
#include "..\scb\PultTabloScheme.h"
#include "..\util\range.h"
#include "..\util\Color.h"

using namespace visual;

using graphics::GraphicsServer;
using graphics::Shader;

using util::Color;
using util::inRange;

int PultTabloCommutator::mainVB = -1;
int PultTabloCommutator::plateVB = -1;
int PultTabloCommutator::mainVS = -1;
int PultTabloCommutator::mainPS = -1;
int PultTabloCommutator::mainIB = -1;
int PultTabloCommutator::plateIB = -1;

bool PultTabloCommutator::initializeBuffers()
{
	GraphicsServer* server = GraphicsServer::getInstance();
	int resource = -1;

	const int nSectors = 24;
	int i;
	float angle, sine, cosine;

	int vertexBuffer = server->createVertexBuffer(L"PN", nSectors * 3 + 16, GraphicsServer::TopologyType::TriangleList);
	if (vertexBuffer == -1)
		return false;

	for (i = 0; i < nSectors; i++)
	{
		angle = 2.0f * XM_PI * i / nSectors;
		sine = sinf(angle);
		cosine = cosf(angle);
		server->fillPositionInVertexBuffer(vertexBuffer, i, cosine * 0.5f, 0.9f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i, 0.0f, 1.0f, 0.0f);
		server->fillPositionInVertexBuffer(vertexBuffer, i + nSectors, cosine * 0.5f, 0.9f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i + nSectors, cosine, 0.0f, sine);
		server->fillPositionInVertexBuffer(vertexBuffer, i + 2 * nSectors, cosine * 0.5f, -0.1f, sine * 0.5f);
		server->fillNormalInVertexBuffer(vertexBuffer, i + 2 * nSectors, cosine, 0.0f, sine);
	}

	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors, -0.2f, 0.9f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 1, -0.2f, 0.9f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 2, 0.2f, 0.9f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 3, 0.2f, 0.9f, 1.5f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 * nSectors + i, 0.0f, 1.0f, 0.0f);

	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 4, -0.2f, 0.6f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 5, -0.2f, 0.6f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 6, -0.2f, 0.9f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 7, -0.2f, 0.9f, 1.5f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 * nSectors + 4 + i, -1.0f, 0.0f, 0.0f);

	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 8, 0.2f, 0.9f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 9, 0.2f, 0.9f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 10, 0.2f, 0.6f, 0.0f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 11, 0.2f, 0.6f, 1.5f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 * nSectors + 8 + i, 1.0f, 0.0f, 0.0f);

	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 12, -0.2f, 0.9f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 13, -0.2f, 0.6f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 14, 0.2f, 0.9f, 1.5f);
	server->fillPositionInVertexBuffer(vertexBuffer, 3 * nSectors + 15, 0.2f, 0.6f, 1.5f);
	for (i = 0; i < 4; ++i)
		server->fillNormalInVertexBuffer(vertexBuffer, 3 * nSectors + 12 + i, 0.0f, 0.0f, 1.0f);

	resource = server->assignVertexBuffer(vertexBuffer);
	if (resource != -1)
		PultTabloCommutator::mainVB = resource;
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
		PultTabloCommutator::plateVB = resource;
	else
		return false;

	const int num_tris = nSectors - 2;
	const int num_indices = (nSectors - 2) * 3 + nSectors * 6;
	unsigned short indices[num_indices + 24];
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

	for (i = 0; i < 4; i++)
	{
		indices[num_indices + 6 * i + 0] = nSectors * 3 + 4 * i + 0;
		indices[num_indices + 6 * i + 1] = nSectors * 3 + 4 * i + 1;
		indices[num_indices + 6 * i + 2] = nSectors * 3 + 4 * i + 3;
		indices[num_indices + 6 * i + 3] = nSectors * 3 + 4 * i + 0;
		indices[num_indices + 6 * i + 4] = nSectors * 3 + 4 * i + 3;
		indices[num_indices + 6 * i + 5] = nSectors * 3 + 4 * i + 2;
	}

	resource = server->createIndexBuffer(num_indices + 24, indices);
	if (resource != -1)
		PultTabloCommutator::mainIB = resource;
	else
		return false;

	unsigned short indices1[] = {0, 1, 2, 2, 1, 3};
	resource = server->createIndexBuffer(6, indices1);
	if (resource != -1)
		PultTabloCommutator::plateIB = resource;
	else
		return false;

	resource = server->getVertexShaderIndexByName(L"vs");
	if (resource != -1)
		PultTabloCommutator::mainVS = resource;
	else
		return false;

	resource = server->getPixelShaderIndexByName(L"ps");
	if (resource != -1)
		PultTabloCommutator::mainPS = resource;
	else
		return false;

	return true;
}

PultTabloCommutator::PultTabloCommutator() :
	commutatorLink(nullptr),
	x(0.0f),
	y(0.0f),
	z(0.0f),
	dirX(0.0f),
	dirY(1.0f),
	dirZ(0.0f)
{
}

PultTabloCommutator::~PultTabloCommutator()
{
}

bool PultTabloCommutator::assignCommutator(scb::PultTabloScheme* pultTabloScheme, int device)
{
	if (this->isCompleted or (pultTabloScheme == nullptr))
		return false;

	auto isInRange = inRange(device, pultTabloScheme->getActiveDeviceCount());
	if (!isInRange )
		return false;

	if ((this->commutatorLink = dynamic_cast<scb::PultTabloAbstractCommutator*>(pultTabloScheme->getActiveDevice(device))) == nullptr)
		return false;

	return this->initializeGeometry();
}

void PultTabloCommutator::setPosition(float x, float y, float z)
{
	if (this->isCompleted)
		return;
	this->z = x;
	this->y = y;
	this->z = z;
}

void PultTabloCommutator::setDirection(float dirX, float dirY, float dirZ)
{
	if (this->isCompleted)
		return;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

bool PultTabloCommutator::initializeGeometry()
{
	auto color = this->commutatorLink->getColor();
	this->diffuseColor = this->getD3dColor(color);
	this->specularColor = this->getD3dColor(color);
	this->specularColor += XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f);
	XMVectorClamp(this->specularColor, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertexBuffers.push_back(PultTabloCommutator::mainVB);
	this->indexBuffers.push_back(PultTabloCommutator::mainIB);
	this->vertexShaders.push_back(PultTabloCommutator::mainVS);
	this->pixelShaders.push_back(PultTabloCommutator::mainPS);

	this->vertexBuffers.push_back(PultTabloCommutator::plateVB);
	this->indexBuffers.push_back(PultTabloCommutator::plateIB);
	this->vertexShaders.push_back(PultTabloCommutator::mainVS);
	this->pixelShaders.push_back(PultTabloCommutator::mainPS);

	return true;
}

void PultTabloCommutator::render()
{
	// Матрица-спин: вращение объекта вокруг своей оси
	XMMATRIX matrixSpin;
	// Матрица-позиция: перемещение на три единицы влево от начала координат
	XMMATRIX matrixTranslate;

	matrixSpin = XMMatrixRotationY(30.0f * XM_PI / 180.0f * this->commutatorLink->getSwitchPosition());
	matrixTranslate = XMMatrixTranslation(this->x, this->y - 0.8f * this->commutatorLink->getPressPosition(), this->z);

	GraphicsServer* server = GraphicsServer::getInstance();
	int vertexShader, pixelShader;

	vertexShader = this->vertexShaders[0];
	pixelShader = this->pixelShaders[0];

	this->worldMatrix = matrixSpin * matrixTranslate;

	server->getVertexShader(vertexShader)->setConstant(Shader::ConstantType::WorldMatrix, this->worldMatrix);

	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::DiffuseColor, this->diffuseColor);
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::SpecularColor, this->specularColor);
	server->getPixelShader(pixelShader)->setConstant(Shader::ConstantType::EmissiveColor, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	server->draw(vertexShader, pixelShader, this->indexBuffers[0], this->vertexBuffers[0]);

	matrixSpin = XMMatrixIdentity();
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

