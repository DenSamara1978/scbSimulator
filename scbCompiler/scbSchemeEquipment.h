#pragma once

#include "scbSchemeObject.h"

class scbSchemeEquipment : public scbSchemeObject
{
protected:
    wstring m_TypeName;

public:
	scbSchemeEquipment ( const wstring& name );
	virtual ~scbSchemeEquipment () override;

	virtual int SetBlock ( int id ) override;
	virtual int SetLocation ( const wstring& location ) override;
	virtual int SetPlacement ( int id, scbDescription::PlacementType pl_type ) override;
	virtual bool CheckLocation ( int block, int placement, const wstring& location ) const override;

	virtual const ObjectType GetObjectType () const override;
    virtual const wstring GetTypeName () const override;
};
