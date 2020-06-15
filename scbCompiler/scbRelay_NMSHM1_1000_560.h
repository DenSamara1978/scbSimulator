#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM1_1000_560 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM1_1000_560 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSHM1_1000_560 () override;

	virtual int FixDescription () override;
};
