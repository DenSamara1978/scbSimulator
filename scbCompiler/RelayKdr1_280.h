#pragma once

#include "SchemeRelay.h"

class RelayKdr1_280 : public SchemeRelay
{
public:
	RelayKdr1_280(const wstring& name);
	virtual ~RelayKdr1_280() override;

	virtual int fixDescription() override;
};
