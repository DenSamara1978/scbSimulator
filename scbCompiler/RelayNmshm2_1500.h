#pragma once

#include "SchemeRelay.h"

class RelayNmshm2_1500 : public SchemeRelay
{
public:
	RelayNmshm2_1500(const wstring& name);
	virtual ~RelayNmshm2_1500() override;

	virtual int fixDescription() override;
};
