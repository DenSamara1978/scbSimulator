#pragma once

#include <vector>
#include <string>
#include "OutputStream.h"

using std::wstring;
using std::vector;

namespace scb
{

	class AbstractSchemeDevice;

	class AbstractScheme
	{
	public:
		AbstractScheme(const wstring& name);
		virtual ~AbstractScheme();

		bool isA(const wstring& name) const;

		void setDeviceCount(int count);
		int getDeviceCount() const;
		AbstractSchemeDevice* getDevice(int index) const;
		virtual void mapInputOutput(int outputIndex, int inputBit, int outputBit);
		virtual void setOutput(int index, const wstring& name, int block = -1);

		virtual void initialize() abstract;
		virtual void recalculate() abstract;
		virtual void setStatusBit(int bit) abstract;
		virtual void resetStatusBit(int bit) abstract;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) abstract;

		void markToRecalculate();

	protected:
		// Устройства, принадлежащие этой схеме
		vector<AbstractSchemeDevice*> devices;

		void markRecalculated();
		bool isNotMarkedToRecalculate() const;

	private:
		wstring name;
		bool markedToRecalculate;
	};

	inline AbstractScheme::AbstractScheme(const wstring& name) :
		name(name),
		markedToRecalculate(false)
	{
	}

	inline bool AbstractScheme::isA(const wstring& name) const
	{
		return this->name == name;
	}

	inline int AbstractScheme::getDeviceCount() const
	{
		return static_cast<int> (this->devices.size ());
	}

	inline AbstractSchemeDevice* AbstractScheme::getDevice(int index) const
	{
		return ((index >= 0) && (index < static_cast<int>(this->devices.size ()))) ? this->devices[index] : nullptr;
	}

	inline void AbstractScheme::markRecalculated()
	{
		this->markedToRecalculate = false;
	}

	inline bool AbstractScheme::isNotMarkedToRecalculate() const
	{
		return !this->markedToRecalculate;
	}

}
