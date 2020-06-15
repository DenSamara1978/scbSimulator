#include "scbMessagePool.h"

scbMessagePool::scbMessagePool ()
{
}


void scbMessagePool::Clear ()
{
	this->m_Pool.clear ();
}

int scbMessagePool::SyntaxError ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������������� ������ � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 1;
}

int scbMessagePool::IncorrectTypeOfFile ()
{
	this->m_Pool.emplace_back ( L"%compilationerror �������� ������ �������� �����.%br" );
	return 1;
}

int scbMessagePool::FatalError ()
{
	this->m_Pool.emplace_back ( L"%compilationerror ��������� ������, ���������� ��������.%br" );
	return 1;
}

int scbMessagePool::IncorrectLevelOfBlock ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������ ������������ ����� ������ %param1 � ������ %row.%br", info.Row, info.Token );
	return 1;
}

int scbMessagePool::NameAlwaysUsed ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ��������� ������������� ����� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::InvalidMultiplicatorArgument ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ �������� ��������������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ��������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������� �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorTagOrder ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ����������� �� �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorGroupTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ��������� ������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ��� ����������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptionTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ��� �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfDescriptionTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ��������� ������������� ���� �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectPlacementType ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ��� ���������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::UnknownTypeOfRelay ( const wstring& name, const wstring& type, const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����������� ��� '%param2' ���� '%param1' � ������ %row.%br", info.Row, name, type );
	return 0;
}

int scbMessagePool::UnknownTypeOfEquipment ( const wstring& name, const wstring& type, const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� ��� '%param2' ������������ '%param1' � ������ %row.%br", info.Row, name, type );
    return 0;
}

int scbMessagePool::UnknownTypeOfBlock ( const scbParseInfo& info, const wstring& name )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����������� ��� '%param2' ����� '%param1' � ������ %row.%br", info.Row, info.Pos, name, info.Token );
	return 0;
}

int scbMessagePool::IncorrectOrderOfDescription ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������� ������� ���������� �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfDescription ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ �������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::DeviceCantHaveAnyJumper ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����������, ������� ��� '%param1', �� ����� ����� ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
	return 0;
}

int scbMessagePool::DeviceCantHaveThisJumper ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����������, ������� ��� '%param1', �� ����� ����� ��������� %param2, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type, info.Token );
	return 0;
}

int scbMessagePool::DeviceHasIncompleteSetOfJumpers ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� ����� �������� ����� ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::DeviceCantHaveNominal ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ���� %param1 �� ����� ����� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHaveNominal ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ���� %param1 ������ ����� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHavePowerClass ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ���� %param1 ������ ����� ����� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHaveObjectName ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ���� %param1 ������ ����� ������������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceCantHaveThisUnit ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror �������� ������� ��������� �������� ���������� ���� %param1, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceCantHavePowerClass ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ���� %param1 �� ����� ������ �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::IncorrectPowerClass ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ����� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfJumper ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfContact ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::DeviceCantHaveThisContact ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� �� ����� ��������� ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::DeviceHasIncompatibleSetOfJumpers ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� ����� ������������� ����� ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::RelayCantUseToCoverAnyRequirement ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����, ������� ��� '%param1', �� ����� ����������� ��� �������������� ������������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, type );
	return 0;
}

int scbMessagePool::NumberExcepted ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ��������� ���������� ����� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::NumberIsOutOfRange ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����� ����������� ���������� ��������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfPlacementName ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ����� ���������� '%param1' � ����� ��������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfPlacementType ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ���� �� ���� ���������� '%param1' � ����� ��������, � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::InexactRepeatOfPlacement ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������� ������ ���������� � ������ ��������� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorMustBeSingle ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ����������������� ���������� ������ ���� ������������ ������������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::DifferentDescriptionGroupsAreEqual ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationwarning �������� ����������� ������ ��������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectSectionBlockInAloneDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������������� ���������� �� ����� ����� ������ ����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::TooMuchSectionBlockInDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ���������� ������ ����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectCoincidingDescriptors ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������� ����������� �����������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectCoincidingDescriptionSets ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������� ����������� ������ ��������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectDescriptorPresence ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ������� ����������� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectDescriptorAbsence ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ���������� ����������� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UsingOfIncorrectDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ���������� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UnachievableDescriptionCombination ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ���������� �������� � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyConnection ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������������� ���������� �� ����� ����� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyExternalLink ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������������� ���������� �� ����� ����� ������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyExtendedBlock ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������������� ���������� �� ����� ������������ ��������� ������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyAliases ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������������� ���������� �� ����� ������������ ����������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::ConditionParamIsRequired ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������� ������� ��������� ����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::ConditionParamIsNotRequired ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������� �� ������� ��������� ����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::CantHaveAnyInternalConnections ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� �������� ����� ���������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExternalConnections ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� �������� ����� ������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExternalLinks ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� �������� ����� ������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExtendedBlocks ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� ������������� ����� ���������� �������������� ������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::DescriptorWithoutParameterMustBeSingle ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������������ �������� ���������� ����� ���� ������ ����, � ������ %row ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UsingInternalConnectionWithSameDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ ���������� ����� ������ ������ �����������, � ������ %row ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::InvalidExtendedBlockCountArgument ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������ �������� ���������� ���������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::UndefinedPlacementName ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������������� ��� ���������� '%param1' � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncompatiblePlacement ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������ �� ����� ���� ���������� � ���������� '%param1', � ������ %row, ������� %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::SimpleDescriptorCantHaveAlternativeNames ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������������������� ���������� �� ����� ����� ������ � ��������������� �������, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectCountOfAlternativeNames ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror �������������� ���������� �������������� ���� � ���������������� �����, � ������ %row.%br", info.Row );
	return 0;
}

int scbMessagePool::LocationStillOccupied ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ��������� ����� � ���������� ��� ������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::DeviceCantOccupyTheLocation ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ���������� �� ����� �������� ��������� �����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::InactiveParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror ������ ������������ ��������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::RequirementDoesntCoverWholeRange ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� �� ����������� �������� ����������, � ������ %row.%br", info.Row );
    return 0;
}

int scbMessagePool::RequirementFromIsGreaterThanTo ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� ������� �� � ������������� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::NameMustBeTheStatus ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� ��� ������ ���� ���������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::NameWasNotFound ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� ��� �� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfRequirementName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ����� �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfRequirementDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ������������ ������ ����������� �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRequirementName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ��� ����������� �� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectProbablityClass ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror �������� ����� �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectCountOfOutput ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror �������������� ���������� �������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectGroupTagInDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ��������� ��������� ��� ����������� �� ���������� �� ������� ������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::MoreThanOneRecordForThisNumberOfRequestingRequirement ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����� ����� ������ ��� ���������� ������ �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::UnableToGrantThisRequirement ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ����������� ����������� ������������� ��������� �����������, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::WholeInputsInRequestingRequirementAreZero ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror � ������� ����������� �� ������ �� ���� ����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::RequirementNameMustBeNonDescriptionName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ��� ����������� �� ����� ���� ������ ����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::UnableToUseShortNameTransitCircuit ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror ���������� ������������ ������� ��� ���������� ����, � ������ %row, ������� %pos.%br", info.Row, info.Pos );
    return 0;
}
