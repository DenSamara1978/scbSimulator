#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KDR1M_435 : public scbSchemeRelay
{
public:
	scbRelay_KDR1M_435 ( const wstring& name );
	virtual ~scbRelay_KDR1M_435 () override;

	virtual int FixDescription () override;
};
