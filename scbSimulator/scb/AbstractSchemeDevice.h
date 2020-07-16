#pragma once

#include <vector>
#include "..\time\TimeSensable.h"
#include "OutputStream.h"

using std::vector;

namespace scb
{
	class AbstractScheme;

	class AbstractSchemeDevice : public time::TimeSensable
	{
	public:
		AbstractSchemeDevice(AbstractScheme* owner);
		virtual ~AbstractSchemeDevice();

		void mapInputOutput(int inputBit, int outputBit);

		virtual void initialize() abstract;
		virtual void changeStatus(const OutputStream& param) abstract; // Вызывается схемой-хозяином после собственного расчета

	protected:
		struct Convertation
		{
			int outputElement;
			unsigned long outputMask;
			int inputElement;
			unsigned long inputMask;
		};

		vector<Convertation> convertations;

		AbstractScheme* ownerScheme;
	};
}