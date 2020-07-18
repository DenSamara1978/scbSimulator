#pragma once

#include "SchemeObject.h"

class SchemeEquipment : public SchemeObject
{
public:
	SchemeEquipment(const wstring& name);
	virtual ~SchemeEquipment() override;

	virtual int setBlock(int id) override;
	virtual int setLocation(const wstring& location) override;
	virtual int setPlacement(int id, Description::PlacementType placementType) override;
	virtual bool checkLocation(int block, int placement, const wstring& location) const override;

	virtual const ObjectType getObjectType() const override;
	virtual const wstring getTypeName() const override;

protected:
	wstring typeName;

};
