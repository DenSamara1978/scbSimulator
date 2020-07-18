#pragma once

#include "SchemeRelay.h"

class SchemeIncorrectRelay : public SchemeRelay
{
public:
	SchemeIncorrectRelay(const wstring& name);
	virtual ~SchemeIncorrectRelay() override;

	virtual int fixDescription() override;
	virtual const wstring getTypeName() const override;
};

inline SchemeIncorrectRelay::SchemeIncorrectRelay(const wstring& name) :
	SchemeRelay(name)
{

}

inline const wstring SchemeIncorrectRelay::getTypeName() const
{
	return this->isPlugable ? L"?" : L"?";
}
