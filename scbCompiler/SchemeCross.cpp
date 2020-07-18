#include "SchemeCross.h"

SchemeCross::SchemeCross(const wstring& name) :
	SchemeObject(name),
	order(0),
	count(1)
{
	this->contacts.fill(0);
}

SchemeCross::~SchemeCross()
{
}

int SchemeCross::setLocation(const wstring& location)
{
	// Проверка возможности установки этого типа реле в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
	this->location = location;
	return 0;
}

int SchemeCross::setPlacement(int id, Description::PlacementType placementType)
{
	this->placement = id;
	return (Description::checkCaseInPlacement(Description::DeviceCase::Cross, placementType)) ? 0 : -1;
}

int SchemeCross::setOrder(int order)
{
	this->order = order;
	return 0;
}

int SchemeCross::setCable(const wstring& cable)
{
	this->cable = cable;
	return 0;
}

int SchemeCross::setContact(const wstring& contact)
{
	int cont = -1;
	if ((contact == L"1-2") or (contact == L"2-1"))
		cont = 0;
	else if ((contact == L"3-4") or (contact == L"4-3"))
		cont = 1;
	else if ((contact == L"5-6") or (contact == L"6-5"))
		cont = 2;
	else if ((contact == L"7-8") or (contact == L"8-7"))
		cont = 3;
	else if ((contact == L"9-10") or (contact == L"10-9"))
		cont = 4;
	else if ((contact == L"11-12") or (contact == L"12-11"))
		cont = 5;
	else if ((contact == L"13-14") or (contact == L"14-13"))
		cont = 6;
	else if ((contact == L"15-16") or (contact == L"16-15"))
		cont = 7;

	if (cont == -1)
		return -1;
	else if (this->contacts[cont] == 1)
		return 1;
	else
	{
		this->contacts[cont] = 1;
		return 0;
	}
}

int SchemeCross::setCount(int count)
{
	this->count = count;
	return 0;
}

int SchemeCross::fixDescription()
{
	return 0;
}

const SchemeObject::ObjectType SchemeCross::getObjectType() const
{
	return SchemeObject::ObjectType::Cross;
}

