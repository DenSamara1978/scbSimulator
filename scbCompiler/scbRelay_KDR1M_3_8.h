#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KDR1M_3_8 : public scbSchemeRelay
{
public:
	scbRelay_KDR1M_3_8 ( const wstring& name );
	virtual ~scbRelay_KDR1M_3_8 () override;

	virtual int FixDescription () override;
};
