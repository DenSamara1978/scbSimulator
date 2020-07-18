#pragma once

#include "SchemeEquipment.h"

class SchemeTransformerSt5 : public SchemeEquipment
{
public:
	enum class Type { ST5A, ST5M, ST5MP, ST5G };

	SchemeTransformerSt5(const wstring& name, Type type);

	virtual int setJumper(const wstring& jumper);
	virtual int fixDescription();

private:
	Type type;

};
