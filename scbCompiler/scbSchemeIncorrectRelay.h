#pragma once

#include "scbSchemeRelay.h"

class scbSchemeIncorrectRelay : public scbSchemeRelay
{
public:
	scbSchemeIncorrectRelay ( const wstring& name );
	virtual ~scbSchemeIncorrectRelay () override;

	virtual int FixDescription () override;
	virtual const wstring GetTypeName () const override;
};

inline scbSchemeIncorrectRelay::scbSchemeIncorrectRelay ( const wstring& name ) :
	scbSchemeRelay ( name )
{

}

inline const wstring scbSchemeIncorrectRelay::GetTypeName () const
{
	return this->m_IsPlugable ? L"?" : L"?";
}
