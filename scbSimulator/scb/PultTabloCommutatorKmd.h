#pragma once

#include "PultTabloAbstractCommutator.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloCommutatorKmd : public PultTabloAbstractCommutator
	{
	public:
		PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit);
		PultTabloCommutatorKmd(AbstractScheme* ownerScheme, Color color, int leftPositionOnBit, int leftPositionOffBit, int rightPositionOnBit, int rightPositionOffBit, int onBit, int offBit);
		virtual ~PultTabloCommutatorKmd();

		virtual void initialize() override;

		virtual void turnCw() override;
		virtual void turnCcw() override;

		virtual void idleTimer(unsigned long long time) override;

	private:
		/*
		m_SwitchStatus
		0 - �������� ( ����� )
		1 - �������������� �� �������
		2 - ��������� ( ������ )
		3 - �������������� ������ �������
		*/

		/*
		m_SwitchContactStatus
		0 - ����� ������ ��������� �������, ��� ������� ��������� �������
		1 -								��� ������� ��������� �������
		2 - ��� ������ ��������� �������, ��� ������� ��������� �������
		3 - ��� ������ ��������� �������
		4 - ��� ������ ��������� �������, ����� ������� ��������� ������
		*/

		static constexpr float switchOnBorder = 0.7f; // �������� ��������� ���������� ��������� ��������� ��� ������������
		static constexpr float switchOffBorder = 0.2f; // �������� ��������� ���������� ������� ��������� ��� ������������
		static constexpr float switchTime = 400.0f; // ����� �������� ����� �����������, ��

	};
}