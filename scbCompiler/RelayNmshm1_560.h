#pragma once

#include "SchemeRelay.h"

class RelayNmshm1_560 : public SchemeRelay
{
public:
	RelayNmshm1_560(const wstring& name, bool plugable);
	virtual ~RelayNmshm1_560() override;

	virtual int fixDescription() override;
};
