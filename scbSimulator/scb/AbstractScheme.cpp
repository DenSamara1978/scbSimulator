#include "AbstractScheme.h"
#include "SchemeOutput.h"
#include "SchemeServer.h"

using namespace scb;

AbstractScheme::~AbstractScheme()
{
	if (this->markedToRecalculate)
	{
		this->markedToRecalculate = false;
		SchemeServer::getInstance()->deleteSchemeToRecalculate(this);
	}
	for (auto& ptr : this->devices)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
}

void AbstractScheme::setDeviceCount(int count)
{
	for (auto& ptr : this->devices)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	this->devices.resize(count , nullptr);
}

void AbstractScheme::setOutput(int index, const wstring& name, int block)
{
	if (( index < 0) or ( index >= static_cast<int>(this->devices.size()))) return;
	if (this->devices[index] != nullptr) return;

	this->devices[index] = new SchemeOutput(this, name, block);
}

void AbstractScheme::mapInputOutput ( int outputIndex, int inputBit, int outputBit)
{
	bool inRange = (outputIndex >= 0) and (outputIndex < static_cast<int>(this->devices.size ()));
	if ( inRange and ( this->devices[outputIndex] != nullptr))
		this->devices[outputIndex]->mapInputOutput(inputBit, outputBit);
}

void AbstractScheme::markToRecalculate()
{
	if (!this->markedToRecalculate)
	{
		SchemeServer::getInstance()->addSchemeToRecalculate(this);
		this->markedToRecalculate = true;
	}
}
