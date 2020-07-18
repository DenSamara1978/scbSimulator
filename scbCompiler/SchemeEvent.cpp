#include "SchemeEvent.h"

SchemeEvent::SchemeEvent() :
	probablityClass(ProbablityClass::No)
{
}

int SchemeEvent::setProbablityClass(const wstring& name)
{
	if (name == L"Äâèãàòåëü ÌÑÏ")
		this->probablityClass = ProbablityClass::EngineMSP;
	else if (name == L"Äâèãàòåëü ÌÑÀ")
		this->probablityClass = ProbablityClass::EngineMSA;
	else if (name == L"ÁÄÐ-Ì")
		this->probablityClass = ProbablityClass::BDR_M;
	else
		return -1;
	return 0;
}
