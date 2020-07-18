#pragma once

#include "SchemeEquipment.h"

class SchemeTimeBlock : public SchemeEquipment
{
public:
	enum class Type { BVMSH, BVV_M, BVV_C };

	SchemeTimeBlock(const wstring& name, Type type);

	virtual int setJumper(const wstring& jumper) override;
	virtual int fixDescription() override;

private:
	Type type;

};
