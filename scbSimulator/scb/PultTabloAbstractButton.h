#pragma once

#include "PultTabloActiveDevice.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloAbstractButton : public PultTabloActiveDevice
	{
	public:
		PultTabloAbstractButton(AbstractScheme* ownerScheme, Color color, int onBit);
		PultTabloAbstractButton(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloAbstractButton() override;

		Color getColor() const;
		float getPressPosition() const;

	protected:
		int onContactBit;
		int offContactBit;
		float position; // Физическое положение кнопки: 0.0f - исходное, 1.0f - нажатое
		Color color;
		unsigned long long timeStamp;
		int status; // 0 - исходное положение, остальное специфично
		int contactStatus; // 0 - исходное положение, остальное специфично

		static constexpr float onBorder = 0.7f; // значение положения коммутации фронтовых контактов
		static constexpr float offBorder = 0.2f; // Значение положения коммутации тыловых контактов
		static constexpr float fixBorder = 0.8f; // Значение положения фиксации
		static constexpr float pressTime = 300.0f; // Время нажатия/отпуска, мс
	};

	inline Color PultTabloAbstractButton::getColor() const
	{
		return this->color;
	}

	inline float PultTabloAbstractButton::getPressPosition() const
	{
		return this->position;
	}
}