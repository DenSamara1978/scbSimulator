#pragma once

#include "AbstractSchemeDevice.h"

namespace scb
{

	class PultTabloActiveDevice : public AbstractSchemeDevice
	{
	public:
		PultTabloActiveDevice(AbstractScheme* ownerScheme);
		virtual ~PultTabloActiveDevice() override;

		// ������, ���������� ������� ������� �� ���������� ��������� ����������
		virtual void press(); // �������
		virtual void release(); // ����������
		virtual void turnCw(); // ������� �� ������� �������
		virtual void turnCcw(); // ������� ������ ������� �������
		virtual void unseal(); // ������ ������ � ��������� ������������� �����
		virtual void seal(); // ��������� ������������� ����� � ��������� ������
		virtual void remove(); // ���������� �����-�����
		virtual void insert(); // ������� �����-�����

		virtual void changeStatus(const OutputStream& param) override; // ���������� ������-�������� ����� �������
	};
}
