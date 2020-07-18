#pragma once

#include "Scheme.h"


namespace scb
{
	class AbstractSchemeDevice;

	class SchemeGpr128 : public Scheme
	{
	public:
		SchemeGpr128(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~SchemeGpr128() override;

		virtual void setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask) override;
		virtual void setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setMainCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;

		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& mask_on, const OutputStream& mask_off, int id) override;

	protected:
		unsigned long status[4]; // ����� ��������� �����
		unsigned long sensitives[4]; // ����� ���������������� �����

		unsigned long* memory; // ������ �������� ������

		unsigned long* constSensitiveMask; // ����� ��������� �������������� ������
		unsigned long* dynSensitiveMask; // ����� ����������� �������� ������

		unsigned long* prepareCircuitMasks; // ������ ��������������� ������� �����
		unsigned long* prepareCircuitResults; // ������ ��������������� ������� �����������

		unsigned long* mainCircuitMasks; // ������ �������� ������� ����� �� ����������
		unsigned long* mainCircuitResults; // ������ �������� ������� ����������� �� ����������

		unsigned long* staticSensitiveMasks; // ������ ������� ����� �� ����������� ����������������
		unsigned long* staticSensitiveResults; // ������ ������� ����������� �� ����������� ����������������

		unsigned long* dynamicSensitiveMasks; // ������ ������� ����� �� ������������ ����������������
		unsigned long* dynamicSensitiveResults; // ������ ������� ����������� �� ������������ ����������������
	};
}