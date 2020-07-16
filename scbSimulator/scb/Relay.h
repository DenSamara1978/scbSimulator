#pragma once

#include "AbstractSchemeDevice.h"


namespace scb
{
	struct RelayTimeSample
	{
		int modeFrom;
		int modeTo;
		int starting;
		int shifting;
	};

	class Relay : public AbstractSchemeDevice
	{
	public:
		Relay(AbstractScheme* ownerScheme);
		virtual ~Relay() override;

		void setSample(int from_mode, int to_mode, int start, int shift);

		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // Вызывается схемой-хозяином после расчета

	protected:
		int currentMode; // Режим, в котором в настоящий момент находится реле
		int targetMode; // Режим, в которое реле начало переводится
		int status; // 0 - стабильно без тока, 1 - трогание на подъем, 2 - перелет на подъем, 3 - стабильно под током, 4 - трогание на отпадание, 5 - перелет на отпадание
		unsigned long long timeStamp;
		int starting;
		int shifting;

		vector<RelayTimeSample> timeSamples;

		// НА ТЕКУЩИЙ МОМЕНТ НЕЙТРАЛЬНЫЕ И ПОЛЯРИЗОВАННЫЕ РЕЛЕ ИМЕЮТ ИДЕНТИЧНЫЙ ТЕКСТ ЭТОГО МЕТОДА
		// - ЭТО НА СЛУЧАЙ ДАЛЬНЕЙШЕГО РАЗНОЧТЕНИЯ ПРИ ДОБАВЛЕНИИ ПОЛНОГО ФУНКЦИОНАЛА МОСТОВЫХ КОНТАКТОВ
		virtual void setMode(unsigned long mode) abstract; // Вызывается из метода ChangeStatus
	};
}