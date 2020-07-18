#pragma once

#include <string>
#include <array>
#include "SchemeObject.h"

using std::wstring;
using std::array;

class SchemeCross : public SchemeObject
{
public:
	SchemeCross(const wstring& name);
	virtual ~SchemeCross() override;

	virtual int setLocation(const wstring& location) override;
	virtual int setPlacement(int id, Description::PlacementType placementType) override;
	virtual int setOrder(int order) override;
	virtual int setCable(const wstring& cable) override;
	virtual int setContact(const wstring& contact) override;
	virtual int setCount(int count) override;

	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;

private:
	int order;
	wstring cable;
	array<int, 8> contacts;
	int count;

};




