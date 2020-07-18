#pragma once

#include "ComplexName.h"

class SchemeOutputDescriptor
{
public:
	enum class Type { Output, GroupOutput, TargetOutput, Requirement };

	SchemeOutputDescriptor(const ComplexName& descriptor, Type type);
	ComplexName& getDescriptor();
	const ComplexName& getDescriptor() const;
	bool checkDescriptor(const ComplexName& descriptor, Type type) const;

private:
	Type type;
	ComplexName descriptor;

};

inline SchemeOutputDescriptor::SchemeOutputDescriptor(const ComplexName& descriptor, Type type) :
	descriptor(descriptor),
	type(type)
{
}

inline ComplexName& SchemeOutputDescriptor::getDescriptor()
{
	return this->descriptor;
}

inline const ComplexName& SchemeOutputDescriptor::getDescriptor() const
{
	return this->descriptor;
}

inline bool SchemeOutputDescriptor::checkDescriptor(const ComplexName& descriptor, Type type) const
{
	return ((this->descriptor.isFullyEqual(descriptor)) and (this->type == type));
}
