#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMPSH2_400 : public scbSchemeRelay
{
public:
	scbRelay_NMPSH2_400 ( const wstring& name );
	virtual ~scbRelay_NMPSH2_400 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
