#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM1_11 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM1_11 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSHM1_11 () override;

	virtual int FixDescription () override;
};
