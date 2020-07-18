#include <algorithm>
#include "Description.h"

using std::get;

vector<tuple<wstring, int, int>> Description::tagAndDescriptions;
vector<pair<wstring, int>> Description::groupTags;
vector<tuple<wstring, Description::PlacementType, int>> Description::placementTypes;
vector<tuple<wstring, Description::DeviceCase, int>> Description::blocks;

Description::Description()
{
	setTagAndDescriptionName(L"Светофор", 0, 0);
	setTagAndDescriptionName(L"Стрелка", 1, 1);
	setTagAndDescriptionName(L"Секция", 2, 2);
	setTagAndDescriptionName(L"Стрелочный_модуль", 3, -1);
	setTagAndDescriptionName(L"Статив", 4, -1);
	setTagAndDescriptionName(L"Маневры", 5, -1);
	setTagAndDescriptionName(L"Переезд", 6, -1);
	setTagAndDescriptionName(L"Подключение", 7, -1);

	setTagAndDescriptionName(L"Набор", 100, -1);
	setTagAndDescriptionName(L"Исполнение", 101, -1);
	setTagAndDescriptionName(L"Управление", 102, -1);
	setTagAndDescriptionName(L"Группа", 103, -1);
	setTagAndDescriptionName(L"Общие", 104, -1);
	setTagAndDescriptionName(L"Макет", 105, -1);
	setTagAndDescriptionName(L"Сигнал", 106, -1);
	setTagAndDescriptionName(L"Коммутация", 107, -1);
	setTagAndDescriptionName(L"Привод", 108, -1);
	setTagAndDescriptionName(L"Объект", 109, -1);
	setTagAndDescriptionName(L"РЦ", 110, -1);
	setTagAndDescriptionName(L"Питание", 111, -1);

	setTagAndDescriptionName(L"Электропривод МСП", -1, 200);
	setTagAndDescriptionName(L"Одиночная", -1, 201);
	setTagAndDescriptionName(L"Одиночная с ПС", -1, 202);
	setTagAndDescriptionName(L"Неспаренная", -1, 203);
	setTagAndDescriptionName(L"Неспаренная с ПС", -1, 204);
	setTagAndDescriptionName(L"Съезд", -1, 205);
	setTagAndDescriptionName(L"Угловая", -1, 206);
	setTagAndDescriptionName(L"Неугловая", -1, 207);
	setTagAndDescriptionName(L"Плюс вправо", -1, 208);
	setTagAndDescriptionName(L"Плюс влево", -1, 209);
	setTagAndDescriptionName(L"Центральное питание", -1, 210);
	setTagAndDescriptionName(L"Магистральное питание", -1, 211);
	setTagAndDescriptionName(L"Местное питание", -1, 212);

	setTagAndDescriptionName(L"Маневровый", -1, 300);
	setTagAndDescriptionName(L"Поездной", -1, 301);
	setTagAndDescriptionName(L"В створе", -1, 302);
	setTagAndDescriptionName(L"Из тупика", -1, 303);
	setTagAndDescriptionName(L"Из тупика с участком пути", -1, 304);
	setTagAndDescriptionName(L"С участка пути", -1, 305);
	setTagAndDescriptionName(L"С пути", -1, 306);
	setTagAndDescriptionName(L"В горловине", -1, 307);
	setTagAndDescriptionName(L"Заградительный", -1, 308);
	setTagAndDescriptionName(L"Синий", -1, 309);
	setTagAndDescriptionName(L"Красный", -1, 310);
	setTagAndDescriptionName(L"Два белых", -1, 311);

	setTagAndDescriptionName(L"Четный", -1, 400);
	setTagAndDescriptionName(L"Нечетный", -1, 401);

	setTagAndDescriptionName(L"Стрелочная секция", -1, 500);
	setTagAndDescriptionName(L"Бесстрелочная секция", -1, 501);
	setTagAndDescriptionName(L"участок пути", -1, 502);
	setTagAndDescriptionName(L"Путь", -1, 503);
	setTagAndDescriptionName(L"РЦ25-12", -1, 504);
	setTagAndDescriptionName(L"Неразветвленная", -1, 505);

	setTagAndDescriptionName(L"Двойное управление", -1, 600);

	setTagAndDescriptionName(L"Две жилы", -1, 700);
	setTagAndDescriptionName(L"Три жилы", -1, 701);
	setTagAndDescriptionName(L"Четыре жилы", -1, 702);
	setTagAndDescriptionName(L"Пять жил", -1, 703);
	setTagAndDescriptionName(L"Шесть жил", -1, 704);
	setTagAndDescriptionName(L"Семь жил", -1, 705);
	setTagAndDescriptionName(L"Восемь жил", -1, 706);
	setTagAndDescriptionName(L"Девять жил", -1, 707);
	setTagAndDescriptionName(L"Десять жил", -1, 708);

	setTagAndDescriptionName(L"МРЦ-13", -1, 1000);
	setTagAndDescriptionName(L"МРЦ-16-78", -1, 1001);

	setTagAndDescriptionName(L"СРКМ-75", -1, 1100);

	setTagAndDescriptionName(L"Комплект использован", -1, 1200);


	int index = 0;
	setGroupTag(L"Впереди", index++);
	setGroupTag(L"Позади", index++);
	setGroupTag(L"Сторона1", index++);
	setGroupTag(L"Сторона2", index++);
	setGroupTag(L"Плюс", index++);
	setGroupTag(L"Минус", index++);


	index = 0;
	setPlacementType(L"Релейный статив", PlacementType::RelayStativ, index++);
	setPlacementType(L"Блочный статив", PlacementType::BlockStativ, index++);
	setPlacementType(L"Релейный или блочный статив", PlacementType::RelayStativ, index++);
	setPlacementType(L"Первый статив", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"Первый статив в ряду релейного статива", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"Первый статив в ряду блочного статива", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"Первый статив в ряду", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"Кроссовый статив", PlacementType::CrossStativ, index++);
	setPlacementType(L"Релейный шкаф", PlacementType::RSH, index++);
	setPlacementType(L"Трансформаторный ящик", PlacementType::TYA, index++);
	//	setPlacementType ( L"", PlacementType::, index++ );

	index = 0;
	setBlock(L"М1", DeviceCase::BigBlock, index++);
	setBlock(L"М2", DeviceCase::BigBlock, index++);
	setBlock(L"М3", DeviceCase::BigBlock, index++);
	setBlock(L"В1", DeviceCase::BigBlock, index++);
	setBlock(L"В2", DeviceCase::BigBlock, index++);
	setBlock(L"В3-65", DeviceCase::BigBlock, index++);
	setBlock(L"ВД62", DeviceCase::BigBlock, index++);
	setBlock(L"СП69", DeviceCase::BigBlock, index++);
	setBlock(L"УП65", DeviceCase::BigBlock, index++);
	setBlock(L"П62", DeviceCase::BigBlock, index++);
	setBlock(L"ПС220М", DeviceCase::BigBlock, index++);
	setBlock(L"ОГ1-76", DeviceCase::BigBlock, index++);
	setBlock(L"НН", DeviceCase::SmallBlock, index++);
	setBlock(L"НМ1", DeviceCase::SmallBlock, index++);
	setBlock(L"НМ1Д", DeviceCase::SmallBlock, index++);
	setBlock(L"НМ2П", DeviceCase::SmallBlock, index++);
	setBlock(L"НМ2АП", DeviceCase::SmallBlock, index++);
	setBlock(L"НПМ69", DeviceCase::SmallBlock, index++);
	setBlock(L"НСОх2", DeviceCase::SmallBlock, index++);
	setBlock(L"НСС", DeviceCase::SmallBlock, index++);
	setBlock(L"НПС", DeviceCase::SmallBlock, index++);
	setBlock(L"С", DeviceCase::SmallBlock, index++);
}

int Description::getDescriptionIdByName(const wstring& name)
{
	const auto cbegin = tagAndDescriptions.cbegin();
	const auto cend = tagAndDescriptions.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (get<0>(val) == name); });
	if (res != cend)
		return get<2>(*res);
	else
		return -1;
}

int Description::getTagIdByName(const wstring& name)
{
	const auto cbegin = tagAndDescriptions.cbegin();
	const auto cend = tagAndDescriptions.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (get<0>(val) == name); });
	if (res != cend)
		return get<1>(*res);
	else
		return -1;
}

int Description::getGroupTag(const wstring& name)
{
	const auto cbegin = groupTags.cbegin();
	const auto cend = groupTags.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (val.first == name); });
	if (res != cend)
		return (*res).second;
	else
		return -1;
}

int Description::getPlacementId(const wstring& name)
{
	const auto cbegin = placementTypes.cbegin();
	const auto cend = placementTypes.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (get<0>(val) == name); });
	if (res != cend)
		return get<2>(*res);
	else
		return -1;
}

Description::PlacementType Description::getPlacementType(const wstring& name)
{
	const auto cbegin = placementTypes.cbegin();
	const auto cend = placementTypes.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (get<0>(val) == name); });
	if (res != cend)
		return get<1>(*res);
	else
		return Description::PlacementType::No;
}

pair<Description::DeviceCase, int> Description::getBlockInfo(const wstring& name)
{
	const auto cbegin = blocks.cbegin();
	const auto cend = blocks.cend();
	const auto res = find_if(cbegin, cend, [&name] (const auto& val) { return (get<0>(val) == name); });
	if (res != cend)
		return pair {get<1>(*res), get<2>(*res)};
	else
		return pair {DeviceCase::No, -1};
}

bool Description::checkCaseInPlacement(DeviceCase _case, PlacementType pl_type)
{
	switch (pl_type)
	{
		case PlacementType::TYA:
			return ((_case == DeviceCase::NR) or (_case == DeviceCase::Capacitor) or
				(_case == DeviceCase::Resistor) or (_case == DeviceCase::Rheostat) or
				(_case == DeviceCase::Fuse) or (_case == DeviceCase::Diode) or
				(_case == DeviceCase::BigTransformer) or (_case == DeviceCase::SmallTransformer));
			break;
		case PlacementType::RSH:
			return ((_case == DeviceCase::DSSH) or (_case == DeviceCase::NSH) or (_case == DeviceCase::NMSH) or
				(_case == DeviceCase::REL) or (_case == DeviceCase::NR) or (_case == DeviceCase::Capacitor) or
				(_case == DeviceCase::Resistor) or (_case == DeviceCase::Rheostat) or
				(_case == DeviceCase::Fuse) or (_case == DeviceCase::Diode) or (_case == DeviceCase::MeasuringPanel) or
				(_case == DeviceCase::BigTransformer) or (_case == DeviceCase::SmallTransformer));
			break;
		case PlacementType::CrossStativ:
			return (_case == DeviceCase::Cross);
			break;
		case PlacementType::RelayStativ:
			return ((_case == DeviceCase::DSSH) or (_case == DeviceCase::NSH) or (_case == DeviceCase::NMSH) or
				(_case == DeviceCase::REL) or (_case == DeviceCase::NR) or
				(_case == DeviceCase::KDRSH) or (_case == DeviceCase::Cross) or
				(_case == DeviceCase::BigBlock) or (_case == DeviceCase::SmallBlock) or
				(_case == DeviceCase::Capacitor) or (_case == DeviceCase::Resistor) or
				(_case == DeviceCase::Rheostat) or
				(_case == DeviceCase::Diode) or (_case == DeviceCase::MeasuringPanel) or
				(_case == DeviceCase::BigTransformer) or (_case == DeviceCase::SmallTransformer));
			break;
		case PlacementType::FirstRelayStativ:
			return ((_case == DeviceCase::DSSH) or (_case == DeviceCase::NSH) or (_case == DeviceCase::NMSH) or
				(_case == DeviceCase::REL) or (_case == DeviceCase::NR) or
				(_case == DeviceCase::KDRSH) or (_case == DeviceCase::Cross) or
				(_case == DeviceCase::BigBlock) or (_case == DeviceCase::SmallBlock) or
				(_case == DeviceCase::Capacitor) or (_case == DeviceCase::Resistor) or
				(_case == DeviceCase::Rheostat) or (_case == DeviceCase::Fuse) or
				(_case == DeviceCase::Diode) or (_case == DeviceCase::MeasuringPanel) or
				(_case == DeviceCase::BigTransformer) or (_case == DeviceCase::SmallTransformer));
			break;
		case PlacementType::BlockStativ:
			return ((_case == DeviceCase::NMSH) or (_case == DeviceCase::REL) or
				(_case == DeviceCase::SmallBlock) or (_case == DeviceCase::BigBlock) or
				(_case == DeviceCase::Capacitor) or (_case == DeviceCase::Resistor) or
				(_case == DeviceCase::Diode) or (_case == DeviceCase::MeasuringPanel));
			break;
	}
	return false;
}
