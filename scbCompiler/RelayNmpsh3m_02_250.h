#pragma once

#include "SchemeRelay.h"

class RelayNmpsh3m_02_250 : public SchemeRelay
{
public:
	RelayNmpsh3m_02_250(const wstring& name, bool plugable);
	virtual ~RelayNmpsh3m_02_250() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
