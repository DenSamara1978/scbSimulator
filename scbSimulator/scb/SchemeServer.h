#pragma once

#include <string>
#include <vector>
#include <deque>
#include "AbstractScheme.h"
#include "LightSignalScheme.h"

using std::wstring;
using std::vector;
using std::deque;

namespace scb
{
	class Scheme;
	class PultTabloScheme;
	class MotorDriveScheme;
	class LightSignalScheme;
	class BusScheme;
	class ChainScheme;

	class SchemeServer
	{
	public:
		~SchemeServer();

		static SchemeServer* getInstance();

		LightSignalScheme* addNewLightSignalScheme(const wstring& name, vector<LightSignalScheme::LampPurpose>& lamps);
		MotorDriveScheme* addNewMotorDriveScheme(const wstring& name);
		Scheme* addNewScheme(const wstring& name, int nPrepareCircuits, int nMainCircuits, int nStaticSensitives, int nDynamicSensitives);
		BusScheme* addNewBusScheme(const wstring& name, int length);
		ChainScheme* addNewChainScheme(const wstring& name, int length);
		PultTabloScheme* addNewPultTablo(const wstring& name);

		AbstractScheme* findAbstractSchemeByName(const wstring& name);
		Scheme* findSchemeByName(const wstring& name);
		BusScheme* findBusSchemeByName(const wstring& name);
		ChainScheme* findChainSchemeByName(const wstring& name);
		PultTabloScheme* findPultTabloSchemeByName(const wstring& name);
		MotorDriveScheme* findMotorDriveSchemeByName(const wstring& name);
		LightSignalScheme* findLightSignalSchemeByName(const wstring& name);

		void initialize();

		void recalculateSchemes();
		void addSchemeToRecalculate(AbstractScheme* scheme);
		void deleteSchemeToRecalculate(AbstractScheme* scheme);

	private:
		SchemeServer();

		vector<AbstractScheme*> schemes;
		deque<AbstractScheme*> recalculateDeque;

		static SchemeServer* instance;
	};

	inline SchemeServer* SchemeServer::getInstance()
	{
		if (SchemeServer::instance == nullptr)
			SchemeServer::instance = new SchemeServer;
		return SchemeServer::instance;
	}

	inline AbstractScheme* SchemeServer::findAbstractSchemeByName(const wstring& name)
	{
		auto scheme = find_if(this->schemes.cbegin(), this->schemes.cend(), [&] (const AbstractScheme* scheme)->bool { return scheme->isA(name); });
		return (scheme != this->schemes.cend()) ? *scheme : nullptr;
	}

	inline void SchemeServer::addSchemeToRecalculate(AbstractScheme* scheme)
	{
		this->recalculateDeque.push_back(scheme);
	}

	inline void SchemeServer::deleteSchemeToRecalculate(AbstractScheme* scheme)
	{
		auto rem = remove(this->recalculateDeque.begin(), this->recalculateDeque.end(), scheme);
		this->recalculateDeque.erase(rem, this->recalculateDeque.cend());
	}

}