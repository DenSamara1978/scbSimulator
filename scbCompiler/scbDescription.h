#pragma once

#include <vector>
#include <string>

using std::vector;
using std::wstring;
using std::tuple;
using std::pair;

class scbDescription
{
public:
	enum class DeviceCase { No = 0, BigBlock, SmallBlock, DSSH, NSH, NMSH, NM, REL, BN, NR, KDR, KDRSH, Cross, Fuse, Capacitor, Resistor, Rheostat, Diode, MeasuringPanel, BigTransformer, SmallTransformer, SKTTransformer };
	enum class PlacementType { No = 0, TYA, RSH, FirstRelayStativ, RelayStativ, BlockStativ, CrossStativ };

private:
	static vector<tuple<wstring, int, int>> m_TagAndDescriptions;
	static vector<pair<wstring, int>> m_GroupTags;
	static vector<tuple<wstring, PlacementType, int>> m_PlacementTypes;
	static vector<tuple<wstring, DeviceCase, int>> m_Blocks;

	static void SetTagAndDescriptionName ( const wstring& name, int tag, int description );
	static void SetGroupTag ( const wstring& name, int tag );
	static void SetPlacementType ( const wstring& name, PlacementType type, int id );
	static void SetBlock ( const wstring& name, DeviceCase _case, int id );

public:
	scbDescription ();

	static int GetDescriptionIdByName ( const wstring& name );
	static int GetTagIdByName ( const wstring& name );
	static int GetGroupTag ( const wstring& name );
	static int GetPlacementId ( const wstring& name );
	static PlacementType GetPlacementType ( const wstring& name );
	static pair<DeviceCase, int> GetBlockInfo ( const wstring& name );

	static bool CheckCaseInPlacement ( DeviceCase _case, PlacementType pl_type );
};

inline void scbDescription::SetTagAndDescriptionName ( const wstring& name, int tag, int description )
{
	if ( ( tag != -1 ) or ( description != -1 ) )
		m_TagAndDescriptions.emplace_back ( name, tag, description );
}

inline void scbDescription::SetGroupTag ( const wstring& name, int tag )
{
	if ( tag != -1 ) 
		m_GroupTags.emplace_back ( name, tag );
}

inline void scbDescription::SetPlacementType ( const wstring& name, PlacementType type, int id )
{
	if ( id != -1 )
		m_PlacementTypes.emplace_back ( name, type, id );
}

inline void scbDescription::SetBlock ( const wstring& name, DeviceCase _case, int id )
{
	if ( id != -1 )
		m_Blocks.emplace_back ( name, _case, id );
}
