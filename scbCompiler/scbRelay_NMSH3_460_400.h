#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSH3_460_400 : public scbSchemeRelay
{
public:
	scbRelay_NMSH3_460_400 ( const wstring& name );
	virtual ~scbRelay_NMSH3_460_400 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
	virtual int FixDescription () override;
};
