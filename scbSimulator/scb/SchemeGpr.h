#pragma once

#include "Scheme.h"


namespace scb
{
	class AbstractSchemeDevice;

	class SchemeGpr : public Scheme
	{
	public:
		SchemeGpr(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~SchemeGpr() override;

		virtual void setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setMainCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;
		virtual void setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) override;

		virtual void recalculate() override;
		virtual void setStatusBit(int bit) override;
		virtual void resetStatusBit(int bit) override;
		virtual void correctInputStatus(const OutputStream& mask_on, const OutputStream& mask_off, int id) override;

	protected:
		unsigned long status[4]; // Слово состояния схемы

		unsigned long* memory; // Массив бинарных данных

		unsigned long* prepareCircuitMasks; // Массив предварительных схемных масок
		unsigned long* prepareCircuitResults; // Массив предварительных схемных результатов

		unsigned long* mainCircuitMasks; // Массив основных схемных масок на устройства
		unsigned long* mainCircuitResults; // Массив основных схемных результатов на устройства

		unsigned long* staticSensitiveMasks; // Массив схемных масок на статические чувствительности
		unsigned long* staticSensitiveResults; // Массив схемных результатов на статические чувствительности

		unsigned long* dynamicSensitiveMasks; // Массив схемных масок на динамические чувствительности
		unsigned long* dynamicSensitiveResults; // Массив схемных результатов на динамические чувствительности
	};
}