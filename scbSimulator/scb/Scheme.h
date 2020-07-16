#pragma once

#include "AbstractScheme.h"

namespace scb
{
	class Scheme : public AbstractScheme
	{
	public:
		Scheme(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		virtual ~Scheme();

		virtual void setPrepareCircuit(int index, const OutputStream& mask, const OutputStream& result) abstract;
		virtual void setMainCircuit(int index, const OutputStream& mask, const OutputStream& result) abstract;
		virtual void setStaticSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) abstract;
		virtual void setDynamicSensitiveCircuit(int index, const OutputStream& mask, const OutputStream& result) abstract;

		virtual void initialize() override;
		virtual void mapInputOutput(int output_index, int inputBit, int outputBit) override;

		void setPolarRelay(int index, int directionalBit, int reverseBit);
		void setNeutralRelay(int index, int onBit);
		void setNeutralRelay(int index, int onBit, int offBit);
		void setNeutralRelay(int index, int onBit, int offBit, int onBridgeBit, int offBridgeBit);

		void addRelayTimeSample(int index, int fromMode, int toMode, int start, int shift);
		void addRelayConvertation(int index, int inputBit, int outputBit);

	protected:
		int nPrepareCircuits; // Размер массивов предварительных схем
		int nMainCircuits; // Размер массивов схем на устройства
		int nStaticSensitives; // Размер массива схем на статические чувствительности
		int nDynamicSensitives; // Размер массива схем на динамические чувствительности
	};
}