#pragma once

#include "SchemeRelay.h"

class RelayNmshm1_11 : public SchemeRelay
{
public:
	RelayNmshm1_11(const wstring& name, bool plugable);
	virtual ~RelayNmshm1_11() override;

	virtual int fixDescription() override;
};
