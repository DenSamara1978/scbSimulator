#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KMSH_450 : public scbSchemeRelay
{
public:
	scbRelay_KMSH_450 ( const wstring& name, bool plugable );
	virtual ~scbRelay_KMSH_450 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
