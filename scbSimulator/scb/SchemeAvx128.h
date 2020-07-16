#pragma once

#include "Scheme.h"

namespace scb
{
	class AbstractSchemeDevice;

	class SchemeAvx128 : public Scheme
	{
	public:
		SchemeAvx128(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~SchemeAvx128() override;

		virtual void setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setMainCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;

		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& mask_on, const OutputStream& mask_off, int id) override;

	private:
		__m256i status; // ����� ��������� �����

		__m256i* memory; // ������ �������� ������

		__m256i* prepareCircuitMasks; // ������ ��������������� ������� �����
		__m256i* prepareCircuitResults; // ������ ��������������� ������� �����������

		__m256i* mainCircuitMasks; // ������ �������� ������� ����� �� ����������
		__m256i* mainCircuitResults; // ������ �������� ������� ����������� �� ����������

		__m256i* staticSensitiveMasks; // ������ ������� ����� �� ����������� ����������������
		__m256i* staticSensitiveResults; // ������ ������� ����������� �� ����������� ����������������

		__m256i* dynamicSensitiveMasks; // ������ ������� ����� �� ������������ ����������������
		__m256i* dynamicSensitiveResults; // ������ ������� ����������� �� ������������ ����������������
	};
}