#pragma once

#include "PultTabloAbstractButton.h"
#include "..\util\Color.h"

using util::Color;

namespace scb
{

	class PultTabloButtonKmd : public PultTabloAbstractButton
	{
		/*
		m_Status
		0 - ��������
		1 - ����������
		2 - ������
		3 - �����������
		*/

		/*
		m_ContactStatus
		0 - ��� �������
		1 - ���������� ��� ��������
		2 - ����� �������
		*/

	public:
		PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit);
		PultTabloButtonKmd(AbstractScheme* ownerScheme, Color color, int onBit, int offBit);
		virtual ~PultTabloButtonKmd() override;

		virtual void initialize() override;

		virtual void press() override;
		virtual void release() override;

		virtual void idleTimer(unsigned long long time) override;
	};
}