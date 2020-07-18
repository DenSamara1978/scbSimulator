#include "ComplexName.h"
#include "Description.h"
#include "Manager.h"

ComplexName::ComplexName() :
	firstTagId(-1),
	secondTagId(-1),
	thirdTagId(-1),
	type(ComplexNameType::Empty)
{
}

void ComplexName::clear()
{
	this->firstTagId = -1;
	this->secondTagId = -1;
	this->thirdTagId = -1;
	this->fourthTagName.clear();
	this->type = ComplexNameType::Empty;
}

int ComplexName::addTagName(const wstring& name)
{
	int id;
	if (this->firstTagId == -1)
	{
		this->type = ComplexNameType::Incorrect;
		if ((id = Description::getTagIdByName(name)) == -1)
			return 1;
		else
		{
			this->firstTagId = id;
			return 0;
		}
	}
	else if (this->secondTagId == -1)
	{
		this->type = ComplexNameType::Incorrect;
		if ((id = Description::getTagIdByName(name)) == -1)
			return 1;
		else
		{
			this->secondTagId = id;
			return 0;
		}
	}
	else if (this->thirdTagId == -1)
	{
		if ((id = Description::getTagIdByName(name)) == -1)
		{
			this->type = ComplexNameType::Incorrect;
			return 1;
		}
		else
		{
			this->type = ComplexNameType::Short;
			this->thirdTagId = id;
			return 0;
		}
	}
	else if (this->fourthTagName.empty())
	{
		this->fourthTagName = name;
		this->type = ComplexNameType::Full;
		return 0;
	}
	else
		return -1;
}

int ComplexName::addGroupTagName(const wstring& name)
{
	if ((this->firstTagId == -1) || (this->secondTagId == -1))
		return -1;
	else if (this->thirdTagId == -1)
	{
		this->thirdTagId = Description::getGroupTag(name);
		if (this->thirdTagId == -1)
			return 1; // Неверное групповое имя
		else
			this->thirdTagId += 200'000;
		this->type = ComplexNameType::Short;
		return 0;
	}
	else
		return -1;
}

int ComplexName::addParamTagId(int id)
{
	if (this->firstTagId == -1)
		return -1;
	else if (this->secondTagId == -1)
	{
		this->secondTagId = id;
		this->type = ComplexNameType::Incorrect;
		return 0;
	}
	else if (this->thirdTagId == -1)
	{
		this->thirdTagId = id;
		this->type = ComplexNameType::Short;
		return 0;
	}
	else
		return -1;
}

int ComplexName::extractParamTag() const
{
	if ((this->secondTagId >= 0) and (this->secondTagId >= Manager::parameterNameShift))
		return this->secondTagId - Manager::parameterNameShift;
	else if ((this->thirdTagId >= 0) and (this->thirdTagId >= Manager::parameterNameShift))
		return this->thirdTagId - Manager::parameterNameShift;
	else return -1;
}

bool ComplexName::replaceFourthTag(const wstring& name)
{
	if ((this->type == ComplexNameType::Full) or (this->type == ComplexNameType::Short))
	{
		this->fourthTagName = name;
		this->type = ComplexNameType::Full;
		return true;
	}
	return false;
}

bool ComplexName::isEqual(const ComplexName& name) const
{
	return (((this->firstTagId == name.firstTagId) and (this->secondTagId == name.secondTagId) and (this->thirdTagId == name.thirdTagId) and
		(this->type == ComplexNameType::Short) and (name.type == ComplexNameType::Short)) or
		((this->type == ComplexNameType::Empty) and (name.type == ComplexNameType::Empty)));
}

bool ComplexName::isInclude(const ComplexName& name) const
{
	return  ((this->firstTagId == name.firstTagId) and (this->secondTagId == name.secondTagId) and (this->thirdTagId == name.thirdTagId) and
		(this->type == ComplexNameType::Short) and (name.type == ComplexNameType::Full));
}

bool ComplexName::isFullyEqual(const ComplexName& name) const
{
	return ((this->firstTagId == name.firstTagId) and (this->secondTagId == name.secondTagId) and
		(this->thirdTagId == name.thirdTagId) and (this->fourthTagName == name.fourthTagName) and
		(this->type == ComplexNameType::Full) and (name.type == ComplexNameType::Full));
}
