#pragma once

#include <vector>
#include "scbAbstractScheme.h"
#include "scbTimer.h"

using std::vector;

class scbAbstractSchemeDevice
{
protected:
	struct Convertation
	{
		int OutputElement;
		unsigned long OutputMask;
		int InputElement;
		unsigned long InputMask;
	};

	vector<Convertation> m_Convertations;

	scbAbstractScheme* m_OwnerScheme;

	void AddIdleTimer ();
	void DeleteIdleTimer ();

private:
	bool m_HasIdleTimer;

public:
	scbAbstractSchemeDevice ( scbAbstractScheme* owner );
	virtual ~scbAbstractSchemeDevice ();

	void MapInputOutput ( int in_bit, int out_bit );

	virtual void TimeToWork ( int signal, unsigned long long time ); // Обработка таймера

	virtual void Init () abstract;
	virtual void ChangeStatus ( const scbOutputStream& param ) abstract; // Вызывается схемой-хозяином после собственного расчета

	virtual void IdleTimer ( unsigned long long time ) abstract;
};


inline void scbAbstractSchemeDevice::AddIdleTimer ()
{
	if ( !this->m_HasIdleTimer )
	{
		this->m_HasIdleTimer = true;
		scbTimer::Instance ()->AddIdleTimer ( this );
	}
}

inline void scbAbstractSchemeDevice::DeleteIdleTimer ()
{
	if ( this->m_HasIdleTimer )
	{
		this->m_HasIdleTimer = false;
		scbTimer::Instance ()->DeleteIdleTimer ( this );
	}
}
