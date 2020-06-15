#pragma once

class scbAbstractSchemeDevice;

class scbTimerRecord
{
	friend class scbTimer;

	scbAbstractSchemeDevice* m_Device;
	scbTimerRecord* m_Prev;
	scbTimerRecord* m_Next;
	unsigned long long m_TimeToWork;
	int m_Signal;

public:
	scbTimerRecord ( scbAbstractSchemeDevice* device, unsigned long long time, int signal );
};

inline scbTimerRecord::scbTimerRecord ( scbAbstractSchemeDevice* device, unsigned long long time, int signal ) :
	m_TimeToWork ( time ),
	m_Device ( device ),
	m_Signal ( signal ),
	m_Next ( nullptr ),
	m_Prev ( nullptr )
{
}
