#pragma once

#include "scbAbstractSchemeDevice.h"

struct scbRelayTimeSample
{
	int ModeFrom;
	int ModeTo;
	int Starting;
	int Shifting;
};

class scbRelay : public scbAbstractSchemeDevice
{
protected:
	int m_CurrentMode; // Режим, в котором в настоящий момент находится реле
	int m_TargetMode; // Режим, в которое реле начало переводится
	int m_Status; // 0 - стабильно без тока, 1 - трогание на подъем, 2 - перелет на подъем, 3 - стабильно под током, 4 - трогание на отпадание, 5 - перелет на отпадание
	unsigned long long m_TimeStamp;
	int m_Starting;
	int m_Shifting;

	vector<scbRelayTimeSample> m_TimeSamples;

	// НА ТЕКУЩИЙ МОМЕНТ НЕЙТРАЛЬНЫЕ И ПОЛЯРИЗОВАННЫЕ РЕЛЕ ИМЕЮТ ИДЕНТИЧНЫЙ ТЕКСТ ЭТОГО МЕТОДА
	// - ЭТО НА СЛУЧАЙ ДАЛЬНЕЙШЕГО РАЗНОЧТЕНИЯ ПРИ ДОБАВЛЕНИИ ПОЛНОГО ФУНКЦИОНАЛА МОСТОВЫХ КОНТАКТОВ
	virtual void SetMode ( unsigned long mode ) abstract; // Вызывается из метода ChangeStatus

public:
	scbRelay ( scbAbstractScheme* ownerScheme );
	virtual ~scbRelay () override;

	void SetSample ( int from_mode, int to_mode, int start, int shift );

	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается схемой-хозяином после расчета
};
