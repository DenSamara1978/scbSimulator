#pragma once

#include "SchemeRelay.h"

class RelayKdr1m_280 : public SchemeRelay
{
public:
	RelayKdr1m_280(const wstring& name);
	virtual ~RelayKdr1m_280() override;

	virtual int fixDescription() override;
};
