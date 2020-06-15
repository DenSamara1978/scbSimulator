#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSHM2_3000 : public scbSchemeRelay
{
public:
	scbRelay_NMSHM2_3000 ( const wstring& name );
	virtual ~scbRelay_NMSHM2_3000 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
