#pragma once

#include "Message.h"
#include <fstream>

#include "ParseInfo.h"
#include "MessagePool.h"

using namespace std;

class Manager
{
public:
	static const int parameterNameShift = 10'000;

	Manager();
	virtual ~Manager();

	void setMessagePool(MessagePool* pool);
	virtual void clear() abstract;
	virtual int parse(const ParseInfo& info) abstract;
	virtual void compile() abstract;
	virtual void flushBinFile(const ofstream& file) abstract;
	virtual void flushLogFile(const wofstream& file) abstract;

protected:
	MessagePool* messagePool;

};

inline void Manager::setMessagePool(MessagePool* pool)
{
	this->messagePool = pool;
}
