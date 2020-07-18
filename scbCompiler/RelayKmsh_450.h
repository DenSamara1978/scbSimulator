#pragma once

#include "SchemeRelay.h"

class RelayKmsh_450 : public SchemeRelay
{
public:
	RelayKmsh_450(const wstring& name, bool plugable);
	virtual ~RelayKmsh_450() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
