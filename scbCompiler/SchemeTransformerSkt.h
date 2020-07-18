#pragma once

#include "SchemeEquipment.h"

class SchemeTransformerSkt : public SchemeEquipment
{
public:
	SchemeTransformerSkt(const wstring& name);

	virtual int setJumper(const wstring& jumper);
	virtual int fixDescription();
};
