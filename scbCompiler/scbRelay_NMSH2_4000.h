#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSH2_4000 : public scbSchemeRelay
{
    int m_RequirementId;
    int m_RequirementFrom;
    int m_RequirementTo;

public:
	scbRelay_NMSH2_4000 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSH2_4000 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
    virtual int SetRequirement ( int req ) override;
    virtual int SetRequirementFrom ( int from ) override;
	virtual int SetRequirementTo ( int to ) override;
	virtual int FixDescription () override;
};
