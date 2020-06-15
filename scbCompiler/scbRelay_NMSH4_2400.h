#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSH4_2400 : public scbSchemeRelay
{
public:
	scbRelay_NMSH4_2400 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSH4_2400 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
