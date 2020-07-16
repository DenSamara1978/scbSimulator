#include "LightSignalScheme.h"
#include "LightSignalLamp.h"
#include "..\util\Color.h"
#include "..\util\range.h"

using namespace scb;

using util::Color;
using util::inRange;

LightSignalScheme::LightSignalScheme(const wstring& name) :
	AbstractScheme(name)
{
	this->status[0] = 0;
	this->status[1] = 0;
	for (int i = 0; i < 13; i++)
		this->lampIndex[i] = -1;
}

LightSignalScheme::~LightSignalScheme()
{
	for (int i = 0; i < 13; ++i)
		this->lampIndex[i] = -1;
}

void LightSignalScheme::setOutput(int index, const wstring& name, int block)
{
	// Пустой вызов
}

bool LightSignalScheme::setLamp(int index, LampPurpose type)
{
	auto isInRange = inRange(index, this->devices.size());
	if (!isInRange)
		return false;
	if (this->devices[index] != nullptr)
		return false;

	// Проверка отсутствия повторения назначений
	if ((type == LampPurpose::Red) and (this->lampIndex[0] != -1)) return false;
	if ((type == LampPurpose::Blue) and (this->lampIndex[1] != -1)) return false;
	if ((type == LampPurpose::White) and ((this->lampIndex[2] != -1) or (this->lampIndex[3] != -1))) return false;
	if ((type == LampPurpose::FirstWhite) and (this->lampIndex[2] != -1)) return false;
	if ((type == LampPurpose::SecondWhite) and (this->lampIndex[3] != -1)) return false;
	if ((type == LampPurpose::Yellow) and ((this->lampIndex[4] != -1) or (this->lampIndex[5] != -1) or (this->lampIndex[6] != -1))) return false;
	if ((type == LampPurpose::FirstYellow) and (this->lampIndex[4] != -1)) return false;
	if ((type == LampPurpose::SecondYellow) and (this->lampIndex[5] != -1)) return false;
	if ((type == LampPurpose::ThirdYellow) and (this->lampIndex[6] != -1)) return false;
	if ((type == LampPurpose::Green) and ((this->lampIndex[7] != -1) or (this->lampIndex[8] != -1))) return false;
	if ((type == LampPurpose::FirstGreen) and (this->lampIndex[7] != -1)) return false;
	if ((type == LampPurpose::SecondGreen) and (this->lampIndex[8] != -1)) return false;
	if ((type == LampPurpose::GreenStrip) and ((this->lampIndex[9] != -1) or (this->lampIndex[10] != -1))) return false;
	if ((type == LampPurpose::FirstGreenStrip) and (this->lampIndex[9] != -1)) return false;
	if ((type == LampPurpose::SecondGreenStrip) and (this->lampIndex[10] != -1)) return false;
	if ((type == LampPurpose::BreakArrow) and ((this->lampIndex[11] != -1) or (this->lampIndex[12] != -1))) return false;
	if ((type == LampPurpose::FirstBreakArrow) and (this->lampIndex[11] != -1)) return false;
	if ((type == LampPurpose::SecondBreakArrow) and (this->lampIndex[12] != -1)) return false;

	// Создание новой лампы
	LightSignalLamp* lamp = new LightSignalLamp(this);
	this->devices[index] = lamp;
	switch (type)
	{
		case LampPurpose::Red:
			lamp->setColor(Color::Red);
			this->lampIndex[0] = index;
			break;
		case LampPurpose::Yellow:
		case LampPurpose::FirstYellow:
			lamp->setColor(Color::Yellow);
			this->lampIndex[4] = index;
			break;
		case LampPurpose::SecondYellow:
			lamp->setColor(Color::Yellow);
			this->lampIndex[5] = index;
			break;
		case LampPurpose::ThirdYellow:
			lamp->setColor(Color::Yellow);
			this->lampIndex[6] = index;
			break;
		case LampPurpose::Green:
		case LampPurpose::FirstGreen:
			lamp->setColor(Color::Green);
			this->lampIndex[7] = index;
			break;
		case LampPurpose::SecondGreen:
			lamp->setColor(Color::Green);
			this->lampIndex[8] = index;
			break;
		case LampPurpose::GreenStrip:
		case LampPurpose::FirstGreenStrip:
			lamp->setColor(Color::Green);
			this->lampIndex[9] = index;
			break;
		case LampPurpose::SecondGreenStrip:
			lamp->setColor(Color::Green);
			this->lampIndex[10] = index;
			break;
		case LampPurpose::Blue:
			lamp->setColor(Color::Blue);
			this->lampIndex[1] = index;
			break;
		case LampPurpose::White:
		case LampPurpose::FirstWhite:
			lamp->setColor(Color::White);
			this->lampIndex[2] = index;
			break;
		case LampPurpose::SecondWhite:
			lamp->setColor(Color::White);
			this->lampIndex[3] = index;
			break;
		case LampPurpose::BreakArrow:
		case LampPurpose::FirstBreakArrow:
			lamp->setColor(Color::Milk);
			this->lampIndex[11] = index;
			break;
		case LampPurpose::SecondBreakArrow:
			lamp->setColor(Color::Milk);
			this->lampIndex[12] = index;
			break;
	}
	return true;
}

void LightSignalScheme::initialize()
{
	// Пустой вызов
}

void LightSignalScheme::recalculate()
{
	// пустой вызов
	this->markRecalculated();
}

void LightSignalScheme::setStatusBit(int bit)
{
	// пустой вызов
}

void LightSignalScheme::resetStatusBit(int bit)
{
	// пустой вызов
}

void LightSignalScheme::correctInputStatus(const OutputStream& maskOn, const OutputStream& maskOff, int id)
{
	/* По устройствам есть фиксированные битовые карты

	для светофора каждый из четырех битов означает:
	0 - режим ДСН
	1 - режим ночь
	2 - режим день
	3 - 25-ваттная лампа

	биты 0, 1, 2, 3 - красный огонь
	биты 4, 5, 6, 7 - синий огонь
	биты 8, 9, 10, 11 - первый белый огонь
	биты 12, 13, 14, 15 - второй белый огонь
	биты 16, 17, 18, 19 - первый желтый огонь
	биты 20, 21, 22, 23 - второй желтый огонь
	биты 24, 25, 26, 27 - третий желтый огонь
	биты 28, 29, 30, 31 - первый зеленый огонь
	биты 32, 33, 34, 35 - вторый зеленый огонь
	биты 36, 37, 38, 39 - первая зеленая полоса
	биты 40, 41, 42, 43 - вторая зеленая полоса
	биты 44, 45, 46, 47 - первый световой указатель скорости
	биты 48, 49, 50, 51 - первый световой указатель скорости

	*/

	// Используется только нулевой элемент состояния
	this->status[0] = this->status[0] & maskOff.mask[0] | maskOn.mask[0];
	this->status[1] = this->status[1] & maskOff.mask[1] | maskOn.mask[1];

	OutputStream param;

	param.mask[0] = this->status[0];
	for (int i = 0; i < 8; i++)
	{
		if (this->lampIndex[i] != -1)
			this->devices[this->lampIndex[i]]->changeStatus(param); // Предполагаются лампы - передача параметров упрощена
		param.mask[0] >>= 4;
	}

	param.mask[0] = this->status[1];
	for (int i = 9; i < 13; i++)
	{
		if (this->lampIndex[i] != -1)
			this->devices[this->lampIndex[i]]->changeStatus(param); // Предполагаются лампы - передача параметров упрощена
		param.mask[0] >>= 4;
	}
}
