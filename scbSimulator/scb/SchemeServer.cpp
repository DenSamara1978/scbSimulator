#include "SchemeServer.h"
#include "PultTabloScheme.h"
#include "LightSignalScheme.h"
#include "MotorDriveScheme.h"
#include "Scheme.h"
#include "BusScheme.h"
#include "ChainScheme.h"
#include "SchemeSse16.h"
#include "SchemeSse32.h"
#include "SchemeSse64.h"
#include "SchemeSse128.h"
#include "SchemeSse256.h"
#include "SchemeAvx64.h"
#include "SchemeAvx128.h"
#include "SchemeAvx256.h"
#include "SchemeGpr32.h"
#include "SchemeGpr64.h"
#include "SchemeGpr128.h"
#include "SchemeGpr256.h"

using namespace scb;

SchemeServer* SchemeServer::instance = nullptr;

SchemeServer::SchemeServer()
{
	SchemeServer::instance = this;
}

SchemeServer::~SchemeServer()
{
	for (auto& scheme : this->schemes)
	{
		delete scheme;
		scheme = nullptr;
	}
	SchemeServer::instance = nullptr;
}

LightSignalScheme* SchemeServer::addNewLightSignalScheme(const wstring& name, vector<LightSignalScheme::LampPurpose>& lamps)
{
	LightSignalScheme* lightSignal = new LightSignalScheme(name);
	this->schemes.push_back(lightSignal);
	lightSignal->setDeviceCount(static_cast<int>(lamps.size()));
	int counter = 0;
	for (auto& lamp : lamps)
	{
		if (!lightSignal->setLamp(counter++, lamp))
			return nullptr;
	}
	return lightSignal;
}

MotorDriveScheme* SchemeServer::addNewMotorDriveScheme(const wstring& name)
{
	MotorDriveScheme* motorDriveScheme = new MotorDriveScheme(name);
	this->schemes.push_back(motorDriveScheme);
	return motorDriveScheme;
}

Scheme* SchemeServer::addNewScheme(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives)
{
	Scheme* scheme = new SchemeGpr256(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives);
	this->schemes.push_back(scheme);
	return scheme;
}

BusScheme* SchemeServer::addNewBusScheme(const wstring& name, int length)
{
	BusScheme* busScheme = new BusScheme(name, length);
	this->schemes.push_back(busScheme);
	return busScheme;
}

ChainScheme* SchemeServer::addNewChainScheme(const wstring& name, int length)
{
	ChainScheme* chainScheme = new ChainScheme(name, length);
	this->schemes.push_back(chainScheme);
	return chainScheme;
}

PultTabloScheme* SchemeServer::addNewPultTablo(const wstring& name)
{
	PultTabloScheme* pultTabloScheme = new PultTabloScheme(name);
	this->schemes.push_back(pultTabloScheme);
	return pultTabloScheme;
}

PultTabloScheme* SchemeServer::findPultTabloSchemeByName(const wstring& name)
{
	return dynamic_cast<PultTabloScheme*>(findAbstractSchemeByName(name));
}

Scheme* SchemeServer::findSchemeByName(const wstring& name)
{
	return dynamic_cast<Scheme*>(findAbstractSchemeByName(name));
}

BusScheme* SchemeServer::findBusSchemeByName(const wstring& name)
{
	return dynamic_cast<BusScheme*>(findAbstractSchemeByName(name));
}

ChainScheme* SchemeServer::findChainSchemeByName(const wstring& name)
{
	return dynamic_cast<ChainScheme*>(findAbstractSchemeByName(name));
}

LightSignalScheme* SchemeServer::findLightSignalSchemeByName(const wstring& name)
{
	return dynamic_cast<LightSignalScheme*>(findAbstractSchemeByName(name));
}

MotorDriveScheme* SchemeServer::findMotorDriveSchemeByName(const wstring& name)
{
	return dynamic_cast<MotorDriveScheme*>(findAbstractSchemeByName(name));
}

void SchemeServer::initialize()
{
	for (auto& scheme : this->schemes)
	{
		scheme->initialize();
		scheme->markToRecalculate();
	}
}

void SchemeServer::recalculateSchemes()
{
	while (!this->recalculateDeque.empty())
	{
		this->recalculateDeque.front()->recalculate();
		this->recalculateDeque.pop_front();
	}
}

void SchemeServer::getStatistic()
{
	unsigned long long countM2, countM3;
	for (auto& scheme : this->schemes)
	{
		if (scheme->isA(L"Светофор.М2.Исполнение"))
			countM2 = scheme->getAverageWorkingTime();
		if (scheme->isA(L"Светофор.М3.Исполнение"))
			countM3 = scheme->getAverageWorkingTime();
	}
	countM2;
	countM3;
}