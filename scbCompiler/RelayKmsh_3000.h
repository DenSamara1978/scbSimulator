#pragma once

#include "SchemeRelay.h"

class RelayKmsh_3000 : public SchemeRelay
{
public:
	RelayKmsh_3000(const wstring& name, bool plugable);
	virtual ~RelayKmsh_3000() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
