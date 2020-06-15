#pragma once

#include "scbAbstractScheme.h"

class scbScheme : public scbAbstractScheme
{
protected:
	int m_PrepareCircuitCount; // Размер массивов предварительных схем
	int m_MainCircuitCount; // Размер массивов схем на устройства
	int m_StaticSensitiveCount; // Размер массива схем на статические чувствительности
	int m_DynamicSensitiveCount; // Размер массива схем на динамические чувствительности

public:
	scbScheme ( const wstring& name, int prep_count, int main_count, int statsens_count, int dynsens_count );
	virtual ~scbScheme ();

	virtual void SetPrepareCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) abstract;
	virtual void SetMainCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) abstract;
	virtual void SetStaticSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) abstract;
	virtual void SetDynamicSensitiveCircuit ( int index, const scbOutputStream& mask, const scbOutputStream& result ) abstract;

	virtual void Init () override;
	virtual void MapInputOutput ( int output_index, int in_bit, int out_bit ) override;

	void SetPolarRelay ( int index, int dir_bit, int rev_bit );
	void SetNeutralRelay ( int index, int on_bit );
	void SetNeutralRelay ( int index, int on_bit, int off_bit );
	void SetNeutralRelay ( int index, int on_bit, int off_bit, int on_bridge_bit, int off_bridge_bit );

	void AddRelayTimeSample ( int index, int from_mode, int to_mode, int start, int shift );
	void AddRelayConvertation ( int index, int in_bit, int out_bit );
};
