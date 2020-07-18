#pragma once

#include "SchemeRelay.h"

class RelayKdr1_200 : public SchemeRelay
{
public:
	RelayKdr1_200(const wstring& name);
	virtual ~RelayKdr1_200() override;

	virtual int fixDescription() override;
};
