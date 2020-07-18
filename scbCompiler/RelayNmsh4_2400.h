#pragma once

#include "SchemeRelay.h"

class RelayNmsh4_2400 : public SchemeRelay
{
public:
	RelayNmsh4_2400(const wstring& name, bool plugable);
	virtual ~RelayNmsh4_2400() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
