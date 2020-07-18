#pragma once

#include "SchemeRelay.h"

class RelayKdr1m_120 : public SchemeRelay
{
public:
	RelayKdr1m_120(const wstring& name);
	virtual ~RelayKdr1m_120() override;

	virtual int fixDescription() override;
};
