#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMPSH_900 : public scbSchemeRelay
{
public:
	scbRelay_NMPSH_900 ( const wstring& name );
	virtual ~scbRelay_NMPSH_900 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
