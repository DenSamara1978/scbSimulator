#include <algorithm>
#include "scbDescription.h"

using std::get;

vector<tuple<wstring, int, int>> scbDescription::m_TagAndDescriptions;
vector<pair<wstring, int>> scbDescription::m_GroupTags;
vector<tuple<wstring, scbDescription::PlacementType, int>> scbDescription::m_PlacementTypes;
vector<tuple<wstring, scbDescription::DeviceCase, int>> scbDescription::m_Blocks;

scbDescription::scbDescription ()
{
	SetTagAndDescriptionName ( L"��������", 0, 0 );
	SetTagAndDescriptionName ( L"�������", 1, 1 );
	SetTagAndDescriptionName ( L"������", 2, 2 );
	SetTagAndDescriptionName ( L"����������_������", 3, -1 );
	SetTagAndDescriptionName ( L"������", 4, -1 );
	SetTagAndDescriptionName ( L"�������", 5, -1 );
	SetTagAndDescriptionName ( L"�������", 6, -1 );
	SetTagAndDescriptionName ( L"�����������", 7, -1 );

	SetTagAndDescriptionName ( L"�����", 100, -1 );
	SetTagAndDescriptionName ( L"����������", 101, -1 );
	SetTagAndDescriptionName ( L"����������", 102, -1 );
	SetTagAndDescriptionName ( L"������", 103, -1 );
	SetTagAndDescriptionName ( L"�����", 104, -1 );
	SetTagAndDescriptionName ( L"�����", 105, -1 );
	SetTagAndDescriptionName ( L"������", 106, -1 );
	SetTagAndDescriptionName ( L"����������", 107, -1 );
	SetTagAndDescriptionName ( L"������", 108, -1 );
	SetTagAndDescriptionName ( L"������", 109, -1 );
	SetTagAndDescriptionName ( L"��", 110, -1 );
	SetTagAndDescriptionName ( L"�������", 111, -1 );

	SetTagAndDescriptionName ( L"������������� ���", -1, 200 );
	SetTagAndDescriptionName ( L"���������", -1, 201 );
	SetTagAndDescriptionName ( L"��������� � ��", -1, 202 );
	SetTagAndDescriptionName ( L"�����������", -1, 203 );
	SetTagAndDescriptionName ( L"����������� � ��", -1, 204 );
	SetTagAndDescriptionName ( L"�����", -1, 205 );
	SetTagAndDescriptionName ( L"�������", -1, 206 );
	SetTagAndDescriptionName ( L"���������", -1, 207 );
	SetTagAndDescriptionName ( L"���� ������", -1, 208 );
	SetTagAndDescriptionName ( L"���� �����", -1, 209 );
	SetTagAndDescriptionName ( L"����������� �������", -1, 210 );
	SetTagAndDescriptionName ( L"������������� �������", -1, 211 );
	SetTagAndDescriptionName ( L"������� �������", -1, 212 );

    SetTagAndDescriptionName ( L"����������", -1, 300 );
	SetTagAndDescriptionName ( L"��������", -1, 301 );
	SetTagAndDescriptionName ( L"� ������", -1, 302 );
	SetTagAndDescriptionName ( L"�� ������", -1, 303 );
	SetTagAndDescriptionName ( L"�� ������ � �������� ����", -1, 304 );
	SetTagAndDescriptionName ( L"� ������� ����", -1, 305 );
	SetTagAndDescriptionName ( L"� ����", -1, 306 );
	SetTagAndDescriptionName ( L"� ���������", -1, 307 );
	SetTagAndDescriptionName ( L"��������������", -1, 308 );
	SetTagAndDescriptionName ( L"�����", -1, 309 );
	SetTagAndDescriptionName ( L"�������", -1, 310 );
	SetTagAndDescriptionName ( L"��� �����", -1, 311 );

	SetTagAndDescriptionName ( L"������", -1, 400 );
	SetTagAndDescriptionName ( L"��������", -1, 401 );

	SetTagAndDescriptionName ( L"���������� ������", -1, 500 );
	SetTagAndDescriptionName ( L"������������� ������", -1, 501 );
	SetTagAndDescriptionName ( L"������� ����", -1, 502 );
	SetTagAndDescriptionName ( L"����", -1, 503 );
	SetTagAndDescriptionName ( L"��25-12", -1, 504 );
	SetTagAndDescriptionName ( L"���������������", -1, 505 );

	SetTagAndDescriptionName ( L"������� ����������", -1, 600 );

    SetTagAndDescriptionName ( L"��� ����", -1, 700 );
    SetTagAndDescriptionName ( L"��� ����", -1, 701 );
    SetTagAndDescriptionName ( L"������ ����", -1, 702 );
    SetTagAndDescriptionName ( L"���� ���", -1, 703 );
    SetTagAndDescriptionName ( L"����� ���", -1, 704 );
    SetTagAndDescriptionName ( L"���� ���", -1, 705 );
    SetTagAndDescriptionName ( L"������ ���", -1, 706 );
    SetTagAndDescriptionName ( L"������ ���", -1, 707 );
    SetTagAndDescriptionName ( L"������ ���", -1, 708 );

    SetTagAndDescriptionName ( L"���-13", -1, 1000 );
	SetTagAndDescriptionName ( L"���-16-78", -1, 1001 );

	SetTagAndDescriptionName ( L"����-75", -1, 1100 );

    SetTagAndDescriptionName ( L"�������� �����������", -1, 1200 );


	int index = 0;
	SetGroupTag ( L"�������", index++ );
	SetGroupTag ( L"������", index++ );
	SetGroupTag ( L"�������1", index++ );
	SetGroupTag ( L"�������2", index++ );
	SetGroupTag ( L"����", index++ );
	SetGroupTag ( L"�����", index++ );


	index = 0;
	SetPlacementType ( L"�������� ������", PlacementType::RelayStativ,  index++ );
	SetPlacementType ( L"������� ������", PlacementType::BlockStativ, index++ );
	SetPlacementType ( L"�������� ��� ������� ������", PlacementType::RelayStativ, index++ );
	SetPlacementType ( L"������ ������", PlacementType::FirstRelayStativ, index++ );
	SetPlacementType ( L"������ ������ � ���� ��������� �������", PlacementType::FirstRelayStativ, index++ );
	SetPlacementType ( L"������ ������ � ���� �������� �������", PlacementType::FirstRelayStativ, index++ );
    SetPlacementType ( L"������ ������ � ����", PlacementType::FirstRelayStativ, index++ );
    SetPlacementType ( L"��������� ������", PlacementType::CrossStativ, index++ );
	SetPlacementType ( L"�������� ����", PlacementType::RSH, index++ );
	SetPlacementType ( L"���������������� ����", PlacementType::TYA, index++ );
//	SetPlacementType ( L"", PlacementType::, index++ );

	index = 0;
	SetBlock ( L"�1", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�2", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�3", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�1", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�2", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�3-65", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��62", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��69", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��65", DeviceCase::BigBlock, index++ );
	SetBlock ( L"�62", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��220�", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��1-76", DeviceCase::BigBlock, index++ );
	SetBlock ( L"��", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"��1", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"��1�", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"��2�", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"��2��", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"���69", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"����2", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"���", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"���", DeviceCase::SmallBlock, index++ );
	SetBlock ( L"�", DeviceCase::SmallBlock, index++ );
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
