#pragma once

#include <vector>
#include <string>
#include <emmintrin.h>
#include <immintrin.h>
#include "scbTimer.h"

using std::wstring;
using std::vector;

class scbAbstractSchemeDevice;

union scbOutputStream
{
	unsigned long Mask [8];
	__m128i SSE_mask [2];
	__m256i AVX_mask;
};

class scbAbstractScheme
{
	wstring m_Name;
	bool m_MarkedToRecalculate;

protected:
	vector<scbAbstractSchemeDevice*> m_Devices; // Устройства, принадлежащие этой схеме

public:
	scbAbstractScheme ( const wstring& name );
	virtual ~scbAbstractScheme ();

	bool IsA ( const wstring& name ) const;

	void SetDeviceCount ( int count );
	int GetDeviceCount () const;
	scbAbstractSchemeDevice* GetDevice ( int index ) const;
	virtual void MapInputOutput ( int output_index, int in_bit, int out_bit );
	virtual void SetOutput ( int index, const wstring& name, int block = -1 );

	virtual void Init () abstract;
	virtual void Recalculate () abstract;
	virtual void SetStatusBit ( int bit ) abstract;
	virtual void ResetStatusBit ( int bit ) abstract;
	virtual void CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id ) abstract;

	void MarkToRecalculate ();
	void MarkRecalculated ();
	bool IsNotMarkedToRecalculate () const;
};

inline scbAbstractScheme::scbAbstractScheme ( const wstring& name ) :
	m_Name ( name ),
	m_MarkedToRecalculate ( false )
{
}

inline bool scbAbstractScheme::IsA ( const wstring& name ) const
{
	return this->m_Name == name;
}

inline int scbAbstractScheme::GetDeviceCount () const
{
	return static_cast<int> ( this->m_Devices.size ());
}

inline scbAbstractSchemeDevice* scbAbstractScheme::GetDevice ( int index ) const
{
	return (( index >= 0 ) && ( index < static_cast<int>( this->m_Devices.size ()))) ? this->m_Devices [index] : nullptr;
}

inline void scbAbstractScheme::MarkToRecalculate ()
{
	if ( !this->m_MarkedToRecalculate )
		scbTimer::Instance ()->AddSchemeToRecalculate ( this );
	this->m_MarkedToRecalculate = true;
}

inline void scbAbstractScheme::MarkRecalculated ()
{
	this->m_MarkedToRecalculate = false;
}

inline bool scbAbstractScheme::IsNotMarkedToRecalculate () const
{
	return !this->m_MarkedToRecalculate;
}
