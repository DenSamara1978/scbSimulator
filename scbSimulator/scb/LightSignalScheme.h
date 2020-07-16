#pragma once

#include "AbstractScheme.h"
#include "LightSignalLamp.h"

namespace scb
{

	class LightSignalScheme : public AbstractScheme
	{
	public:
		enum class LampPurpose
		{
			Red = 0,
			Yellow,
			FirstYellow,
			SecondYellow,
			ThirdYellow,
			Green,
			FirstGreen,
			SecondGreen,
			GreenStrip,
			FirstGreenStrip,
			SecondGreenStrip,
			White,
			FirstWhite,
			SecondWhite,
			Blue,
			BreakArrow,
			FirstBreakArrow,
			SecondBreakArrow,

			LampPurposeCount,
		};

		LightSignalScheme(const wstring& name);
		virtual ~LightSignalScheme();

		virtual void setOutput(int index, const wstring& name, int block) override;

		bool setLamp(int index, LampPurpose type);

		virtual void initialize() override;
		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id) override;

	private:
		char lampIndex[13];
		unsigned long status[2]; // Текущее состояние ламп ( необходимо, чтобы разные лампы можно было независимо подключать от разных схем )
	};
}