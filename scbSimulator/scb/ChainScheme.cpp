#include "ChainScheme.h"
#include "SchemeOutput.h"

using namespace scb;

ChainScheme::ChainScheme(const wstring& name, int length) :
	AbstractScheme(name)
{
	this->status = new unsigned long[this->statusCount = length];
	memset(this->status, 0xFF, sizeof(unsigned long) * length);
}

ChainScheme::~ChainScheme()
{
	if (this->status != nullptr)
	{
		delete[] this->status;
		this->status = nullptr;
		this->statusCount = 0;
	}
}

void ChainScheme::initialize()
{
	// Ïףסעמי גûחמג
}

void ChainScheme::setStatusBit(int bit)
{
	// Ïףסעמי גûחמג
}

void ChainScheme::resetStatusBit(int bit)
{
	// Ïףסעמי גûחמג
}

void ChainScheme::recalculate()
{
	OutputStream result;
	unsigned long temp = 0xFFFFFFFF;

	const int loop = this->statusCount;
	for (int i = 0; i < loop; ++i)
		temp &= this->status[i];

	result.mask[0] = (temp != 0xFFFFFFFF) ? 0 : 1;
	for (const auto& ptr : this->devices)
		ptr->changeStatus(result);

	this->markRecalculated();
}

void ChainScheme::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
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
				if ((oldValue != newValue) && ((oldValue | newValue) == 0xFFFFFFFF))
					changed = true;
			}
		}
		this->status[i] = newValue;
	}

	if (changed)
		this->markToFullRecalculating();
}
