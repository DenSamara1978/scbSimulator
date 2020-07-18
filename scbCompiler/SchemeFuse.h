#pragma once

#include "SchemeEquipment.h"

class SchemeFuse : public SchemeEquipment
{
public:
	enum class PowerClass { No = 0, RPB, PHKS, PHS, OHS, P, M, KSH, SH, SHM, PHL, OHL };

	SchemeFuse(const wstring& name);

	virtual int setNominal(const wstring& nominal) override;
	virtual int setUnitOfNominal(const wstring& unit) override;
	virtual int setPowerClass(const wstring& powerClass) override;
	virtual int fixDescription() override;

private:
	float maxCurrent;
	PowerClass powerClass;

};
