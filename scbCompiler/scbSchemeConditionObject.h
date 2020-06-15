#pragma once

#include <string>
#include <vector>
#include "scbSchemeCondition.h"

using std::vector;
using std::wstring;

class scbSchemeConditionObject
{
protected:

	vector<scbSchemeCondition> m_Conditions;

public:

		// Добавляет новую группу условий
	void AddNewConditionGroup ();
		// Добавляет новое условие в текущую группу, возврат - ( 0 - все Ок, 1 - повтор описателя, -1 - неверный описатель ), ( идентификатор описателя, либо -1 )
	pair<int, int> AddCondition ( int conditionParam, const wstring& name );
		// Проверяет наличие повторного идентичного набора условий
	bool CheckForEqualConditions () const;

	const vector<tuple<int, int, bool>>& GetLastConditions () const;
};

inline void scbSchemeConditionObject::AddNewConditionGroup ()
{
	this->m_Conditions.emplace_back ();
}

inline pair<int, int> scbSchemeConditionObject::AddCondition ( int conditionParam, const wstring& name )
{
	return this->m_Conditions.back ().AddCondition ( conditionParam, name );
}

inline const vector<tuple<int, int, bool>>& scbSchemeConditionObject::GetLastConditions () const
{
	return this->m_Conditions.back ().GetDescriptionTags ();
}
