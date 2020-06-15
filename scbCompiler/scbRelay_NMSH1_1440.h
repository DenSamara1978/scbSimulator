#pragma once

#include "scbSchemeRelay.h"

class scbRelay_NMSH1_1440 : public scbSchemeRelay
{
    int m_RequirementId;
    int m_RequirementFrom;
    int m_RequirementTo;

public:
	scbRelay_NMSH1_1440 ( const wstring& name, bool plugable );
	virtual ~scbRelay_NMSH1_1440 () override;

	virtual int SetJumper ( const wstring& jumper ) override;
    virtual int SetRequirement ( int req ) override;
    virtual int SetRequirementFrom ( int from ) override;
	virtual int SetRequirementTo ( int to ) override;
	virtual int FixDescription () override;
};
