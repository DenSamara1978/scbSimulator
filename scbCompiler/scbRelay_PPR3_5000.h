#pragma once

#include "scbSchemeRelay.h"

class scbRelay_PPR3_5000 : public scbSchemeRelay
{
public:
	scbRelay_PPR3_5000 ( const wstring& name );
	virtual ~scbRelay_PPR3_5000 () override;

	virtual int FixDescription () override;
};
