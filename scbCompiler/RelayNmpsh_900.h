#pragma once

#include "SchemeRelay.h"

class RelayNmpsh_900 : public SchemeRelay
{
public:
	RelayNmpsh_900(const wstring& name);
	virtual ~RelayNmpsh_900() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
