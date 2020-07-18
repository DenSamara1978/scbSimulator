#pragma once

#include "SchemeEquipment.h"

class SchemeRheostat : public SchemeEquipment
{
public:
	SchemeRheostat(const wstring& name);

	virtual int setNominal(const wstring& nominal) override;
	virtual int setUnitOfNominal(const wstring& unit) override;
	virtual int fixDescription() override;

private:
	int resistance;

};
