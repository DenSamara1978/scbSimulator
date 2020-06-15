#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeAVX256 : public scbScheme
{
	__m256i m_Status; // ����� ��������� �����

	__m256i* m_Memory; // ������ �������� ������

	__m256i* m_PrepareCircuitMask; // ������ ��������������� ������� �����
	__m256i* m_PrepareCircuitResult; // ������ ��������������� ������� �����������

	__m256i* m_MainCircuitMask; // ������ �������� ������� ����� �� ����������
	__m256i* m_MainCircuitResult; // ������ �������� ������� ����������� �� ����������

	__m256i* m_StaticSensitiveMask; // ������ ������� ����� �� ����������� ����������������
	__m256i* m_StaticSensitiveResult; // ������ ������� ����������� �� ����������� ����������������

	__m256i* m_DynamicSensitiveMask; // ������ ������� ����� �� ������������ ����������������
	__m256i* m_DynamicSensitiveResult; // ������ ������� ����������� �� ������������ ����������������

public:
	scbSchemeAVX256 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count );
	virtual ~scbSchemeAVX256 () override;

	virtual void SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;

	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};