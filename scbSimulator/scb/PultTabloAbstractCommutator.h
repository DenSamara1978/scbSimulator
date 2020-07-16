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
		float pressPosition; // ���������� ��������� �������� ��������: 0.0f - ��������, 1.0f - �������
		float switchPosition; // ���������� ��������� ����������� �����������: 0.0f - �������, -1.0f - ��������� ������ ������� ( ������), 1.0f - ��������� �� ������� ( ������� )
		Color color;
		bool pressable; // ������� �������� ��������
		unsigned long long timeStamp;
		/*
		0 - ��������
		1 - ����������
		2 - ������
		3 - �����������
		*/
		int pressStatus;
		/*
		0 - ��� �������
		1 - ���������� ��� ��������
		2 - ����� �������
		*/
		int pressContactStatus;
		int switchStatus; // 0 - ��������, ��������� ����������
		int switchContactStatus; // 0 - ��������, ��������� ����������

		static constexpr float pressOnBorder = 0.7f; // �������� ��������� ���������� ��������� ���������
		static constexpr float pressOffBorder = 0.2f; // �������� ��������� ���������� ������� ���������
		static constexpr float pressTime = 300.0f; // ����� �������/�������, ��
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