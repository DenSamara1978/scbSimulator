#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KDR1_280 : public scbSchemeRelay
{
public:
	scbRelay_KDR1_280 ( const wstring& name );
	virtual ~scbRelay_KDR1_280 () override;

	virtual int FixDescription () override;
};
