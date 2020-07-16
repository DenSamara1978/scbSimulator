#pragma once

#include <string>
#include "AbstractSchemeDevice.h"

using std::wstring;
using namespace scb;

/*
	������������ ������ ����������, ������������ �� ���� ��������� �����,
	��������������, ���� ���� ����� ����� ���������� �� ���������� ������ -
	��� ���������� ����� �������������� � scbSchemeOutput ������� �����������
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

		virtual void changeStatus(const OutputStream& param) override; // ���������� ������-�������� ����� �������

	private:
		wstring* targetSchemeName;
		AbstractScheme* targetScheme;
		int id;

	};
}
