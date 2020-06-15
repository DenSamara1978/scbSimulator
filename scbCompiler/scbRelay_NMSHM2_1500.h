#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM2_1500 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM2_1500 ( const wstring& name );
	virtual ~scbRelay_NMSHM2_1500 () override;

	virtual int FixDescription () override;
};
