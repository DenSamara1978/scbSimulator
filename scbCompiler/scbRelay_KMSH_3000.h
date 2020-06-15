#pragma once

#include "scbSchemeRelay.h"

class scbRelay_KMSH_3000 : public scbSchemeRelay
{
public:
	scbRelay_KMSH_3000 ( const wstring& name, bool plugable );
	virtual ~scbRelay_KMSH_3000 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
