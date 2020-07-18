#pragma once

#include "SchemeRelay.h"

class RelayNmpsh2_400 : public SchemeRelay
{
public:
	RelayNmpsh2_400(const wstring& name);
	virtual ~RelayNmpsh2_400() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
