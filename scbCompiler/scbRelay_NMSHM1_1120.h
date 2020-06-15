#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM1_1120 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM1_1120 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSHM1_1120 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
