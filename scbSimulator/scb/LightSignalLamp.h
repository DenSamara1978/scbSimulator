#pragma once

#include "AbstractSchemeDevice.h"
#include "..\util\color.h"

using util::Color;

namespace scb
{
	class LightSignalLamp : public AbstractSchemeDevice
	{
	public:
		LightSignalLamp(AbstractScheme* ownerScheme);
		virtual ~LightSignalLamp();

		virtual void initialize() override;
		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // Вызывается светофором-хозяином

		void setColor(Color color);
		Color getColor() const;
		float getBright() const;

	private:
		static constexpr float lampOnVelocity = 5.0f;
		static constexpr float lampOffVelocity = -3.0f;

		inline static float targetBright[] = {0.0f, 0.5f, 0.8f, 1.0f, 0.5f, 0.8f, 1.0f};

		Color color;
		
		/*
		0 - лампа потушена
		1 - ДСН 15 Вт
		2 - Ночь 15 Вт
		3 - День 15 Вт
		4 - ДСН 25 Вт
		5 - Ночь 25 Вт
		6 - День 25 Вт
		*/
		char status;
		float bright; // 0.0f - 1.0f яркость
		float velocity; // Скорость изменения яркости, ед.ярк./сек.
		unsigned long long timeStamp;

	};

	inline void LightSignalLamp::setColor(Color color)
	{
		this->color = color;
	}

	inline Color LightSignalLamp::getColor() const
	{
		return this->color;
	}

	inline float LightSignalLamp::getBright() const
	{
		return this->bright;
	}
}