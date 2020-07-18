#pragma once

#include "SchemeEquipment.h"

class SchemeResistor : public SchemeEquipment
{
public:
	enum class Type { MLT_1, MLT_2, PEV_25, PEV_50 };

	SchemeResistor(const wstring& name, Type type);

	virtual int setNominal(const wstring& nominal) override;
	virtual int setUnitOfNominal(const wstring& unit) override;
	virtual int fixDescription() override;

private:
	int resistance;
	Type type;

};
