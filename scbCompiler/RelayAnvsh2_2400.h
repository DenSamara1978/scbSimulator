#pragma once

#include "SchemeRelay.h"

class RelayAnvsh2_2400 : public SchemeRelay
{
public:
	RelayAnvsh2_2400(const wstring& name);
	virtual ~RelayAnvsh2_2400() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
