#pragma once

#include <string>
#include "scbAbstractSchemeDevice.h"

using std::wstring;

/*
	Представляет группу соединений, направленных на одну стороннюю схему,
	соответственно, если один выход схемы расходится по нескольким схемам -
	это соединение будет присутствовать в scbSchemeOutput каждого направления
*/

class scbSchemeOutput : public scbAbstractSchemeDevice
{
	wstring* m_TargetSchemeName;
	scbAbstractScheme* m_TargetScheme;
	int m_Id;

public:
	scbSchemeOutput ( scbAbstractScheme* ownerShema, const wstring& name, int id );
	virtual ~scbSchemeOutput () override;

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;

	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается схемой-хозяином после расчета
};

