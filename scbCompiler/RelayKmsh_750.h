#pragma once

#include "SchemeRelay.h"

class RelayKmsh_750 : public SchemeRelay
{
public:
	RelayKmsh_750(const wstring& name);
	virtual ~RelayKmsh_750() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
