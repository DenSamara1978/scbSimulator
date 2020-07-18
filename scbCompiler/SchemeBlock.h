#pragma once

#include "SchemeObject.h"

class SchemeBlock : public SchemeObject
{
public:
	SchemeBlock(const wstring& name);
	virtual ~SchemeBlock() override;

	virtual int setPlacement(int id, Description::PlacementType placementTtype) override;
	virtual int setLocation(const wstring& location) override;
	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;
	virtual bool checkLocation(int block, int placement, const wstring& location) const override;

	int setTypeName(const wstring& name);
	//	const wstring GetTypeName () const;

protected:
	int typeId;

};