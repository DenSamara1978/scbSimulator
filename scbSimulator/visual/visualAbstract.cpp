#include "..\stdafx.h"
#include "visualAbstract.h"
#include "..\graphics\graphServer.h"
#include "..\graphics\graphVertexShader.h"

visualAbstract::visualAbstract () :
	m_IsCompleted ( false )
{
	this->m_WorldMatrix = XMMatrixIdentity ();
}

visualAbstract::~visualAbstract ()
{
}

