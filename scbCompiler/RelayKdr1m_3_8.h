#pragma once

#include "SchemeRelay.h"

class RelayKdr1m_3_8 : public SchemeRelay
{
public:
	RelayKdr1m_3_8(const wstring& name);
	virtual ~RelayKdr1m_3_8() override;

	virtual int fixDescription() override;
};
