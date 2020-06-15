#pragma once

#include "scbSchemeRelay.h"

class scbRelay_ANVSH2_2400 : public scbSchemeRelay
{
public:
	scbRelay_ANVSH2_2400 ( const wstring& name );
	virtual ~scbRelay_ANVSH2_2400 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
