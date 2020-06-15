#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KMSH_750 : public scbSchemeRelay
{
public:
	scbRelay_KMSH_750 ( const wstring& name );
	virtual ~scbRelay_KMSH_750 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
