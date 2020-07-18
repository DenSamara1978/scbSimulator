#pragma once

#include "SchemeRelay.h"

class RelayPpr3_5000 : public SchemeRelay
{
public:
	RelayPpr3_5000(const wstring& name);
	virtual ~RelayPpr3_5000() override;

	virtual int fixDescription() override;
};
