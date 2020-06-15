#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KDR1_200 : public scbSchemeRelay
{
public:
	scbRelay_KDR1_200 ( const wstring& name );
	virtual ~scbRelay_KDR1_200 () override;

	virtual int FixDescription () override;
};
