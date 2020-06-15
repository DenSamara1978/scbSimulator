#include "graphVertexDeclaration.h"
#include "graphServer.h"
#include "..\stdafx.h"

graphVertexDeclaration::graphVertexDeclaration ( const wstring& vDecl )
{
	this->m_PositionOffset = -1;
	this->m_NormalOffset = -1;
	this->m_DiffuseColorOffset = -1;
	this->m_SpecularColorOffset = -1;
	this->m_EmissiveColorOffset = -1;
	this->m_Declaration = vDecl;
	size_t desc_count = this->m_Declaration.size ();
	int offset = 0;
	this->m_Args.clear ();
	Argument arg;
	for ( size_t i = 0; i < desc_count; i++ )
	{
		switch ( this->m_Declaration [i] )
		{
		case L'P':
			arg.Type = Type::Position;
			arg.Size = 12;
			arg.Offset = offset;
			this->m_PositionOffset = offset;
			offset += 12;
			break;
		case L'N':
			arg.Type = Type::Normal;
			arg.Size = 12;
			arg.Offset = offset;
			this->m_NormalOffset = offset;
			offset += 12;
			break;
		case L'D':
			arg.Type = Type::DiffuseColor;
			arg.Size = 16;
			arg.Offset = offset;
			this->m_DiffuseColorOffset = offset;
			offset += 16;
			break;
		case L'S':
			arg.Type = Type::SpecularColor;
			arg.Size = 16;
			arg.Offset = offset;
			this->m_SpecularColorOffset = offset;
			offset += 16;
			break;
		case L'E':
			arg.Type = Type::EmissiveColor;
			arg.Size = 16;
			arg.Offset = offset;
			this->m_EmissiveColorOffset = offset;
			offset += 16;
			break;
		default:
			return;
			break;
		}
		this->m_Args.push_back ( arg );
	}
	this->m_VertexSize = offset;
};

graphVertexDeclaration::~graphVertexDeclaration ()
{
}


