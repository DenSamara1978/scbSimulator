#pragma once

#include "Scheme.h"


namespace scb
{
	class AbstractSchemeDevice;

	class SchemeSse16 : public Scheme
	{
	public:
		SchemeSse16(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~SchemeSse16() override;

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
		__m128i status; // Слово состояния схемы
		__m128i sensitives; // Слово чувствительности схемы

		__m128i* memory; // Массив бинарных данных

		__m128i* constSensitiveMask; // Маска постоянно чувствительных входов
		__m128i* dynSensitiveMask; // Маска динамически влияющих входов

		__m128i* prepareCircuitMasks; // Массив предварительных схемных масок
		__m128i* prepareCircuitResults; // Массив предварительных схемных результатов

		__m128i* mainCircuitMasks; // Массив основных схемных масок на устройства
		__m128i* mainCircuitResults; // Массив основных схемных результатов на устройства

		__m128i* staticSensitiveMasks; // Массив схемных масок на статические чувствительности
		__m128i* staticSensitiveResults; // Массив схемных результатов на статические чувствительности

		__m128i* dynamicSensitiveMasks; // Массив схемных масок на динамические чувствительности
		__m128i* dynamicSensitiveResults; // Массив схемных результатов на динамические чувствительности
	};
}