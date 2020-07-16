#pragma once

#include <string>
#include "AbstractSchemeDevice.h"

using std::wstring;
using namespace scb;

/*
	Представляет группу соединений, направленных на одну стороннюю схему,
	соответственно, если один выход схемы расходится по нескольким схемам -
	это соединение будет присутствовать в scbSchemeOutput каждого направления
*/
namespace scb
{
	class SchemeOutput : public AbstractSchemeDevice
	{
	public:
		SchemeOutput(AbstractScheme* ownerShema, const wstring& name, int id);
		virtual ~SchemeOutput() override;

		virtual void initialize() override;
		virtual void idleTimer(unsigned long long time) override;

		virtual void changeStatus(const OutputStream& param) override; // Вызывается схемой-хозяином после расчета

	private:
		wstring* targetSchemeName;
		AbstractScheme* targetScheme;
		int id;

	};
}
