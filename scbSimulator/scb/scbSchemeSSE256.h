#pragma once

#include "scbScheme.h"

class scbAbstractSchemeDevice;

class scbSchemeSSE256 : public scbScheme
{
	__m128i m_Status [2]; // Слово состояния схемы

	__m128i* m_Memory; // Массив бинарных данных

	__m128i* m_PrepareCircuitMask; // Массив предварительных схемных масок
	__m128i* m_PrepareCircuitResult; // Массив предварительных схемных результатов

	__m128i* m_MainCircuitMask; // Массив основных схемных масок на устройства
	__m128i* m_MainCircuitResult; // Массив основных схемных результатов на устройства

	__m128i* m_StaticSensitiveMask; // Массив схемных масок на статические чувствительности
	__m128i* m_StaticSensitiveResult; // Массив схемных результатов на статические чувствительности

	__m128i* m_DynamicSensitiveMask; // Массив схемных масок на динамические чувствительности
	__m128i* m_DynamicSensitiveResult; // Массив схемных результатов на динамические чувствительности

public:
	scbSchemeSSE256 ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count );
	virtual ~scbSchemeSSE256 () override;

	virtual void SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;
	virtual void SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) override;

	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};