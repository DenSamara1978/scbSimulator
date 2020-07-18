#pragma once

#include "SchemeRelay.h"

class RelayNmshm2_3000 : public SchemeRelay
{
public:
	RelayNmshm2_3000(const wstring& name);
	virtual ~RelayNmshm2_3000() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
