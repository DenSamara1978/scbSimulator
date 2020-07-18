#pragma once

#include "SchemeRelay.h"

class RelayNmsh4_3 : public SchemeRelay
{
public:
	RelayNmsh4_3(const wstring& name, bool plugable);
	virtual ~RelayNmsh4_3() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
