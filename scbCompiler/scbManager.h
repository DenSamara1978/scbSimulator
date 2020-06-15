#pragma once

#include "scbMessage.h"
#include <fstream>

#include "scbParseInfo.h"
#include "scbMessagePool.h"

using namespace std;

class scbManager
{
protected:
	scbMessagePool* m_MessagePool;

public:
	static const int ParameterNameShift = 10'000;

	scbManager ();
	virtual ~scbManager ();

	void SetMessagePool ( scbMessagePool* pool );
	virtual void Clear () abstract;
	virtual int Parse ( const scbParseInfo& info ) abstract;
	virtual void Compile () abstract;
	virtual void FlushBinFile ( const ofstream& file ) abstract;
	virtual void FlushLogFile ( const wofstream& file ) abstract;
};

inline void scbManager::SetMessagePool ( scbMessagePool* pool )
{
	this->m_MessagePool = pool;
}
