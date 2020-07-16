#include "SchemeOutput.h"
#include "AbstractScheme.h"
#include "SchemeServer.h"

using namespace scb;

SchemeOutput::SchemeOutput(AbstractScheme* ownerScheme, const wstring& name, int id) :
	AbstractSchemeDevice(ownerScheme),
	targetScheme(nullptr),
	id(id)
{
	this->targetSchemeName = new wstring(name);
}

SchemeOutput::~SchemeOutput()
{
	if (this->targetSchemeName != nullptr)
		delete this->targetSchemeName;
}

void SchemeOutput::initialize()
{
	// Ïóñòîé âûçîâ
}

void SchemeOutput::idleTimer(unsigned long long time)
{
	// Ïóñòîé âûçîâ
}

void SchemeOutput::changeStatus(const OutputStream& param)
{
	OutputStream maskOn = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
	OutputStream maskOff = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

	for (auto& conv : this->convertations)
	{
		if ((param.mask[conv.inputElement] & conv.inputMask) != 0)
			maskOn.mask[conv.outputElement] |= conv.outputMask;
		else
			maskOff.mask[conv.outputElement] &= ~conv.outputMask;
	}

	if (this->targetScheme == nullptr)
	{
		if (this->targetSchemeName != nullptr)
		{
			// Ğàçğåøåíèå èìåíè ñõåìû â åå óêàçàòåëü
			this->targetScheme = SchemeServer::getInstance()->findAbstractSchemeByName(*(this->targetSchemeName));
			delete this->targetSchemeName;
			this->targetSchemeName = nullptr;
			if (this->targetScheme == nullptr)
				return;
		}
		else
			return;
	}
	this->targetScheme->correctInputStatus(maskOn, maskOff, this->id);
}
