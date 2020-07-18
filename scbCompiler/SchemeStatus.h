#pragma once

#include "SchemeObject.h"

class SchemeStatus : public SchemeObject
{
public:
	SchemeStatus(const wstring& name);
	virtual ~SchemeStatus() override;

	virtual int fixDescription() override;
	virtual const ObjectType getObjectType() const override;

	virtual int defaultSettingStatus() override;

private:
	bool isDefaultSetting;

};

