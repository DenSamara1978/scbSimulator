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
		__m256i status; // Слово состояния схемы
		__m256i sensitives; // Слово чувствительности схемы
		__m256i staticSensitives; // Статические чувствительности

		__m256i* memory; // Массив бинарных данных

		__m256i* constSensitiveMask; // Маска постоянно чувствительных входов
		__m256i* dynSensitiveMask; // Маска динамически влияющих входов

		__m256i* prepareCircuitMasks; // Массив предварительных схемных масок
		__m256i* prepareCircuitResults; // Массив предварительных схемных результатов

		__m256i* mainCircuitMasks; // Массив основных схемных масок на устройства
		__m256i* mainCircuitResults; // Массив основных схемных результатов на устройства

		__m256i* staticSensitiveMasks; // Массив схемных масок на статические чувствительности
		__m256i* staticSensitiveResults; // Массив схемных результатов на статические чувствительности

		__m256i* dynamicSensitiveMasks; // Массив схемных масок на динамические чувствительности
		__m256i* dynamicSensitiveResults; // Массив схемных результатов на динамические чувствительности
	};
}