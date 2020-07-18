#pragma once

#include <string>
#include <vector>

using std::wstring;
using std::vector;

class ComplexName
{
public:
	enum class ComplexNameType { Empty, Incorrect, Short, Full };

	ComplexName();
	void clear();

	int addTagName(const wstring& name);
	int addParamTagId(int id);
	int addGroupTagName(const wstring& name);

	void setSecondTag(int tag);
	int extractParamTag() const;
	bool replaceFourthTag(const wstring& name);

	ComplexNameType getType() const;
	bool isValid() const;
	bool isGroupDescriptor() const;
	bool isEqualForDescription(const ComplexName& name) const;
	bool isEqual(const ComplexName& name) const;
	bool isInclude(const ComplexName& name) const;
	bool isFullyEqual(const ComplexName& name) const;

private:

	int firstTagId;
	int secondTagId;
	int thirdTagId;
	wstring fourthTagName;

	ComplexNameType type;

};

inline ComplexName::ComplexNameType ComplexName::getType() const
{
	return this->type;
}

inline bool ComplexName::isValid() const
{
	return ((this->type != ComplexNameType::Incorrect) and (this->type != ComplexNameType::Empty));
}

inline bool ComplexName::isEqualForDescription(const ComplexName& name) const
{
	return ((this->firstTagId == name.firstTagId) and (this->secondTagId == name.secondTagId) and
		(this->type == ComplexNameType::Short) and
		((name.type == ComplexNameType::Short) or (name.type == ComplexNameType::Full)));
}

inline bool ComplexName::isGroupDescriptor() const
{
	return (this->thirdTagId >= 200'000);
}

inline void ComplexName::setSecondTag(int tag)
{
	this->secondTagId = tag;
}
