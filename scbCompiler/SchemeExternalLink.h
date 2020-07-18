#pragma once

#include <vector>
#include "ComplexName.h"
#include "SchemeConditionObject.h"

using std::vector;

class SchemeExternalLink : public SchemeConditionObject
{
public:
	SchemeExternalLink();

	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;
	void setNecesserily();
	pair<int, int> setDescriptionTag(const wstring& name);
	int getDescriptionTag() const;

	// Проверяет наличие описателя в списке беспараметрических условий
	bool checkPresenceInConditionsAndDescription(int id) const;

private:
	ComplexName descriptor;
	bool isNecesserily;
	int descriptionTag;

};

inline SchemeExternalLink::SchemeExternalLink() :
	isNecesserily(false),
	descriptionTag(-1)
{
}

inline ComplexName& SchemeExternalLink::getDescriptor()
{
	return this->descriptor;
}

inline const ComplexName& SchemeExternalLink::getDescriptor() const
{
	return this->descriptor;
}

inline void SchemeExternalLink::setNecesserily()
{
	this->isNecesserily = true;
}

inline int SchemeExternalLink::getDescriptionTag() const
{
	return this->descriptionTag;
}
