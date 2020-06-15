#pragma once

#include "scbSchemeObject.h"

class scbSchemeRelay : public scbSchemeObject
{
protected:
	bool m_IsPlugable;
	wstring m_TypeName;

public:
	scbSchemeRelay ( const wstring& name );
	virtual ~scbSchemeRelay () override;

	virtual int SetBlock ( int id ) override;
	virtual int SetLocation ( const wstring& location ) override;
	virtual int SetPlacement ( int id, scbDescription::PlacementType pl_type ) override;
	virtual const ObjectType GetObjectType () const override;
	virtual bool CheckLocation ( int block, int placement, const wstring& locaation ) const override;

	virtual const wstring GetTypeName () const override;
};