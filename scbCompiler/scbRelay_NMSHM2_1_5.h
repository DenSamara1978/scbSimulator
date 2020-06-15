#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM2_1_5 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM2_1_5 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSHM2_1_5 () override;

	virtual int FixDescription () override;
};
