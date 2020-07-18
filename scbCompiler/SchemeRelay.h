#pragma once

#include "SchemeObject.h"

class SchemeRelay : public SchemeObject
{
protected:
	bool isPlugable;
	wstring typeName;

public:
	SchemeRelay(const wstring& name);
	virtual ~SchemeRelay() override;

	virtual int setBlock(int id) override;
	virtual int setLocation(const wstring& location) override;
	virtual int setPlacement(int id, Description::PlacementType placementType) override;
	virtual const ObjectType getObjectType() const override;
	virtual bool checkLocation(int block, int placement, const wstring& location) const override;

	virtual const wstring getTypeName() const override;
};