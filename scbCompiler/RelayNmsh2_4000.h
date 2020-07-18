#pragma once

#include "SchemeRelay.h"

class RelayNmsh2_4000 : public SchemeRelay
{
public:
	RelayNmsh2_4000(const wstring& name, bool plugable);
	virtual ~RelayNmsh2_4000() override;

	virtual int setJumper(const wstring& jumper) override;
	virtual int setRequirement(int req) override;
	virtual int setRequirementFrom(int from) override;
	virtual int setRequirementTo(int to) override;
	virtual int fixDescription() override;

private:
	int requirementId;
	int requirementFrom;
	int requirementTo;

};
