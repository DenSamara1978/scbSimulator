#include "VertexDeclaration.h"
#include "GraphicsServer.h"
#include "..\stdafx.h"

using namespace graphics;

VertexDeclaration::VertexDeclaration(const wstring& declarationName)
{
	this->positionOffset = -1;
	this->normalOffset = -1;
	this->diffuseColorOffset = -1;
	this->specularColorOffset = -1;
	this->emissiveColorOffset = -1;
	this->declarationName = declarationName;
	size_t descriptorCount = this->declarationName.size();
	int offset = 0;
	this->args.clear();
	Argument arg;
	for (size_t i = 0; i < descriptorCount; i++)
	{
		switch(this->declarationName[i])
		{
			case L'P':
				arg.type = Type::Position;
				arg.size = 12;
				arg.offset = offset;
				this->positionOffset = offset;
				offset += 12;
				break;
			case L'N':
				arg.type = Type::Normal;
				arg.size = 12;
				arg.offset = offset;
				this->normalOffset = offset;
				offset += 12;
				break;
			case L'D':
				arg.type = Type::DiffuseColor;
				arg.size = 16;
				arg.offset = offset;
				this->diffuseColorOffset = offset;
				offset += 16;
				break;
			case L'S':
				arg.type = Type::SpecularColor;
				arg.size = 16;
				arg.offset = offset;
				this->specularColorOffset = offset;
				offset += 16;
				break;
			case L'E':
				arg.type = Type::EmissiveColor;
				arg.size = 16;
				arg.offset = offset;
				this->emissiveColorOffset = offset;
				offset += 16;
				break;
			default:
				return;
				break;
		}
		this->args.push_back(arg);
	}
	this->vertexSize = offset;
};

VertexDeclaration::~VertexDeclaration()
{
}


