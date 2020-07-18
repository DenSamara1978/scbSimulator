#pragma once

#include "SchemeEquipment.h"

class SchemeCapacitor : public SchemeEquipment
{
public:
	enum class Type { KEG_1_30V, KEG_2_30V, MBGCH_1_1_250V, MBGCH_1_2A_250V, EGC_30V };

	SchemeCapacitor(const wstring& name, Type type);

	virtual int setNominal(const wstring& nominal) override;
	virtual int setUnitOfNominal(const wstring& unit) override;
	virtual int fixDescription() override;

private:
	int capacity;
	Type type;

};
