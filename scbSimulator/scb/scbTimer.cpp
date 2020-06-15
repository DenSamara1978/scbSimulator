#include <windows.h>
#include <algorithm>

#include "scbTimer.h"
#include "scbAbstractScheme.h"
#include "scbAbstractSchemeDevice.h"

scbTimer* scbTimer::m_Instance = nullptr;

scbTimer::scbTimer ()
{
	m_Instance = this;
}

scbTimer::~scbTimer ()
{
	m_Instance = nullptr;
}

void scbTimer::Time ()
{
	this->m_Time = GetTickCount64 ();

	// Выбрать из очереди готовые таймеры
	while ( !this->m_TimerDeque.empty () )
	{
		auto rec = this->m_TimerDeque.front ();
		if ( this->m_Time < rec.m_TimeToWork )
			break;
		unsigned long long time = rec.m_TimeToWork;
		rec.m_Device->TimeToWork ( rec.m_Signal, time );
		this->m_TimerDeque.pop_front ();
	}

	// Рассчитать схемы из очереди
	while ( !this->m_RecalculateDeque.empty () )
	{
		this->m_RecalculateDeque.front ()->Recalculate ();
		this->m_RecalculateDeque.pop_front ();
	}

	// Раздать свободный таймер всем нуждающимся устройствам
	auto now = this->m_IdleList.cbegin ();
	while ( now != this->m_IdleList.cend ())
		( *( now++ ))->IdleTimer ( this->m_Time );
}

void scbTimer::AddTimeToWork ( scbAbstractSchemeDevice* device, unsigned long long delay, int signal )
{
	if ( !device ) return;

	unsigned long long time = this->m_Time + delay;
	auto rec = find_if ( this->m_TimerDeque.cbegin (), this->m_TimerDeque.cend (), [time] ( const scbTimerRecord& rec )->bool { return time >= rec.m_TimeToWork; } );
	this->m_TimerDeque.emplace ( rec, device, time, signal );
}

void scbTimer::DeleteTimeToWork ( scbAbstractSchemeDevice* device )
{
	if ( !device ) return;

	auto rem = remove_if ( this->m_TimerDeque.begin (), this->m_TimerDeque.end (), [device] ( const scbTimerRecord& rec )->bool { return device == rec.m_Device; } );
	this->m_TimerDeque.erase ( rem, this->m_TimerDeque.cend () );
}

void scbTimer::DeleteTimeToWork ( scbAbstractSchemeDevice* device, int signal )
{
	if ( !device ) return;

	auto rem = remove_if ( this->m_TimerDeque.begin (), this->m_TimerDeque.end (), [device, signal] ( const scbTimerRecord& rec )->bool { return ( device == rec.m_Device ) && ( signal == rec.m_Signal ); } );
	this->m_TimerDeque.erase ( rem, this->m_TimerDeque.cend () );
}

void scbTimer::ChangeTimeToWork ( scbAbstractSchemeDevice* device, unsigned long long delay )
{
	if ( !device ) return;

	auto rem = find_if ( this->m_TimerDeque.cbegin (), this->m_TimerDeque.cend (), [device] ( const scbTimerRecord& rec )->bool { return device == rec.m_Device; } );
	int signal = ( *rem ).m_Signal;
	this->m_TimerDeque.erase ( rem );
	this->AddTimeToWork ( device, delay, signal );
}

void scbTimer::ChangeTimeToWork ( scbAbstractSchemeDevice* device, int signal, unsigned long long delay )
{
	if ( !device ) return;

	this->DeleteTimeToWork ( device, signal );
	this->AddTimeToWork ( device, delay, signal );
}
