#pragma once

#include "AbstractScheme.h"

namespace scb
{
	class ChainScheme : public AbstractScheme
	{
	public:
		ChainScheme(const wstring& name, int length);
		virtual ~ChainScheme() override;

		virtual void initialize() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void recalculate() override;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) override;

	private:
		unsigned long* status; // Слово состояния схемы
		int statusCount;
	};
}