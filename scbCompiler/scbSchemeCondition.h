#pragma once

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::tuple;
using std::wstring;

class scbSchemeCondition
{
	vector<tuple<int, int, bool>> m_Conditions; // Параметр, Описатель, Отрицание

public:
		// Добавляет новое условие, возврат - ( 0 - все Ок, 1 - повтор описателя, -1 - неверный описатель ), ( идентификатор описателя, либо -1 )
	pair<int, int> AddCondition ( int conditionParam, const wstring& name );
		// Проверяется наличие описателя в непараметрических условиях
	bool CheckPresence ( int id ) const;
		// Проверяет повторение описаний
	bool CheckForEqual ( const scbSchemeCondition& cond ) const;

	const vector<tuple<int, int, bool>>& GetDescriptionTags () const;
};

inline const vector<tuple<int, int, bool>>& scbSchemeCondition::GetDescriptionTags () const
{
	return this->m_Conditions;
}
