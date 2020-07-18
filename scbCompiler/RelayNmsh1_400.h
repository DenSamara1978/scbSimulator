#pragma once

#include "SchemeRelay.h"

class RelayNmsh1_400 : public SchemeRelay
{
public:
	RelayNmsh1_400(const wstring& name, bool plugable);
	virtual ~RelayNmsh1_400() override;

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
