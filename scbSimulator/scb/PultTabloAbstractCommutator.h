#pragma once

#include "PultTabloActiveDevice.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{

	class PultTabloAbstractCommutator : public PultTabloActiveDevice
	{
	public:
		PultTabloAbstractCommutator(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		PultTabloAbstractCommutator(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);
		virtual ~PultTabloAbstractCommutator() override;

		virtual void press() override;
		virtual void release() override;

		Color getColor() const;
		float getPressPosition() const;
		float getSwitchPosition() const;

	protected:
		int switchLeftOnContactBit;
		int switchLeftOffContactBit;
		int switchRightOnContactBit;
		int switchRightOffContactBit;
		int pressOnContactBit;
		int pressOffContactBit;
		float pressPosition; // Физическое положение нажимной рукоятки: 0.0f - исходное, 1.0f - нажатое
		float switchPosition; // Физическое положение поворотного коммутатора: 0.0f - среднее, -1.0f - положение против часовой ( налево), 1.0f - положение по часовой ( направо )
		Color color;
		bool pressable; // Имеется нажимная рукоятка
		unsigned long long timeStamp;
		/*
		0 - исходное
		1 - нажимается
		2 - нажата
		3 - отпускается
		*/
		int pressStatus;
		/*
		0 - тыл замкнут
		1 - размокнуты все контакты
		2 - фронт замкнут
		*/
		int pressContactStatus;
		int switchStatus; // 0 - исходное, остальное специфично
		int switchContactStatus; // 0 - исходное, остальное специфично

		static constexpr float pressOnBorder = 0.7f; // значение положения коммутации фронтовых контактов
		static constexpr float pressOffBorder = 0.2f; // Значение положения коммутации тыловых контактов
		static constexpr float pressTime = 300.0f; // Время нажатия/отпуска, мс
	};

	inline Color PultTabloAbstractCommutator::getColor() const
	{
		return this->color;
	}

	inline float PultTabloAbstractCommutator::getPressPosition() const
	{
		return this->pressPosition;
	}

	inline float PultTabloAbstractCommutator::getSwitchPosition() const
	{
		return this->switchPosition;
	}
}