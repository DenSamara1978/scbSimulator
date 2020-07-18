#pragma once

#include "SchemeEquipment.h"

class SchemeDiode : public SchemeEquipment
{
public:
	enum class Type { D226B };

	SchemeDiode(const wstring& name, Type type);

	virtual int fixDescription() override;

private:
	Type type;

};
