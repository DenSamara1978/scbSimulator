#pragma once

#include "Scheme.h"

namespace scb
{
	class AbstractSchemeDevice;

	class SchemeSse128 : public Scheme
	{
	public:
		SchemeSse128(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~SchemeSse128() override;

		virtual void setSensitiveMasks(const OutputStream& constMask, const OutputStream& dynMask) override;
		virtual void setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setMainCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;

		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& mask_on, const OutputStream& mask_off, int id) override;

	private:
		__m128i status; // ����� ��������� �����
		__m128i sensitives; // ����� ���������������� �����

		__m128i* memory; // ������ �������� ������

		__m128i* constSensitiveMask; // ����� ��������� �������������� ������
		__m128i* dynSensitiveMask; // ����� ����������� �������� ������

		__m128i* prepareCircuitMasks; // ������ ��������������� ������� �����
		__m128i* prepareCircuitResults; // ������ ��������������� ������� �����������

		__m128i* mainCircuitMasks; // ������ �������� ������� ����� �� ����������
		__m128i* mainCircuitResults; // ������ �������� ������� ����������� �� ����������

		__m128i* staticSensitiveMasks; // ������ ������� ����� �� ����������� ����������������
		__m128i* staticSensitiveResults; // ������ ������� ����������� �� ����������� ����������������

		__m128i* dynamicSensitiveMasks; // ������ ������� ����� �� ������������ ����������������
		__m128i* dynamicSensitiveResults; // ������ ������� ����������� �� ������������ ����������������
	};
}