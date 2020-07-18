#pragma once

#include "SchemeRelay.h"

class RelayNmshm1_1000_560 : public SchemeRelay
{
public:
	RelayNmshm1_1000_560(const wstring& name, bool plugable);
	virtual ~RelayNmshm1_1000_560() override;

	virtual int fixDescription() override;
};
