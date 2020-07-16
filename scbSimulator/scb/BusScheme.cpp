#include "BusScheme.h"
#include "SchemeOutput.h"

using namespace scb;

BusScheme::BusScheme(const wstring& name, int length) :
	AbstractScheme(name)
{
	this->status = new unsigned long[this->statusCount = length];
	memset(this->status, 0, sizeof(unsigned long) * length);
}

BusScheme::~BusScheme()
{
	if (this->status != nullptr)
	{
		delete[] this->status;
		this->status = nullptr;
		this->statusCount = 0;
	}
}

void BusScheme::initialize()
{
	// Ïףסעמי גûחמג
}

void BusScheme::setStatusBit(int bit)
{
	// Ïףסעמי גûחמג
}

void BusScheme::resetStatusBit(int bit)
{
	// Ïףסעמי גûחמג
}

void BusScheme::recalculate()
{
	OutputStream result;
	unsigned long temp = 0;

	const int loop = this->statusCount;
	for (int i = 0; i < loop; ++i)
		temp |= this->status[i];

	result.mask[0] = (temp == 0) ? 0 : 1;
	for (const auto& ptr : this->devices)
		ptr->changeStatus(result);

	this->markRecalculated();
}

void BusScheme::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	bool changed = false;
	unsigned long oldValue, newValue;

	const int loop = this->statusCount;
	for (int i = 0; i < loop; ++i)
	{
		newValue = (this->status[i] & maskOff.mask[i]) | maskOn.mask[i];
		if (!changed)
		{
			oldValue = this->status[i];
			if (!changed)
			{
				if ((oldValue != newValue) && ((oldValue & newValue) == 0))
					changed = true;
			}
		}
		this->status[i] = newValue;
	}

	if (changed)
		this->markToRecalculate();
}
