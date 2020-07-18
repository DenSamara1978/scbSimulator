#pragma once

#include <string>
#include <vector>
#include <utility>

#include "ComplexName.h"
#include "SchemeConditionObject.h"
#include "Description.h"

using std::wstring;
using std::vector;
using std::pair;

class SchemeObject : public SchemeConditionObject
{
public:
	enum class ObjectType { No, Block, Relay, Equipment, Variable, Status, Cross, Line, Input, Output };

	SchemeObject(const wstring& name);
	virtual ~SchemeObject();

	virtual int setDescriptor(const ComplexName& descriptor);
	virtual int setBlock(int id);
	virtual int setLocation(const wstring& location);
	virtual int setPlacement(int id, Description::PlacementType placementType);
	virtual int setJumper(const wstring& jumper);
	virtual int setOrder(int order);
	virtual int setCable(const wstring& cable);
	virtual int setContact(const wstring& contact);
	virtual int setCount(int count);
	virtual int setNominal(const wstring& nominal);
	virtual int setUnitOfNominal(const wstring& unit);
	virtual int setPowerClass(const wstring& power_class);
	virtual int setRequirement(int req);
	virtual int setRequirementFrom(int from);
	virtual int setRequirementTo(int to);
	virtual int defaultSettingStatus();

	virtual bool checkLocation(int block, int placement, const wstring& location) const;

	/* ¬озврат
	0 - ќк,
	1 - неполный набор перемычек,
	2 - несовместимый набор перемычек
	3 - отсутствует номинал
	4 - отсутствует класс питани€
	5 - отсутствует наименование
	*/
	virtual int fixDescription() abstract;

	virtual int setTypeName(const wstring& name);
	virtual const wstring getTypeName() const;

	void addNewObjectName(const wstring& name);
	int getObjectNamesCount() const;

	const wstring& getName() const;
	virtual const ObjectType getObjectType() const abstract;

protected:
	wstring name;
	int block;
	Description::DeviceCase deviceCase;
	wstring location;
	int placement;
	vector<wstring> objectNames;

};

inline const wstring& SchemeObject::getName() const
{
	return this->name;
}

inline void SchemeObject::addNewObjectName(const wstring& name)
{
	this->objectNames.emplace_back(name);
}

inline int SchemeObject::getObjectNamesCount() const
{
	return static_cast<int>(this->objectNames.size());
}