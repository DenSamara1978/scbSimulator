#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeGPR : public scbScheme
{
	unsigned long m_Status [4]; // Слово состояния схемы

	unsigned long* m_Memory; // Массив бинарных данных

	unsigned long* m_PrepareCircuitMask; // Массив предварительных схемных масок
	unsigned long* m_PrepareCircuitResult; // Массив предварительных схемных результатов

	unsigned long* m_MainCircuitMask; // Массив основных схемных масок на устройства
	unsigned long* m_MainCircuitResult; // Массив основных схемных результатов на устройства

	unsigned long* m_StaticSensitiveMask; // Массив схемных масок на статические чувствительности
	unsigned long* m_StaticSensitiveResult; // Массив схемных результатов на статические чувствительности

	unsigned long* m_DynamicSensitiveMask; // Массив схемных масок на динамические чувствительности
	unsigned long* m_DynamicSensitiveResult; // Массив схемных результатов на динамические чувствительности

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