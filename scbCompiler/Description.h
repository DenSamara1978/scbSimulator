#pragma once

#include <vector>
#include <string>

using std::vector;
using std::wstring;
using std::tuple;
using std::pair;

class Description
{
public:
	enum class DeviceCase { No = 0, BigBlock, SmallBlock, DSSH, NSH, NMSH, NM, REL, BN, NR, KDR, KDRSH, Cross, Fuse, Capacitor, Resistor, Rheostat, Diode, MeasuringPanel, BigTransformer, SmallTransformer, SKTTransformer };
	enum class PlacementType { No = 0, TYA, RSH, FirstRelayStativ, RelayStativ, BlockStativ, CrossStativ };

	Description();

	static int getDescriptionIdByName(const wstring& name);
	static int getTagIdByName(const wstring& name);
	static int getGroupTag(const wstring& name);
	static int getPlacementId(const wstring& name);
	static PlacementType getPlacementType(const wstring& name);
	static pair<DeviceCase, int> getBlockInfo(const wstring& name);

	static bool checkCaseInPlacement(DeviceCase _case, PlacementType pl_type);

private:
	static vector<tuple<wstring, int, int>> tagAndDescriptions;
	static vector<pair<wstring, int>> groupTags;
	static vector<tuple<wstring, PlacementType, int>> placementTypes;
	static vector<tuple<wstring, DeviceCase, int>> blocks;

	static void setTagAndDescriptionName(const wstring& name, int tag, int description);
	static void setGroupTag(const wstring& name, int tag);
	static void setPlacementType(const wstring& name, PlacementType type, int id);
	static void setBlock(const wstring& name, DeviceCase _case, int id);

};

inline void Description::setTagAndDescriptionName(const wstring& name, int tag, int description)
{
	if ((tag != -1) or (description != -1))
		tagAndDescriptions.emplace_back(name, tag, description);
}

inline void Description::setGroupTag(const wstring& name, int tag)
{
	if (tag != -1)
		groupTags.emplace_back(name, tag);
}

inline void Description::setPlacementType(const wstring& name, PlacementType type, int id)
{
	if (id != -1)
		placementTypes.emplace_back(name, type, id);
}

inline void Description::setBlock(const wstring& name, DeviceCase _case, int id)
{
	if (id != -1)
		blocks.emplace_back(name, _case, id);
}
