#include "scbLightSignal.h"
#include "scbLightSignalLamp.h"

scbLightSignal::scbLightSignal ( const wstring& name ) :
	scbAbstractScheme ( name )
{
	this->m_Status [0] = 0;
	this->m_Status [1] = 0;
	for ( int i = 0; i < 13; i++ )
		this->m_LampIndex [i] = -1;
}

scbLightSignal::~scbLightSignal ()
{
	for ( int i = 0; i < 13; i++ )
		this->m_LampIndex [i] = -1;
}

void scbLightSignal::SetOutput ( int index, const wstring& name, int block )
{
	// Пустой вызов
}

bool scbLightSignal::SetLamp ( int index, LampPurpose type )
{
	if (( index < 0 ) || ( index >= static_cast<int> ( this->m_Devices.size ()))) return false;
	if ( this->m_Devices [index] != nullptr ) return false;

	// Проверка отсутствия повторения назначений
	if ( ( type == LampPurpose::Red ) && ( this->m_LampIndex [0] != -1 ) ) return false;
	if ( ( type == LampPurpose::Blue ) && ( this->m_LampIndex [1] != -1 ) ) return false;
	if ( ( type == LampPurpose::White ) && (( this->m_LampIndex [2] != -1 ) || ( this->m_LampIndex [3] != -1 ))) return false;
	if ( ( type == LampPurpose::FirstWhite ) && ( this->m_LampIndex [2] != -1 ) ) return false;
	if ( ( type == LampPurpose::SecondWhite ) && ( this->m_LampIndex [3] != -1 ) ) return false;
	if ( ( type == LampPurpose::Yellow ) && ( ( this->m_LampIndex [4] != -1 ) || ( this->m_LampIndex [5] != -1 ) || ( this->m_LampIndex [6] != -1 ) ) ) return false;
	if ( ( type == LampPurpose::FirstYellow ) && ( this->m_LampIndex [4] != -1 ) ) return false;
	if ( ( type == LampPurpose::SecondYellow ) && ( this->m_LampIndex [5] != -1 ) ) return false;
	if ( ( type == LampPurpose::ThirdYellow ) && ( this->m_LampIndex [6] != -1 ) ) return false;
	if ( ( type == LampPurpose::Green ) && ( ( this->m_LampIndex [7] != -1 ) || ( this->m_LampIndex [8] != -1 ) ) ) return false;
	if ( ( type == LampPurpose::FirstGreen ) && ( this->m_LampIndex [7] != -1 ) ) return false;
	if ( ( type == LampPurpose::SecondGreen ) && ( this->m_LampIndex [8] != -1 ) ) return false;
	if ( ( type == LampPurpose::GreenStrip ) && ( ( this->m_LampIndex [9] != -1 ) || ( this->m_LampIndex [10] != -1 ) ) ) return false;
	if ( ( type == LampPurpose::FirstGreenStrip ) && ( this->m_LampIndex [9] != -1 ) ) return false;
	if ( ( type == LampPurpose::SecondGreenStrip ) && ( this->m_LampIndex [10] != -1 ) ) return false;
	if ( ( type == LampPurpose::BreakArrow ) && ( ( this->m_LampIndex [11] != -1 ) || ( this->m_LampIndex [12] != -1 ) ) ) return false;
	if ( ( type == LampPurpose::FirstBreakArrow ) && ( this->m_LampIndex [11] != -1 ) ) return false;
	if ( ( type == LampPurpose::SecondBreakArrow ) && ( this->m_LampIndex [12] != -1 ) ) return false;
	
	// Создание новой лампы
	scbLightSignalLamp* lamp = new scbLightSignalLamp ( this );
	this->m_Devices [index] = lamp;
	switch ( type )
	{
	case LampPurpose::Red:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Red );
		this->m_LampIndex [0] = index;
		break;
	case LampPurpose::Yellow:
	case LampPurpose::FirstYellow:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Yellow );
		this->m_LampIndex [4] = index;
		break;
	case LampPurpose::SecondYellow:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Yellow );
		this->m_LampIndex [5] = index;
		break;
	case LampPurpose::ThirdYellow:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Yellow );
		this->m_LampIndex [6] = index;
		break;
	case LampPurpose::Green:
	case LampPurpose::FirstGreen:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Green );
		this->m_LampIndex [7] = index;
		break;
	case LampPurpose::SecondGreen:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Green );
		this->m_LampIndex [8] = index;
		break;
	case LampPurpose::GreenStrip:
	case LampPurpose::FirstGreenStrip:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Green );
		this->m_LampIndex [9] = index;
		break;
	case LampPurpose::SecondGreenStrip:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Green );
		this->m_LampIndex [10] = index;
		break;
	case LampPurpose::Blue:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Blue );
		this->m_LampIndex [1] = index;
		break;
	case LampPurpose::White:
	case LampPurpose::FirstWhite:
		lamp->SetColor ( scbLightSignalLamp::LampColor::White );
		this->m_LampIndex [2] = index;
		break;
	case LampPurpose::SecondWhite:
		lamp->SetColor ( scbLightSignalLamp::LampColor::White );
		this->m_LampIndex [3] = index;
		break;
	case LampPurpose::BreakArrow:
	case LampPurpose::FirstBreakArrow:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Milk );
		this->m_LampIndex [11] = index;
		break;
	case LampPurpose::SecondBreakArrow:
		lamp->SetColor ( scbLightSignalLamp::LampColor::Milk );
		this->m_LampIndex [12] = index;
		break;
	}
	return true;
}

void scbLightSignal::Init ()
{
	// Пустой вызов
}

void scbLightSignal::Recalculate ()
{
	// пустой вызов
	this->MarkRecalculated ();
}

void scbLightSignal::SetStatusBit ( int bit )
{
	// пустой вызов
}

void scbLightSignal::ResetStatusBit ( int bit )
{
	// пустой вызов
}

void scbLightSignal::CorrectInputStatus ( const scbOutputStream& mask_on, const scbOutputStream& mask_off, int id )
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
	this->m_Status [0] = this->m_Status [0] & mask_off.Mask [0] | mask_on.Mask [0];
	this->m_Status [1] = this->m_Status [1] & mask_off.Mask [1] | mask_on.Mask [1];

	scbOutputStream param;

	param.Mask [0] = this->m_Status [0];
	for ( int i = 0; i < 8; i++ )
	{
		if ( this->m_LampIndex [i] != -1 )
			this->m_Devices [this->m_LampIndex [i]]->ChangeStatus ( param ); // Предполагаются лампы - передача параметров упрощена
		param.Mask [0] >>= 4;
	}

	param.Mask [0] = this->m_Status [1];
	for ( int i = 9; i < 13; i++ )
	{
		if ( this->m_LampIndex [i] != -1 )
			this->m_Devices [this->m_LampIndex [i]]->ChangeStatus ( param ); // Предполагаются лампы - передача параметров упрощена
		param.Mask [0] >>= 4;
	}
}
