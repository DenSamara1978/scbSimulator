#pragma once

#include "scbSchemeObject.h"

class scbSchemeStatus : public scbSchemeObject
{
	bool m_IsDefaultSetting;

public:
	scbSchemeStatus (const wstring& name);
	virtual ~scbSchemeStatus () override;

	virtual int FixDescription () override;
	virtual const ObjectType GetObjectType () const override;

	virtual int DefaultSettingStatus () override;
};

