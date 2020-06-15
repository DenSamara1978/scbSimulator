#pragma once

#include <vector>
#include "scbComplexName.h"
#include "scbSchemeConditionObject.h"

using std::vector;

class scbSchemeExternalLink : public scbSchemeConditionObject
{
	scbComplexName m_Descriptor;
	bool m_IsNecesserily;
	int m_DescriptionTag;

public:
	scbSchemeExternalLink ();

	scbComplexName& GetDescriptor ();
    const scbComplexName& GetDescriptor () const;
    void SetNecesserily ();
	pair<int, int> SetDescriptionTag ( const wstring& name );
	int GetDescriptionTag () const;

		// Проверяет наличие описателя в списке беспараметрических условий
	bool CheckPresenceInConditionsAndDescription ( int id ) const;
};

inline scbSchemeExternalLink::scbSchemeExternalLink () :
	m_IsNecesserily ( false ),
	m_DescriptionTag ( -1 )
{
}

inline scbComplexName& scbSchemeExternalLink::GetDescriptor ()
{
	return this->m_Descriptor;
}

inline const scbComplexName& scbSchemeExternalLink::GetDescriptor () const
{
    return this->m_Descriptor;
}

inline void scbSchemeExternalLink::SetNecesserily ()
{
	this->m_IsNecesserily = true;
}

inline int scbSchemeExternalLink::GetDescriptionTag () const
{
	return this->m_DescriptionTag;
}
