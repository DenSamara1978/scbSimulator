#pragma once

#include <vector>
#include <string>
#include "scbAbstractScheme.h"

using std::wstring;
using std::vector;

class scbSchemeOutput;
class scbPultTabloActiveDevice;
class scbPultTabloLampGroup;

class scbPultTablo : public scbAbstractScheme
{
public:
	enum class Color
	{
		Black = 0,
		Blue,
		White,
		Yellow,
		Green,
		Red,
	};

private:
	vector<scbOutputStream> m_PultStatus; // 256-битные структуры состояния аппаратов управления

	scbOutputStream m_TabloStatus; // состояние пассивных элементов

	vector<vector<int>> m_OutputOverBlocks;
	vector<scbPultTabloActiveDevice*> m_ActiveDevices;
	vector<scbAbstractSchemeDevice*> m_PassiveDevices;
	vector<scbPultTabloLampGroup*> m_LampGroups;

public:
	scbPultTablo ( const wstring& name );
	virtual ~scbPultTablo ();

	void SetDeviceCount ( int pultWidth, int outputs, int activeDevs, int passiveDevs, int lampGroups );

	int GetActiveDeviceCount () const;
	int GetPassiveDeviceCount () const;
	int GetLampGroupCount () const;

	scbPultTabloActiveDevice* GetActiveDevice ( int index ) const;
	scbAbstractSchemeDevice* GetPassiveDevice ( int index ) const;
	scbPultTabloLampGroup* GetLampGroup ( int index ) const;

	virtual void SetOutput ( int index, const wstring& name, int block ) override;
	void SetBell ( int index, int continuously_bit, int impulse_bit );
	void SetAmpermeter ( int index, int start_bit );
	void SetButtonKmd ( int index, Color color, int on_bit );
	void SetButtonKmd ( int index, Color color, int on_bit, int off_bit );
	void SetButtonKmdf ( int index, Color color, int on_bit );
	void SetButtonKmdf ( int index, Color color, int on_bit, int off_bit );
	void SetButtonSchm1m ( int index, Color color, int on_bit, int off_bit );
	void SetCommutatorKmd ( int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	void SetCommutatorKmdn ( int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );
	void SetCommutatorKmt ( int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit );
	void SetCommutatorKmtn ( int index, Color color, int leftPos_onBit, int leftPos_offBit, int rightPos_onBit, int rightPos_offBit, int on_bit, int off_bit );

	virtual void Init () override;
	virtual void Recalculate () override;
	virtual void SetStatusBit ( int bit ) override;
	virtual void ResetStatusBit ( int bit ) override;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) override;
};

inline int scbPultTablo::GetActiveDeviceCount () const
{
	return static_cast<int>( this->m_ActiveDevices.size ());
}

inline int scbPultTablo::GetPassiveDeviceCount () const
{
	return static_cast<int>( this->m_PassiveDevices.size ());
}

inline int scbPultTablo::GetLampGroupCount () const
{
	return static_cast<int>( this->m_LampGroups.size ());
}

inline scbPultTabloActiveDevice* scbPultTablo::GetActiveDevice ( int index ) const
{
	return ( ( index < 0 ) || ( index >= static_cast<int>( this->m_ActiveDevices.size ())) ) ? nullptr : this->m_ActiveDevices [index];
}

inline scbAbstractSchemeDevice* scbPultTablo::GetPassiveDevice ( int index ) const
{
	return ( ( index < 0 ) || ( index >= static_cast<int>( this->m_PassiveDevices.size ())) ) ? nullptr : this->m_PassiveDevices [index];
}

inline scbPultTabloLampGroup* scbPultTablo::GetLampGroup ( int index ) const
{
	return ( ( index < 0 ) || ( index >= static_cast<int>( this->m_LampGroups.size ())) ) ? nullptr : this->m_LampGroups [index];
}
