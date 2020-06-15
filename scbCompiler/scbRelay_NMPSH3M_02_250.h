#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMPSH3M_02_250 : public scbSchemeRelay
{
public:
	scbRelay_NMPSH3M_02_250 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMPSH3M_02_250 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
