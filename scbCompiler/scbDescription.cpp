#include <algorithm>
#include "scbDescription.h"

using std::get;

vector<tuple<wstring, int, int>> scbDescription::m_TagAndDescriptions;
vector<pair<wstring, int>> scbDescription::m_GroupTags;
vector<tuple<wstring, scbDescription::PlacementType, int>> scbDescription::m_PlacementTypes;
vector<tuple<wstring, scbDescription::DeviceCase, int>> scbDescription::m_Blocks;

scbDescription::scbDescription ()
{
	SetTagAndDescriptionName ( L"Светофор", 0, 0 );
	SetTagAndDescriptionName ( L"Стрелка", 1, 1 );
	SetTagAndDescriptionName ( L"Секция", 2, 2 );
	SetTagAndDescriptionName ( L"Стрелочный_модуль", 3, -1 );
	SetTagAndDescriptionName ( L"Статив", 4, -1 );
	SetTagAndDescriptionName ( L"Маневры", 5, -1 );
	SetTagAndDescriptionName ( L"Переезд", 6, -1 );
	SetTagAndDescriptionName ( L"Подключение", 7, -1 );

	SetTagAndDescriptionName ( L"Набор", 100, -1 );
	SetTagAndDescriptionName ( L"Исполнение", 101, -1 );
	SetTagAndDescriptionName ( L"Управление", 102, -1 );
	SetTagAndDescriptionName ( L"Группа", 103, -1 );
	SetTagAndDescriptionName ( L"Общие", 104, -1 );
	SetTagAndDescriptionName ( L"Макет", 105, -1 );
	SetTagAndDescriptionName ( L"Сигнал", 106, -1 );
	SetTagAndDescriptionName ( L"Коммутация", 107, -1 );
	SetTagAndDescriptionName ( L"Привод", 108, -1 );
	SetTagAndDescriptionName ( L"Объект", 109, -1 );
	SetTagAndDescriptionName ( L"РЦ", 110, -1 );
	SetTagAndDescriptionName ( L"Питание", 111, -1 );

	SetTagAndDescriptionName ( L"Электропривод МСП", -1, 200 );
	SetTagAndDescriptionName ( L"Одиночная", -1, 201 );
	SetTagAndDescriptionName ( L"Одиночная с ПС", -1, 202 );
	SetTagAndDescriptionName ( L"Неспаренная", -1, 203 );
	SetTagAndDescriptionName ( L"Неспаренная с ПС", -1, 204 );
	SetTagAndDescriptionName ( L"Съезд", -1, 205 );
	SetTagAndDescriptionName ( L"Угловая", -1, 206 );
	SetTagAndDescriptionName ( L"Неугловая", -1, 207 );
	SetTagAndDescriptionName ( L"Плюс вправо", -1, 208 );
	SetTagAndDescriptionName ( L"Плюс влево", -1, 209 );
	SetTagAndDescriptionName ( L"Центральное питание", -1, 210 );
	SetTagAndDescriptionName ( L"Магистральное питание", -1, 211 );
	SetTagAndDescriptionName ( L"Местное питание", -1, 212 );

    SetTagAndDescriptionName ( L"Маневровый", -1, 300 );
	SetTagAndDescriptionName ( L"Поездной", -1, 301 );
	SetTagAndDescriptionName ( L"В створе", -1, 302 );
	SetTagAndDescriptionName ( L"Из тупика", -1, 303 );
	SetTagAndDescriptionName ( L"Из тупика с участком пути", -1, 304 );
	SetTagAndDescriptionName ( L"С участка пути", -1, 305 );
	SetTagAndDescriptionName ( L"С пути", -1, 306 );
	SetTagAndDescriptionName ( L"В горловине", -1, 307 );
	SetTagAndDescriptionName ( L"Заградительный", -1, 308 );
	SetTagAndDescriptionName ( L"Синий", -1, 309 );
	SetTagAndDescriptionName ( L"Красный", -1, 310 );
	SetTagAndDescriptionName ( L"Два белых", -1, 311 );

	SetTagAndDescriptionName ( L"Четный", -1, 400 );
	SetTagAndDescriptionName ( L"Нечетный", -1, 401 );

	SetTagAndDescriptionName ( L"Стрелочная секция", -1, 500 );
	SetTagAndDescriptionName ( L"Бесстрелочная секция", -1, 501 );
	SetTagAndDescriptionName ( L"участок пути", -1, 502 );
	SetTagAndDescriptionName ( L"Путь", -1, 503 );
	SetTagAndDescriptionName ( L"РЦ25-12", -1, 504 );
	SetTagAndDescriptionName ( L"Неразветвленная", -1, 505 );

	SetTagAndDescriptionName ( L"Двойное управление", -1, 600 );

    SetTagAndDescriptionName ( L"Две жилы", -1, 700 );
    SetTagAndDescriptionName ( L"Три жилы", -1, 701 );
    SetTagAndDescriptionName ( L"Четыре жилы", -1, 702 );
    SetTagAndDescriptionName ( L"Пять жил", -1, 703 );
    SetTagAndDescriptionName ( L"Шесть жил", -1, 704 );
    SetTagAndDescriptionName ( L"Семь жил", -1, 705 );
    SetTagAndDescriptionName ( L"Восемь жил", -1, 706 );
    SetTagAndDescriptionName ( L"Девять жил", -1, 707 );
    SetTagAndDescriptionName ( L"Десять жил", -1, 708 );

    SetTagAndDescriptionName ( L"МРЦ-13", -1, 1000 );
	SetTagAndDescriptionName ( L"МРЦ-16-78", -1, 1001 );

	SetTagAndDescriptionName ( L"СРКМ-75", -1, 1100 );

    SetTagAndDescriptionName ( L"Комплект использован", -1, 1200 );


	int index = 0;
	SetGroupTag ( L"Впереди", index++ );
	SetGroupTag ( L"Позади", index++ );
	SetGroupTag ( L"Сторона1", index++ );
	SetGroupTag ( L"Сторона2", index++ );
	SetGroupTag ( L"Плюс", index++ );
	SetGroupTag ( L"Минус", index++ );


	index = 0;
	SetPlacementType ( L"Релейный статив", PlacementType::RelayStativ,  index++ );
	SetPlacementType ( L"Блочный статив", PlacementType::BlockStativ, index++ );
	SetPlacementType ( L"Релейный или блочный статив", PlacementType::RelayStativ, index++ );
	SetPlacementType ( L"Первый статив", PlacementType::FirstRelayStativ, index++ );
	SetPlacementType ( L"Первый статив в ряду релейного статива", PlacementType::FirstRelayStativ, index++ );
	SetPlacementType ( L"Первый статив в ряду блочного статива", PlacementType::FirstRelayStativ, index++ );
    SetPlacementType ( L"Первый статив в ряду", PlacementType::FirstRelayStativ, index++ );
    SetPlacementType ( L"Кроссовый статив", PlacementType::CrossStativ, index++ );
	SetPlacementType ( L"Релейный шкаф", PlacementType::RSH, index++ );
	SetPlacementType ( L"Трансформаторный ящик", PlacementType::TYA, index++ );
//	SetPlacementType ( L"", PlacementType::, index++ );

	index = 0;
	SetBlock ( L"М1", DeviceCase::BigBlock, index++ );
	SetBlock ( L"М2", DeviceCase::BigBlock, index++ );
	SetBlock ( L"М3", DeviceCase::BigBlock, index++ );
	SetBlock ( L"В1", DeviceCase::BigBlock, index++ );
	SetBlock ( L"В2", DeviceCase::BigBlock, index++ );
	SetBlock ( L"В3-65", DeviceCase::BigBlock, index++ );
	SetBlock ( L"ВД62", DeviceCase::BigBlock, index++ );
	SetBlock ( L"СП69", DeviceCase::BigBlock, index++ );
	SetBlock ( L"УП65", DeviceCase::BigBlock, index++ );
	SetBlock ( L"П62", DeviceCase::BigBlock, index++ );
	SetBlock ( L"ПС220М", DeviceCase::BigBlock, index++ );
	SetBlock ( L"ОГ1-76", DeviceCase::BigBlock, index++ );
	SetBlock ( L"НН", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НМ1", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НМ1Д", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НМ2П", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НМ2АП", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НПМ69", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НСОх2", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НСС", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"НПС", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"С", DeviceCase::SmallBlock, index++ );
}

int scbDescription::GetDescriptionIdByName ( const wstring& name )
{
	const auto cbegin = m_TagAndDescriptions.cbegin ();
	const auto cend = m_TagAndDescriptions.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( get<0> ( val ) == name ); } );
	if ( res != cend )
		return get<2> ( *res );
	else
		return -1;
}

int scbDescription::GetTagIdByName ( const wstring& name )
{
	const auto cbegin = m_TagAndDescriptions.cbegin ();
	const auto cend = m_TagAndDescriptions.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( get<0> ( val ) == name ); } );
	if ( res != cend )
		return get<1> ( *res );
	else
		return -1;
}

int scbDescription::GetGroupTag ( const wstring& name )
{
	const auto cbegin = m_GroupTags.cbegin ();
	const auto cend = m_GroupTags.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( val.first == name ); } );
	if ( res != cend )
		return ( *res ).second;
	else
		return -1;
}

int scbDescription::GetPlacementId ( const wstring& name )
{
	const auto cbegin = m_PlacementTypes.cbegin ();
	const auto cend = m_PlacementTypes.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( get<0> ( val ) == name ); } );
	if ( res != cend )
		return get<2> ( *res );
	else
		return -1;
}

scbDescription::PlacementType scbDescription::GetPlacementType ( const wstring& name )
{
	const auto cbegin = m_PlacementTypes.cbegin ();
	const auto cend = m_PlacementTypes.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( get<0> ( val ) == name ); } );
	if ( res != cend )
		return get<1> ( *res );
	else
		return scbDescription::PlacementType::No;
}

pair<scbDescription::DeviceCase, int> scbDescription::GetBlockInfo ( const wstring& name )
{
	const auto cbegin = m_Blocks.cbegin ();
	const auto cend = m_Blocks.cend ();
	const auto res = find_if ( cbegin, cend, [&name] ( const auto& val ) { return ( get<0> ( val ) == name ); } );
	if ( res != cend )
		return pair { get<1> ( *res ), get<2> ( *res ) };
	else
		return pair { DeviceCase::No, -1 };
}

bool scbDescription::CheckCaseInPlacement ( DeviceCase _case, PlacementType pl_type )
{
	switch ( pl_type )
	{
	case PlacementType::TYA:
		return (( _case == DeviceCase::NR ) or ( _case == DeviceCase::Capacitor ) or 
            ( _case == DeviceCase::Resistor ) or ( _case == DeviceCase::Rheostat ) or 
            ( _case == DeviceCase::Fuse ) or ( _case == DeviceCase::Diode ) or
            ( _case == DeviceCase::BigTransformer ) or ( _case == DeviceCase::SmallTransformer ));
		break;
	case PlacementType::RSH:
		return ( ( _case == DeviceCase::DSSH ) or ( _case == DeviceCase::NSH ) or ( _case == DeviceCase::NMSH ) or
			( _case == DeviceCase::REL ) or ( _case == DeviceCase::NR ) or ( _case == DeviceCase::Capacitor ) or
            ( _case == DeviceCase::Resistor ) or ( _case == DeviceCase::Rheostat ) or
            ( _case == DeviceCase::Fuse ) or ( _case == DeviceCase::Diode ) or ( _case == DeviceCase::MeasuringPanel ) or
            ( _case == DeviceCase::BigTransformer ) or ( _case == DeviceCase::SmallTransformer ) );
		break;
	case PlacementType::CrossStativ:
		return ( _case == DeviceCase::Cross );
		break;
	case PlacementType::RelayStativ:
		return ( ( _case == DeviceCase::DSSH ) or ( _case == DeviceCase::NSH ) or ( _case == DeviceCase::NMSH ) or
			( _case == DeviceCase::REL ) or ( _case == DeviceCase::NR ) or
			( _case == DeviceCase::KDRSH ) or ( _case == DeviceCase::Cross ) or
			( _case == DeviceCase::BigBlock ) or ( _case == DeviceCase::SmallBlock ) or 
            ( _case == DeviceCase::Capacitor ) or ( _case == DeviceCase::Resistor ) or 
            ( _case == DeviceCase::Rheostat ) or 
            ( _case == DeviceCase::Diode ) or ( _case == DeviceCase::MeasuringPanel ) or
            ( _case == DeviceCase::BigTransformer ) or ( _case == DeviceCase::SmallTransformer ) );
		break;
	case PlacementType::FirstRelayStativ:
		return ( ( _case == DeviceCase::DSSH ) or ( _case == DeviceCase::NSH ) or ( _case == DeviceCase::NMSH ) or
			( _case == DeviceCase::REL ) or ( _case == DeviceCase::NR ) or
			( _case == DeviceCase::KDRSH ) or ( _case == DeviceCase::Cross ) or
			( _case == DeviceCase::BigBlock ) or ( _case == DeviceCase::SmallBlock ) or
            ( _case == DeviceCase::Capacitor ) or ( _case == DeviceCase::Resistor ) or
            ( _case == DeviceCase::Rheostat ) or ( _case == DeviceCase::Fuse ) or 
            ( _case == DeviceCase::Diode ) or ( _case == DeviceCase::MeasuringPanel ) or
            ( _case == DeviceCase::BigTransformer ) or ( _case == DeviceCase::SmallTransformer ) );
		break;
	case PlacementType::BlockStativ:
		return (( _case == DeviceCase::NMSH ) or ( _case == DeviceCase::REL ) or 
			( _case == DeviceCase::SmallBlock ) or ( _case == DeviceCase::BigBlock ) or
            ( _case == DeviceCase::Capacitor ) or ( _case == DeviceCase::Resistor ) or 
            ( _case == DeviceCase::Diode ) or ( _case == DeviceCase::MeasuringPanel ));
		break;
	}
	return false;
}
