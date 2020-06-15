#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeGPR : public scbScheme
{
	unsigned long m_Status [4]; // ����� ��������� �����

	unsigned long* m_Memory; // ������ �������� ������

	unsigned long* m_PrepareCircuitMask; // ������ ��������������� ������� �����
	unsigned long* m_PrepareCircuitResult; // ������ ��������������� ������� �����������

	unsigned long* m_MainCircuitMask; // ������ �������� ������� ����� �� ����������
	unsigned long* m_MainCircuitResult; // ������ �������� ������� ����������� �� ����������

	unsigned long* m_StaticSensitiveMask; // ������ ������� ����� �� ����������� ����������������
	unsigned long* m_StaticSensitiveResult; // ������ ������� ����������� �� ����������� ����������������

	unsigned long* m_DynamicSensitiveMask; // ������ ������� ����� �� ������������ ����������������
	unsigned long* m_DynamicSensitiveResult; // ������ ������� ����������� �� ������������ ����������������

public:
	scbSchemeGPR (const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count);
	virtual ~scbSchemeGPR () override;

	virtual void SetPrepareCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;
	virtual void SetMainCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;
	virtual void SetStaticSensitiveCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;
	virtual void SetDynamicSensitiveCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;

	virtual void Recalculate () override;
	virtual void SetStatusBit (int bit) override;
	virtual void ResetStatusBit (int bit) override;
	virtual void CorrectInputStatus (const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id) override;
};