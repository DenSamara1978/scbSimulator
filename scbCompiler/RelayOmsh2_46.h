#pragma once

#include "SchemeRelay.h"

class RelayOmsh2_46 : public SchemeRelay
{
public:
	RelayOmsh2_46(const wstring& name, bool plugable);
	virtual ~RelayOmsh2_46() override;

	virtual int fixDescription() override;
};
