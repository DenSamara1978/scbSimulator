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
		float position; // ���������� ��������� ������: 0.0f - ��������, 1.0f - �������
		Color color;
		unsigned long long timeStamp;
		int status; // 0 - �������� ���������, ��������� ����������
		int contactStatus; // 0 - �������� ���������, ��������� ����������

		static constexpr float onBorder = 0.7f; // �������� ��������� ���������� ��������� ���������
		static constexpr float offBorder = 0.2f; // �������� ��������� ���������� ������� ���������
		static constexpr float fixBorder = 0.8f; // �������� ��������� ��������
		static constexpr float pressTime = 300.0f; // ����� �������/�������, ��
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