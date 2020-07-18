#pragma once

#include "SchemeEquipment.h"

class SchemeTransformerSt4 : public SchemeEquipment
{
public:
	enum class Type { ST4A, ST4M, ST4MP, ST4G };

	SchemeTransformerSt4(const wstring& name, Type type);

	virtual int setJumper(const wstring& jumper);
	virtual int fixDescription();

private:
	Type type;

};
