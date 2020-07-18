#pragma once

#include "SchemeRelay.h"

class RelayNmsh3_460_400 : public SchemeRelay
{
public:
	RelayNmsh3_460_400(const wstring& name);
	virtual ~RelayNmsh3_460_400() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
