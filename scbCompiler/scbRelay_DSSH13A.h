#pragma once

#include "scbSchemeRelay.h"

class scbRelay_DSSH13A : public scbSchemeRelay
{
public:
	scbRelay_DSSH13A ( const wstring& name );
	virtual ~scbRelay_DSSH13A () override;

	virtual int FixDescription () override;
};
