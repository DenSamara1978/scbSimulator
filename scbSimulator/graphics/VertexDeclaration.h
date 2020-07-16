#pragma once

#include <d3d11.h>
#include <vector>
#include <string>
#include "..\util\range.h"

using std::vector;
using std::wstring;
using util::inRange;

namespace graphics
{
	class VertexDeclaration
	{
	public:
		enum class Type
		{
			No = 0,
			Position,
			Normal,
			DiffuseColor,
			SpecularColor,
			EmissiveColor,
		};

		struct Argument
		{
			Type type;
			int offset;
			int size;
		};

		VertexDeclaration (const wstring& declarationName);
		~VertexDeclaration ();

		bool isA (const wstring& declarationName) const;

		int getVertexSize () const;
		size_t getDescriptorCount () const;

		int getPositionOffset () const;
		int getNormalOffset () const;
		int getDiffuseColorOffset () const;
		int getSpecularColorOffset () const;
		int getEmissiveColorOffset () const;

		Type getElementType (int index) const;
		int getElementOffset (int index) const;

	private:
		friend class VertexBuffer;

		int vertexSize;
		wstring declarationName;
		vector<Argument> args;

		int positionOffset;
		int normalOffset;
		int diffuseColorOffset;
		int specularColorOffset;
		int emissiveColorOffset;
	};

	inline bool VertexDeclaration::isA (const wstring& declarationName) const
	{
		return (this->declarationName == declarationName);
	}

	inline int VertexDeclaration::getVertexSize() const
	{
		return this->vertexSize;
	}

	inline int VertexDeclaration::getPositionOffset() const
	{
		return this->positionOffset;
	}

	inline int VertexDeclaration::getNormalOffset() const
	{
		return this->normalOffset;
	}

	inline int VertexDeclaration::getDiffuseColorOffset() const
	{
		return this->diffuseColorOffset;
	}

	inline int VertexDeclaration::getSpecularColorOffset() const
	{
		return this->specularColorOffset;
	}

	inline int VertexDeclaration::getEmissiveColorOffset() const
	{
		return this->emissiveColorOffset;
	}

	inline size_t VertexDeclaration::getDescriptorCount() const
	{
		return this->args.size();
	}

	inline VertexDeclaration::Type VertexDeclaration::getElementType(int index) const
	{
		return inRange (index,this->args.size()) ? this->args[index].type : VertexDeclaration::Type::No;
	}

	inline int VertexDeclaration::getElementOffset(int index) const
	{
		return inRange (index, this->args.size()) ? this->args[index].offset : 0;
	}
}