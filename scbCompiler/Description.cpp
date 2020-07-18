#include <algorithm>
#include "Description.h"

using std::get;

vector<tuple<wstring, int, int>> Description::tagAndDescriptions;
vector<pair<wstring, int>> Description::groupTags;
vector<tuple<wstring, Description::PlacementType, int>> Description::placementTypes;
vector<tuple<wstring, Description::DeviceCase, int>> Description::blocks;

Description::Description()
{
	setTagAndDescriptionName(L"��������", 0, 0);
	setTagAndDescriptionName(L"�������", 1, 1);
	setTagAndDescriptionName(L"������", 2, 2);
	setTagAndDescriptionName(L"����������_������", 3, -1);
	setTagAndDescriptionName(L"������", 4, -1);
	setTagAndDescriptionName(L"�������", 5, -1);
	setTagAndDescriptionName(L"�������", 6, -1);
	setTagAndDescriptionName(L"�����������", 7, -1);

	setTagAndDescriptionName(L"�����", 100, -1);
	setTagAndDescriptionName(L"����������", 101, -1);
	setTagAndDescriptionName(L"����������", 102, -1);
	setTagAndDescriptionName(L"������", 103, -1);
	setTagAndDescriptionName(L"�����", 104, -1);
	setTagAndDescriptionName(L"�����", 105, -1);
	setTagAndDescriptionName(L"������", 106, -1);
	setTagAndDescriptionName(L"����������", 107, -1);
	setTagAndDescriptionName(L"������", 108, -1);
	setTagAndDescriptionName(L"������", 109, -1);
	setTagAndDescriptionName(L"��", 110, -1);
	setTagAndDescriptionName(L"�������", 111, -1);

	setTagAndDescriptionName(L"������������� ���", -1, 200);
	setTagAndDescriptionName(L"���������", -1, 201);
	setTagAndDescriptionName(L"��������� � ��", -1, 202);
	setTagAndDescriptionName(L"�����������", -1, 203);
	setTagAndDescriptionName(L"����������� � ��", -1, 204);
	setTagAndDescriptionName(L"�����", -1, 205);
	setTagAndDescriptionName(L"�������", -1, 206);
	setTagAndDescriptionName(L"���������", -1, 207);
	setTagAndDescriptionName(L"���� ������", -1, 208);
	setTagAndDescriptionName(L"���� �����", -1, 209);
	setTagAndDescriptionName(L"����������� �������", -1, 210);
	setTagAndDescriptionName(L"������������� �������", -1, 211);
	setTagAndDescriptionName(L"������� �������", -1, 212);

	setTagAndDescriptionName(L"����������", -1, 300);
	setTagAndDescriptionName(L"��������", -1, 301);
	setTagAndDescriptionName(L"� ������", -1, 302);
	setTagAndDescriptionName(L"�� ������", -1, 303);
	setTagAndDescriptionName(L"�� ������ � �������� ����", -1, 304);
	setTagAndDescriptionName(L"� ������� ����", -1, 305);
	setTagAndDescriptionName(L"� ����", -1, 306);
	setTagAndDescriptionName(L"� ���������", -1, 307);
	setTagAndDescriptionName(L"��������������", -1, 308);
	setTagAndDescriptionName(L"�����", -1, 309);
	setTagAndDescriptionName(L"�������", -1, 310);
	setTagAndDescriptionName(L"��� �����", -1, 311);

	setTagAndDescriptionName(L"������", -1, 400);
	setTagAndDescriptionName(L"��������", -1, 401);

	setTagAndDescriptionName(L"���������� ������", -1, 500);
	setTagAndDescriptionName(L"������������� ������", -1, 501);
	setTagAndDescriptionName(L"������� ����", -1, 502);
	setTagAndDescriptionName(L"����", -1, 503);
	setTagAndDescriptionName(L"��25-12", -1, 504);
	setTagAndDescriptionName(L"���������������", -1, 505);

	setTagAndDescriptionName(L"������� ����������", -1, 600);

	setTagAndDescriptionName(L"��� ����", -1, 700);
	setTagAndDescriptionName(L"��� ����", -1, 701);
	setTagAndDescriptionName(L"������ ����", -1, 702);
	setTagAndDescriptionName(L"���� ���", -1, 703);
	setTagAndDescriptionName(L"����� ���", -1, 704);
	setTagAndDescriptionName(L"���� ���", -1, 705);
	setTagAndDescriptionName(L"������ ���", -1, 706);
	setTagAndDescriptionName(L"������ ���", -1, 707);
	setTagAndDescriptionName(L"������ ���", -1, 708);

	setTagAndDescriptionName(L"���-13", -1, 1000);
	setTagAndDescriptionName(L"���-16-78", -1, 1001);

	setTagAndDescriptionName(L"����-75", -1, 1100);

	setTagAndDescriptionName(L"�������� �����������", -1, 1200);


	int index = 0;
	setGroupTag(L"�������", index++);
	setGroupTag(L"������", index++);
	setGroupTag(L"�������1", index++);
	setGroupTag(L"�������2", index++);
	setGroupTag(L"����", index++);
	setGroupTag(L"�����", index++);


	index = 0;
	setPlacementType(L"�������� ������", PlacementType::RelayStativ, index++);
	setPlacementType(L"������� ������", PlacementType::BlockStativ, index++);
	setPlacementType(L"�������� ��� ������� ������", PlacementType::RelayStativ, index++);
	setPlacementType(L"������ ������", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"������ ������ � ���� ��������� �������", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"������ ������ � ���� �������� �������", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"������ ������ � ����", PlacementType::FirstRelayStativ, index++);
	setPlacementType(L"��������� ������", PlacementType::CrossStativ, index++);
	setPlacementType(L"�������� ����", PlacementType::RSH, index++);
	setPlacementType(L"���������������� ����", PlacementType::TYA, index++);
	//	setPlacementType ( L"", PlacementType::, index++ );

	index = 0;
	setBlock(L"�1", DeviceCase::BigBlock, index++);
	setBlock(L"�2", DeviceCase::BigBlock, index++);
	setBlock(L"�3", DeviceCase::BigBlock, index++);
	setBlock(L"�1", DeviceCase::BigBlock, index++);
	setBlock(L"�2", DeviceCase::BigBlock, index++);
	setBlock(L"�3-65", DeviceCase::BigBlock, index++);
	setBlock(L"��62", DeviceCase::BigBlock, index++);
	setBlock(L"��69", DeviceCase::BigBlock, index++);
	setBlock(L"��65", DeviceCase::BigBlock, index++);
	setBlock(L"�62", DeviceCase::BigBlock, index++);
	setBlock(L"��220�", DeviceCase::BigBlock, index++);
	setBlock(L"��1-76", DeviceCase::BigBlock, index++);
	setBlock(L"��", DeviceCase::SmallBlock, index++);
	setBlock(L"��1", DeviceCase::SmallBlock, index++);
	setBlock(L"��1�", DeviceCase::SmallBlock, index++);
	setBlock(L"��2�", DeviceCase::SmallBlock, index++);
	setBlock(L"��2��", DeviceCase::SmallBlock, index++);
	setBlock(L"���69", DeviceCase::SmallBlock, index++);
	setBlock(L"����2", DeviceCase::SmallBlock, index++);
	setBlock(L"���", DeviceCase::SmallBlock, index++);
	setBlock(L"���", DeviceCase::SmallBlock, index++);
	setBlock(L"�", DeviceCase::SmallBlock, index++);
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
