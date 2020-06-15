#pragma once

#include "scbSchemeRelay.h"

class scbRelay_PMPUSH_150_150 : public scbSchemeRelay
{
public:
	scbRelay_PMPUSH_150_150 ( const wstring& name, bool plugable );
	virtual ~scbRelay_PMPUSH_150_150 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
