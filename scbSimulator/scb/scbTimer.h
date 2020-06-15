#pragma once

#include <deque>
#include <list>
#include <algorithm>
#include "scbTimerRecord.h"

using std::deque;
using std::list;

class scbAbstractScheme;
class scbAbstractSchemeDevice;

class scbTimer
{
	static scbTimer* m_Instance;

	unsigned long long m_Time;

	deque<scbAbstractScheme*> m_RecalculateDeque;
	list<scbAbstractSchemeDevice*> m_IdleList;
	deque<scbTimerRecord> m_TimerDeque;

public:
	scbTimer ();
	~scbTimer ();

	void AddSchemeToRecalculate ( scbAbstractScheme* scheme );
	void DeleteSchemeToRecalculate ( scbAbstractScheme* scheme );

	void AddIdleTimer ( scbAbstractSchemeDevice* device );
	void DeleteIdleTimer ( scbAbstractSchemeDevice* device );

	void AddTimeToWork ( scbAbstractSchemeDevice* device, unsigned long long delay, int signal );
	void DeleteTimeToWork ( scbAbstractSchemeDevice* device );
	void DeleteTimeToWork ( scbAbstractSchemeDevice* device, int signal );
	void ChangeTimeToWork ( scbAbstractSchemeDevice* device, unsigned long long delay );
	void ChangeTimeToWork ( scbAbstractSchemeDevice* device, int signal, unsigned long long delay );

	void Time ();
	unsigned long long GetWorkingTime () const;
	
	static scbTimer* Instance ();
};

inline scbTimer* scbTimer::Instance ()
{
	return m_Instance;
}

inline unsigned long long scbTimer::GetWorkingTime () const
{
	return this->m_Time;
}

inline void scbTimer::AddSchemeToRecalculate ( scbAbstractScheme* scheme )
{
	this->m_RecalculateDeque.push_back ( scheme );
}

inline void scbTimer::DeleteSchemeToRecalculate ( scbAbstractScheme* scheme )
{
	auto rem = remove ( this->m_RecalculateDeque.begin (), this->m_RecalculateDeque.end (), scheme );
	this->m_RecalculateDeque.erase ( rem, this->m_RecalculateDeque.cend ());
}

inline void scbTimer::AddIdleTimer ( scbAbstractSchemeDevice* device )
{
	this->m_IdleList.push_back ( device );
}

inline void scbTimer::DeleteIdleTimer ( scbAbstractSchemeDevice* device )
{
	this->m_IdleList.remove ( device );
}
