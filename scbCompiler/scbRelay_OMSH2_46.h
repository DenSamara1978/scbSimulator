#pragma once

#include "scbSchemeRelay.h"

class scbRelay_OMSH2_46 : public scbSchemeRelay
{
public:
	scbRelay_OMSH2_46 ( const wstring& name, bool plugable );
	virtual ~scbRelay_OMSH2_46 () override;

	virtual int FixDescription () override;
};
