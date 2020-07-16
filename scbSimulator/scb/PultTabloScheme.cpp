#include "PultTabloScheme.h"
#include "PultTabloButtonKmd.h"
#include "PultTabloButtonKmdf.h"
#include "PultTabloButtonSchm1m.h"
#include "PultTabloCommutatorKmd.h"
#include "PultTabloCommutatorKmt.h"
#include "PultTabloLampGroup.h"
#include "PultTabloAmpermeter.h"
#include "PultTabloBell.h"
#include "SchemeOutput.h"

using namespace scb;

PultTabloScheme::PultTabloScheme(const wstring& name) :
	AbstractScheme(name)
{
	memset(&(this->tabloStatus), 0, sizeof(OutputStream));
}

PultTabloScheme::~PultTabloScheme()
{
	for (auto& activeDevice : this->activeDevices)
		if (activeDevice != nullptr)
		{
			delete activeDevice;
			activeDevice = nullptr;
		}

	for (auto& passiveDevice : this->passiveDevices)
		if (passiveDevice != nullptr)
		{
			delete passiveDevice;
			passiveDevice = nullptr;
		}

	for (auto& lampGroup : this->lampGroups)
		if (lampGroup != nullptr)
		{
			delete lampGroup;
			lampGroup = nullptr;
		}
}

void PultTabloScheme::setDeviceCount(int pultWidth, int outputs, int activeDevs, int passiveDevs, int lampGroups)
{
	this->pultStatus.resize(pultWidth, {0, 0, 0, 0, 0, 0, 0, 0});

	for (auto& device : this->devices)
		if (device != nullptr)
		{
			delete device;
			device = nullptr;
		}

	for (auto& activeDevice : this->activeDevices)
		if (activeDevice != nullptr)
		{
			delete activeDevice;
			activeDevice = nullptr;
		}

	for (auto& passiveDevice : this->passiveDevices)
		if (passiveDevice != nullptr)
		{
			delete passiveDevice;
			passiveDevice = nullptr;
		}

	for (auto& lampGroup : this->lampGroups)
		if (lampGroup != nullptr)
		{
			delete lampGroup;
			lampGroup = nullptr;
		}

	this->outputOverBlocks.resize(pultWidth);
	for (auto& outputOverBlock : this->outputOverBlocks)
		outputOverBlock.resize(0);

	this->devices.resize(outputs, nullptr);
	this->activeDevices.resize(activeDevs, nullptr);
	this->passiveDevices.resize(passiveDevs, nullptr);
	this->lampGroups.resize(lampGroups);

	for (auto& lampGroup : this->lampGroups)
		lampGroup = new PultTabloLampGroup(this);

}

void PultTabloScheme::setOutput(int index, const wstring& name, int block)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return;
	if (this->devices[index] != nullptr) 
		return;
	isInRange = inRange(block, this->pultStatus.size());
	if (!isInRange)
		return;

	this->devices[index] = new SchemeOutput(this, name, -1);
	this->outputOverBlocks[block].push_back(index);
}

void PultTabloScheme::setBell(int index, int continuouslyBit, int impulseBit)
{
	if (this->checkForPassiveDevice(index))
		this->passiveDevices[index] = new PultTabloBell(this, continuouslyBit, impulseBit);
}

void PultTabloScheme::setAmpermeter(int index, int startBit)
{
	if (this->checkForPassiveDevice(index))
		this->passiveDevices[index] = new PultTabloAmpermeter(this, startBit);
}

void PultTabloScheme::setButtonKmd(int index, Color color, int onBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloButtonKmd(this, color, onBit);
}

void PultTabloScheme::setButtonKmd(int index, Color color, int onBit, int offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloButtonKmd(this, color, onBit, offBit);
}

void PultTabloScheme::setButtonKmdf(int index, Color color, int onBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloButtonKmdf(this, color, onBit);
}

void PultTabloScheme::setButtonKmdf(int index, Color color, int onBit, int offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloButtonKmdf(this, color, onBit, offBit);
}

void PultTabloScheme::setButtonSchm1m(int index, Color color, int onBit, int offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloButtonSchm1m(this, color, onBit, offBit);
}

void PultTabloScheme::setCommutatorKmd(int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloCommutatorKmd(this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit);
}

void PultTabloScheme::setCommutatorKmdn(int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int onBit, int offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloCommutatorKmd(this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit, onBit, offBit);
}

void PultTabloScheme::setCommutatorKmt(int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloCommutatorKmt(this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit);
}

void PultTabloScheme::setCommutatorKmtn(int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int onBit, int offBit)
{
	if (this->checkForActiveDevice(index))
		this->activeDevices[index] = new PultTabloCommutatorKmt(this, color, leftPos_onBit, leftPos_offBit, rightPos_onBit, rightPos_offBit, onBit, offBit);
}

void PultTabloScheme::initialize()
{
	for (auto& device : this->activeDevices)
		if (device != nullptr)
			device->initialize();
}

void PultTabloScheme::recalculate()
{
	// пустой метод
	this->markRecalculated();
}

void PultTabloScheme::setStatusBit(int bit)
{
	const int element = (bit >> 5) & 7;
	const int block = (bit >> 8);
	const int bit_in_element = bit & 0x1F;
	if (block >= static_cast<int> (this->pultStatus.size())) return;
	this->pultStatus[block].mask[element] |= (1 << bit_in_element);

	for (const auto& output_index : this->outputOverBlocks[block])
		this->devices[output_index]->changeStatus(this->pultStatus[block]);
}

void PultTabloScheme::resetStatusBit(int bit)
{
	const int element = (bit >> 5) & 7;
	const int block = (bit >> 8);
	const int bit_in_element = bit & 0x1F;
	if (block >= static_cast<int> (this->pultStatus.size())) return;
	this->pultStatus[block].mask[element] &= ~(1 << bit_in_element);

	for (const auto& output : this->outputOverBlocks[block])
		this->devices[output]->changeStatus(this->pultStatus[block]);
}

void PultTabloScheme::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	int i;
	if (id == -1)
	{
		for (i = 0; i < 8; ++i)
			this->tabloStatus.mask[i] = (this->tabloStatus.mask[i] & maskOff.mask[i]) | maskOn.mask[i];
		for (auto& device : this->passiveDevices)
			device->changeStatus(this->tabloStatus);
	}
	else
		this->lampGroups[id]->changeStatus(maskOn);
}
