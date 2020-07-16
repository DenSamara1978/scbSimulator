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
		virtual void changeStatus(const OutputStream& param) override; // ���������� ����������-��������

		void setColor(Color color);
		Color getColor() const;
		float getBright() const;

	private:
		static constexpr float lampOnVelocity = 5.0f;
		static constexpr float lampOffVelocity = -3.0f;

		inline static float targetBright[] = {0.0f, 0.5f, 0.8f, 1.0f, 0.5f, 0.8f, 1.0f};

		Color color;
		
		/*
		0 - ����� ��������
		1 - ��� 15 ��
		2 - ���� 15 ��
		3 - ���� 15 ��
		4 - ��� 25 ��
		5 - ���� 25 ��
		6 - ���� 25 ��
		*/
		char status;
		float bright; // 0.0f - 1.0f �������
		float velocity; // �������� ��������� �������, ��.���./���.
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