#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeSSE16 : public scbScheme
{
	__m128i m_Status; // ����� ��������� �����

	__m128i* m_Memory; // ������ �������� ������

	__m128i* m_PrepareCircuitMask; // ������ ��������������� ������� �����
	__m128i* m_PrepareCircuitResult; // ������ ��������������� ������� �����������

	__m128i* m_MainCircuitMask; // ������ �������� ������� ����� �� ����������
	__m128i* m_MainCircuitResult; // ������ �������� ������� ����������� �� ����������

	__m128i* m_StaticSensitiveMask; // ������ ������� ����� �� ����������� ����������������
	__m128i* m_StaticSensitiveResult; // ������ ������� ����������� �� ����������� ����������������

	__m128i* m_DynamicSensitiveMask; // ������ ������� ����� �� ������������ ����������������
	__m128i* m_DynamicSensitiveResult; // ������ ������� ����������� �� ������������ ����������������

public:
	scbSchemeSSE16 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count );
	virtual ~scbSchemeSSE16 () override;

	virtual void SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;

	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};