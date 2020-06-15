#pragma once

#include <d3d11.h>
#include <vector>
#include <string>

using std::vector;
using std::wstring;

class graphVertexDeclaration
{
	friend class graphVertexBuffer;

public:
	enum Type
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
		Type Type;
		int Offset;
		int Size;
	};

private:
	int m_VertexSize;
	wstring m_Declaration;
	vector<Argument> m_Args;

	int m_PositionOffset;
	int m_NormalOffset;
	int m_DiffuseColorOffset;
	int m_SpecularColorOffset;
	int m_EmissiveColorOffset;

public:
	graphVertexDeclaration ( const wstring& vDecl );
	~graphVertexDeclaration ();

	bool IsA ( const wstring& decl ) const;

	int GetVertexSize () const;
	int GetDescCount () const;

	int GetPositionOffset () const;
	int GetNormalOffset () const;
	int GetDiffuseColorOffset () const;
	int GetSpecularColorOffset () const;
	int GetEmissiveColorOffset () const;

	Type GetElementType ( int index ) const;
	int GetElementOffset ( int index ) const;
};

inline bool graphVertexDeclaration::IsA ( const wstring& decl ) const
{
	return ( this->m_Declaration == decl );
}

inline int graphVertexDeclaration::GetVertexSize () const
{
	return this->m_VertexSize;
}

inline int graphVertexDeclaration::GetPositionOffset () const
{
	return this->m_PositionOffset;
}

inline int graphVertexDeclaration::GetNormalOffset () const
{
	return this->m_NormalOffset;
}

inline int graphVertexDeclaration::GetDiffuseColorOffset () const
{
	return this->m_DiffuseColorOffset;
}

inline int graphVertexDeclaration::GetSpecularColorOffset () const
{
	return this->m_SpecularColorOffset;
}

inline int graphVertexDeclaration::GetEmissiveColorOffset () const
{
	return this->m_EmissiveColorOffset;
}

inline int graphVertexDeclaration::GetDescCount () const
{
	return static_cast<int> ( this->m_Args.size ());
}

inline graphVertexDeclaration::Type graphVertexDeclaration::GetElementType ( int index ) const
{
	return (( index < 0 ) || ( index >= static_cast<int>( this->m_Args.size ()) )) ? graphVertexDeclaration::No : this->m_Args.at ( index ).Type;
}

inline int graphVertexDeclaration::GetElementOffset ( int index ) const
{
	return ( ( index < 0 ) || ( index >= static_cast<int>( this->m_Args.size () ) ) ) ? 0 : this->m_Args.at ( index ).Offset;
}
