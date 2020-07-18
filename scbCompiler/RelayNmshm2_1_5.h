#pragma once

#include "SchemeRelay.h"

class RelayNmshm2_1_5 : public SchemeRelay
{
public:
	RelayNmshm2_1_5(const wstring& name, bool plugable);
	virtual ~RelayNmshm2_1_5() override;

	virtual int fixDescription() override;
};
