#pragma once

#include <vector>
#include <string>
#include "OutputStream.h"
#include <Windows.h>

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
		wstring getName() const;

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

		void markToDynamicSensitivesRecalculating();
		void markToFullRecalculating();

		unsigned long long getAverageWorkingTime() const;

	protected:
		// Устройства, принадлежащие этой схеме
		vector<AbstractSchemeDevice*> devices;

		void markRecalculated();
		bool isMarkedToDynamicSensitivesRecalculating() const;
		bool isMarkedToFullRecalculating() const;
		bool isNotMarkedToRecalculate() const;

		unsigned long long getDiffTime(const LARGE_INTEGER& start, const LARGE_INTEGER& end) const;
		vector<unsigned long long> workingTimes;

	private:
		wstring name;

		// Глубина расчета: 0 - нет, 1 - только дин.чувствительности, 2 - полный расчет
		int depthOfRecalculating;
	};

	inline AbstractScheme::AbstractScheme(const wstring& name) :
		name(name),
		depthOfRecalculating(0)
	{
	}

	inline bool AbstractScheme::isA(const wstring& name) const
	{
		return this->name == name;
	}

	inline wstring AbstractScheme::getName() const
	{
		return this->name;
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
		this->depthOfRecalculating = 0;
	}

	inline bool AbstractScheme::isMarkedToDynamicSensitivesRecalculating() const
	{
		return (this->depthOfRecalculating > 0);
	}

	inline bool AbstractScheme::isMarkedToFullRecalculating() const
	{
		return (this->depthOfRecalculating == 2);
	}

	inline bool AbstractScheme::isNotMarkedToRecalculate() const
	{
		return (this->depthOfRecalculating == 0);
	}

	inline unsigned long long AbstractScheme::getDiffTime(const LARGE_INTEGER& start, const LARGE_INTEGER& end) const
	{
		return end.QuadPart - start.QuadPart;
	}

	inline unsigned long long AbstractScheme::getAverageWorkingTime() const
	{
		int count = 0;
		unsigned long long generalTime = 0L;
		for (auto& time : this->workingTimes)
		{
			++count;
			generalTime += time;
		}
		return (count != 0 ) ? generalTime / count : 0;
	}

}
