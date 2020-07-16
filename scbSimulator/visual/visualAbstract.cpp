#include "..\stdafx.h"
#include "VisualAbstract.h"
#include "..\graphics\GraphicsServer.h"

using namespace visual;

VisualAbstract::VisualAbstract() :
	isCompleted(false)
{
	this->worldMatrix = XMMatrixIdentity();
}

VisualAbstract::~VisualAbstract()
{
}

