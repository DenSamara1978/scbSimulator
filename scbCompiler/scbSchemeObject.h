#pragma once

#include <string>
#include <vector>
#include <utility>

#include "scbComplexName.h"
#include "scbSchemeConditionObject.h"
#include "scbDescription.h"

using std::wstring;
using std::vector;
using std::pair;

class scbSchemeObject : public scbSchemeConditionObject
{
protected:
	wstring m_Name;
	int m_Block;
	scbDescription::DeviceCase m_Case;
	wstring m_Location;
	int m_Placement;
	vector<wstring> m_ObjectNames;

public:
	enum class ObjectType { No, Block, Relay, Equipment, Variable, Status, Cross, Line, Input, Output };

	scbSchemeObject ( const wstring& name );
	virtual ~scbSchemeObject ();

    virtual int SetDescriptor ( const scbComplexName& descriptor );
    virtual int SetBlock ( int id );
	virtual int SetLocation ( const wstring& location );
	virtual int SetPlacement ( int id, scbDescription::PlacementType pl_type );
	virtual int SetJumper ( const wstring& jumper );
    virtual int SetOrder ( int order );
    virtual int SetCable ( const wstring& cable );
    virtual int SetContact ( const wstring& contact );
    virtual int SetCount ( int count );
    virtual int SetNominal ( const wstring& nominal );
    virtual int SetUnitOfNominal ( const wstring& unit );
    virtual int SetPowerClass ( const wstring& power_class );
    virtual int SetRequirement ( int req );
	virtual int SetRequirementFrom ( int from );
	virtual int SetRequirementTo ( int to );
	virtual int DefaultSettingStatus ();

	virtual bool CheckLocation ( int block, int placement, const wstring& locaation ) const;

		/* ¬озврат 
        0 - ќк, 
        1 - неполный набор перемычек, 
        2 - несовместимый набор перемычек 
        3 - отсутствует номинал
        4 - отсутствует класс питани€
        5 - отсутствует наименование
        */
	virtual int FixDescription () abstract;

	virtual int SetTypeName ( const wstring& name );
	virtual const wstring GetTypeName () const;

	void AddNewObjectName ( const wstring& name );
	int GetObjectNamesCount () const;

	const wstring& GetName () const;
	virtual const ObjectType GetObjectType () const abstract;
};

inline const wstring& scbSchemeObject::GetName () const
{
	return this->m_Name;
}

inline void scbSchemeObject::AddNewObjectName ( const wstring& name )
{
	this->m_ObjectNames.emplace_back ( name );
}

inline int scbSchemeObject::GetObjectNamesCount () const
{
	return this->m_ObjectNames.size ();
}