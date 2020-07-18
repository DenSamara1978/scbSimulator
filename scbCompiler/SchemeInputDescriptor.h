#pragma once

#include "ComplexName.h"

class SchemeInputDescriptor
{
public:
	enum class Type { FreeInput, GroupInput, Input };

	SchemeInputDescriptor(const ComplexName& descriptor, Type type);
	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;
	bool checkDescriptor(const ComplexName& descriptor, Type type) const;

private:
	Type type;
	ComplexName descriptor;

};

inline SchemeInputDescriptor::SchemeInputDescriptor(const ComplexName& descriptor, Type type) :
	descriptor(descriptor),
	type(type)
{
}

inline ComplexName& SchemeInputDescriptor::getDescriptor()
{
	return this->descriptor;
}

inline const ComplexName& SchemeInputDescriptor::getDescriptor() const
{
	return this->descriptor;
}

inline bool SchemeInputDescriptor::checkDescriptor(const ComplexName& descriptor, Type type) const
{
	return ((this->descriptor.isFullyEqual(descriptor)) and (this->type == type));
}
