#pragma once

#include "PultTabloAbstractButton.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{
	class PultTabloButtonKmdf : public PultTabloAbstractButton
	{
		/*
		m_Status
		0 - ��������
		1 - ���������� �� ��������
		2 - ������ �� ��������
		3 - ����������� �� ��������
		4 - ��������
		5 - ���������� ����� ��������
		6 - ������ ����� ��������
		7 - ����������� ����� ��������
		*/

		/*
		m_ContactStatus
		0 - ��� �������
		1 - ���������� ��� ��������
		2 - ����� �������
		*/

	public:
		PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit);
		PultTabloButtonKmdf(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloButtonKmdf() override;

		virtual void initialize() override;

		virtual void press() override;
		virtual void release() override;

		virtual void idleTimer(unsigned long long time) override;
	};
}