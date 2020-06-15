#pragma once

#include "scbAbstractScheme.h"
#include "scbLightSignalLamp.h"

class scbLightSignal : public scbAbstractScheme
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

private:
	char m_LampIndex [13];
	unsigned long m_Status [2]; // Текущее состояние ламп ( необходимо, чтобы разные лампы можно было независимо подключать от разных схем )

public:
	scbLightSignal ( const wstring& name );
	virtual ~scbLightSignal ();

	virtual void SetOutput ( int index, const wstring& name, int block ) override;

	bool SetLamp ( int index, LampPurpose type );

	virtual void Init () override;
	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};
