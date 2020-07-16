#include "SchemeServer.h"
#include "PultTabloScheme.h"
#include "LightSignalScheme.h"
#include "MotorDriveScheme.h"
#include "Scheme.h"
#include "BusScheme.h"
#include "ChainScheme.h"
#include "SchemeSse128.h"

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
	Scheme* scheme = new SchemeSse128(name, nPrepareCircuits, nMainCircuits, nStaticSensitives, nDynamicSensitives);
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
