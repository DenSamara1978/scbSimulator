#pragma once

#include "scbSchemeObject.h"

class scbSchemeBlock : public scbSchemeObject
{
protected:
	int m_TypeId;

public:
	scbSchemeBlock (const wstring& name);
	virtual ~scbSchemeBlock () override;

	virtual int SetPlacement ( int id, scbDescription::PlacementType pl_type ) override;
	virtual int SetLocation ( const wstring& location ) override;
	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override; 
	virtual bool CheckLocation ( int block, int placement, const wstring& locaation ) const override;

	int SetTypeName ( const wstring& name );
//	const wstring GetTypeName () const;
};