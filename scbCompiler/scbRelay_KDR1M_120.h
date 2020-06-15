#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KDR1M_120 : public scbSchemeRelay
{
public:
	scbRelay_KDR1M_120 ( const wstring& name );
	virtual ~scbRelay_KDR1M_120 () override;

	virtual int FixDescription () override;
};
