#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeAVX128 : public scbScheme
{
	__m256i m_Status; // Слово состояния схемы

	__m256i* m_Memory; // Массив бинарных данных

	__m256i* m_PrepareCircuitMask; // Массив предварительных схемных масок
	__m256i* m_PrepareCircuitResult; // Массив предварительных схемных результатов

	__m256i* m_MainCircuitMask; // Массив основных схемных масок на устройства
	__m256i* m_MainCircuitResult; // Массив основных схемных результатов на устройства

	__m256i* m_StaticSensitiveMask; // Массив схемных масок на статические чувствительности
	__m256i* m_StaticSensitiveResult; // Массив схемных результатов на статические чувствительности

	__m256i* m_DynamicSensitiveMask; // Массив схемных масок на динамические чувствительности
	__m256i* m_DynamicSensitiveResult; // Массив схемных результатов на динамические чувствительности

public:
	scbSchemeAVX128 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count );
	virtual ~scbSchemeAVX128 () override;

	virtual void SetPrepareCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;
	virtual void SetMainCircuit (int index, const scbOutputStream& mask, const scbOutputStream& result) override;
	virtual void SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;

	virtual void Recalculate () override;
	virtual void SetStatusBit (int bit) override;
	virtual void ResetStatusBit (int bit) override;
	virtual void CorrectInputStatus (const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id) override;
};