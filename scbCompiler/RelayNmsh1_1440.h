#pragma once

#include "SchemeRelay.h"

class RelayNmsh1_1440 : public SchemeRelay
{
public:
	RelayNmsh1_1440(const wstring& name, bool plugable);
	virtual ~RelayNmsh1_1440() override;

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
