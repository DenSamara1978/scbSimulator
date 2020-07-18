#pragma once

#include "Manager.h"

class DeviceManager : public Manager
{
public:
	DeviceManager ();
	virtual ~DeviceManager () override;

	virtual int parse ( const ParseInfo& info ) override;
	virtual void clear () override;
	virtual void compile () override;
	virtual void flushBinFile ( const ofstream& file ) override;
	virtual void flushLogFile ( const wofstream& file ) override;

private:
	/* Режим обработки - номер блока
	0 - Шапка шлюза (ШЛЮЗ)
	1 - ВХОДЫ
	2 - ВЫХОДЫ
	*/
	int mode;
	int submode; // Подрежим - разбор внутри блока


	int parseDevice(const ParseInfo& info);
	int parseInput(const ParseInfo& info);
	int parseOutput(const ParseInfo& info);

};