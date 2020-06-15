#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSH4_3 : public scbSchemeRelay
{
public:
	scbRelay_NMSH4_3 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSH4_3 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
