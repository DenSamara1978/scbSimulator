#pragma once

#include "SchemeRelay.h"

class RelayPmpush_150_150 : public SchemeRelay
{
public:
	RelayPmpush_150_150(const wstring& name, bool plugable);
	virtual ~RelayPmpush_150_150() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;
};
