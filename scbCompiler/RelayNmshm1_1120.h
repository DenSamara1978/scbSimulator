#pragma once

#include "SchemeRelay.h"

class RelayNmshm1_1120 : public SchemeRelay
{
public:
	RelayNmshm1_1120(const wstring& name, bool plugable);
	virtual ~RelayNmshm1_1120() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
