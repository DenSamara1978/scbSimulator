#pragma once

#include <vector>
#include <string>
#include <emmintrin.h>
#include <immintrin.h>
#include "..\time\Timer.h"

using std::wstring;
using std::vector;

namespace scb
{

	class AbstractSchemeDevice;

	union OutputStream
	{
		unsigned long mask[8];
		__m128i sseMask[2];
		__m256i avxMask;
	};

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
		void markRecalculated();
		bool isNotMarkedToRecalculate() const;

	protected:
		// Устройства, принадлежащие этой схеме
		vector<AbstractSchemeDevice*> devices;

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

	inline void AbstractScheme::markToRecalculate()
	{
		if (!this->markedToRecalculate)
			time::Timer::getInstance()->addSchemeToRecalculate(this);
		this->markedToRecalculate = true;
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
