#pragma once

#include "SchemeRelay.h"

class RelayDssh13a : public SchemeRelay
{
public:
	RelayDssh13a(const wstring& name);
	virtual ~RelayDssh13a() override;

	virtual int fixDescription() override;
};
