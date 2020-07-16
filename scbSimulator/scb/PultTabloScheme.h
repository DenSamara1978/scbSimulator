#pragma once

#include <vector>
#include <string>
#include "AbstractScheme.h"
#include "..\util\color.h"
#include "..\util\range.h"

using std::wstring;
using std::vector;

using util::Color;
using util::inRange;

namespace scb
{

	class SchemeOutput;
	class PultTabloActiveDevice;
	class PultTabloLampGroup;

	class PultTabloScheme : public AbstractScheme
	{
	public:
		PultTabloScheme(const wstring& name);
		virtual ~PultTabloScheme();

		void setDeviceCount(int pultWidth, int outputs, int activeDevs, int passiveDevs, int lampGroups);

		size_t getActiveDeviceCount() const;
		size_t getPassiveDeviceCount() const;
		size_t getLampGroupCount() const;

		PultTabloActiveDevice* getActiveDevice(int index) const;
		AbstractSchemeDevice* getPassiveDevice(int index) const;
		PultTabloLampGroup* getLampGroup(int index) const;

		virtual void setOutput(int index, const wstring& name, int block) override;
		void setBell(int index, int continuouslyBit, int impulseBit);
		void setAmpermeter(int index, int startBit);
		void setButtonKmd(int index, Color color, int onBit);
		void setButtonKmd(int index, Color color, int onBit, int offBit);
		void setButtonKmdf(int index, Color color, int onBit);
		void setButtonKmdf(int index, Color color, int onBit, int offBit);
		void setButtonSchm1m(int index, Color color, int onBit, int offBit);
		void setCommutatorKmd(int index, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		void setCommutatorKmdn(int index, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);
		void setCommutatorKmt(int index, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		void setCommutatorKmtn(int index, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);

		virtual void initialize() override;
		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) override;

	private:
		bool checkForActiveDevice(int index) const;
		bool checkForPassiveDevice(int index) const;

		vector<OutputStream> pultStatus; // 256-битные структуры состояния аппаратов управления

		OutputStream tabloStatus; // состояние пассивных элементов

		vector<vector<int>> outputOverBlocks;
		vector<PultTabloActiveDevice*> activeDevices;
		vector<AbstractSchemeDevice*> passiveDevices;
		vector<PultTabloLampGroup*> lampGroups;
	};

	inline size_t PultTabloScheme::getActiveDeviceCount() const
	{
		return static_cast<int>(this->activeDevices.size());
	}

	inline size_t PultTabloScheme::getPassiveDeviceCount() const
	{
		return static_cast<int>(this->passiveDevices.size());
	}

	inline size_t PultTabloScheme::getLampGroupCount() const
	{
		return static_cast<int>(this->lampGroups.size());
	}

	inline PultTabloActiveDevice* PultTabloScheme::getActiveDevice(int index) const
	{
		auto isInRange = inRange(index, this->activeDevices.size());
		return isInRange ? this->activeDevices[index] : nullptr;
	}

	inline AbstractSchemeDevice* PultTabloScheme::getPassiveDevice(int index) const
	{
		auto isInRange = inRange(index, this->passiveDevices.size());
		return isInRange ? this->passiveDevices[index] : nullptr;
	}

	inline PultTabloLampGroup* PultTabloScheme::getLampGroup(int index) const
	{
		auto isInRange = inRange(index, this->lampGroups.size());
		return isInRange ? this->lampGroups[index] : nullptr;
	}

	inline bool PultTabloScheme::checkForActiveDevice(int index) const
	{
		auto isInRange = inRange(index, this->activeDevices.size());
		if (!isInRange)
			return false;
		return (this->activeDevices[index] == nullptr);
	}

	inline bool PultTabloScheme::checkForPassiveDevice(int index) const
	{
		auto isInRange = inRange(index, this->passiveDevices.size());
		if (!isInRange)
			return false;
		return (this->passiveDevices[index] == nullptr);
	}
}