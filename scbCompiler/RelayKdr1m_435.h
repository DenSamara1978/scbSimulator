#pragma once

#include "SchemeRelay.h"

class RelayKdr1m_435 : public SchemeRelay
{
public:
	RelayKdr1m_435 ( const wstring& name );
	virtual ~RelayKdr1m_435 () override;

	virtual int fixDescription () override;
};
