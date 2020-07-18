#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "ComplexName.h"

using std::wstring;
using std::vector;
using std::tuple;

class SchemeGrantingRequirement
{
public:
	enum class Type { Source, Transit };

	SchemeGrantingRequirement(const wstring& name);
	SchemeGrantingRequirement(int requestedReq);
	const wstring& getName() const;

	void setMaxRequesting(int num);
	int getMaxRequesting() const;
	int addRequirementName(const ComplexName& descriptor);
	bool checkRequirementNames(const ComplexName& descriptor) const;
	int sourceSetCount(int count);
	void sourceNewRecord();
	int sourceSetFrom(int from);
	int sourceSetTo(int to);
	int sourceAddOutput(int id);
	int sourceFixRecord();

	bool isSourceEnable() const;

	int getLinkedRequestedRequirement() const;

private:
	wstring sourceName; // ��������� ��� ����������� ��� Source
	Type type;

	vector<ComplexName> requirementNames; // �����, ��� �������� ����������� ����� ������
	vector<tuple<int, int, vector<int>>> sourceRecords; // ������ ��� Source - "��", "��", ["������ �����"]
	int sourceCount; // ���������� ����������� �������, ��� Source
	int maxRequesting; // ����������� ����� ������� ��� Source

	int requestedRequirement; // ������ ��������� ��� Transit

};

inline SchemeGrantingRequirement::SchemeGrantingRequirement(const wstring& name) :
	sourceName(name),
	type(Type::Source),
	sourceCount(0),
	maxRequesting(0),
	requestedRequirement(-1)
{
}

inline SchemeGrantingRequirement::SchemeGrantingRequirement(int requestedReq) :
	type(Type::Transit),
	sourceCount(0),
	maxRequesting(0),
	requestedRequirement(requestedReq)
{
}

inline const wstring& SchemeGrantingRequirement::getName() const
{
	return this->sourceName;
}

inline void SchemeGrantingRequirement::setMaxRequesting(int num)
{
	this->maxRequesting = num;
}

inline int SchemeGrantingRequirement::getMaxRequesting() const
{
	return this->maxRequesting;
}

inline bool SchemeGrantingRequirement::isSourceEnable() const
{
	return (this->sourceCount != 0);
}

inline int SchemeGrantingRequirement::getLinkedRequestedRequirement() const
{
	return this->requestedRequirement;
}
