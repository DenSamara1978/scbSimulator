#pragma once

#include "scbMessage.h"
#include "scbParseInfo.h"
#include <vector>

class scbMessagePool
{
	vector<scbMessage> m_Pool;

public:
	scbMessagePool ();

	void Clear ();
	const vector<scbMessage>& GetPool () const;

	int SyntaxError ( const scbParseInfo& info );
	int IncorrectTypeOfFile ();
	int FatalError ();
	int IncorrectLevelOfBlock ( const scbParseInfo& info );
	int NameAlwaysUsed ( const scbParseInfo& info );
	int InvalidMultiplicatorArgument ( const scbParseInfo& info );
	int IncorrectRepeatOfParameter ( const scbParseInfo& info );
	int IncorrectParameter ( const scbParseInfo& info );
	int IncorrectDescriptorTagOrder ( const scbParseInfo& info );
	int IncorrectDescriptorGroupTag ( const scbParseInfo& info );
	int IncorrectDescriptorTag ( const scbParseInfo& info );
	int IncorrectDescriptionTag ( const scbParseInfo& info );
	int IncorrectRepeatOfDescriptionTag ( const scbParseInfo& info );
	int IncorrectPlacementType ( const scbParseInfo& info );
	int UnknownTypeOfRelay ( const wstring& name, const wstring& type, const scbParseInfo& info );
    int UnknownTypeOfEquipment ( const wstring& name, const wstring& type, const scbParseInfo& info );
    int UnknownTypeOfBlock ( const scbParseInfo& info, const wstring& name );
	int IncorrectOrderOfDescription ( const scbParseInfo& info );
	int IncorrectRepeatOfDescription ( const scbParseInfo& info );
	int DeviceCantHaveAnyJumper ( const scbParseInfo& info, const wstring& type );
	int DeviceCantHaveThisJumper ( const scbParseInfo& info, const wstring& type );
    int DeviceCantHaveNominal ( const scbParseInfo& info, const wstring& type );
    int DeviceMustHaveNominal ( const scbParseInfo& info, const wstring& type );
    int DeviceMustHavePowerClass ( const scbParseInfo& info, const wstring& type );
    int DeviceMustHaveObjectName ( const scbParseInfo& info, const wstring& type );
    int DeviceCantHaveThisUnit ( const scbParseInfo& info, const wstring& type );
    int DeviceCantHavePowerClass ( const scbParseInfo& info, const wstring& type );
    int IncorrectPowerClass ( const scbParseInfo& info );
    int IncorrectRepeatOfJumper ( const scbParseInfo& info );
    int IncorrectRepeatOfContact ( const scbParseInfo& info );
    int DeviceCantHaveThisContact ( const scbParseInfo& info );
	int DeviceHasIncompleteSetOfJumpers ( const scbParseInfo& info );
	int DeviceHasIncompatibleSetOfJumpers ( const scbParseInfo& info );
	int RelayCantUseToCoverAnyRequirement ( const scbParseInfo& info, const wstring& type );
	int NumberExcepted ( const scbParseInfo& info );
	int NumberIsOutOfRange ( const scbParseInfo& info );
	int IncorrectRepeatOfPlacementName ( const scbParseInfo& info );
	int IncorrectRepeatOfPlacementType ( const scbParseInfo& info );
	int InexactRepeatOfPlacement ( const scbParseInfo& info );
	int MultiplicatingDescriptorMustBeSingle ( const scbParseInfo& info );
	int DifferentDescriptionGroupsAreEqual ( const scbParseInfo& info );
	int IncorrectSectionBlockInAloneDescriptor ( const scbParseInfo& info );
	int TooMuchSectionBlockInDescriptor ( const scbParseInfo& info );
	int IncorrectCoincidingDescriptors ( const scbParseInfo& info );
	int IncorrectCoincidingDescriptionSets ( const scbParseInfo& info );
	int IncorrectDescriptorPresence ( const scbParseInfo& info );
	int IncorrectDescriptorAbsence ( const scbParseInfo& info );
	int UsingOfIncorrectDescriptor ( const scbParseInfo& info );
	int UnachievableDescriptionCombination ( const scbParseInfo& info );
	int MultiplicatingDescriptorCantHaveAnyConnection ( const scbParseInfo& info );
	int MultiplicatingDescriptorCantHaveAnyExternalLink ( const scbParseInfo& info );
	int MultiplicatingDescriptorCantHaveAnyExtendedBlock ( const scbParseInfo& info );
	int MultiplicatingDescriptorCantHaveAnyAliases ( const scbParseInfo& info );
	int ConditionParamIsRequired ( const scbParseInfo& info );
	int ConditionParamIsNotRequired ( const scbParseInfo& info );
	int CantHaveAnyInternalConnections ( const scbParseInfo& info );
	int CantHaveAnyExternalConnections ( const scbParseInfo& info );
	int CantHaveAnyExternalLinks ( const scbParseInfo& info );
	int CantHaveAnyExtendedBlocks ( const scbParseInfo& info );
	int DescriptorWithoutParameterMustBeSingle ( const scbParseInfo& info );
	int UsingInternalConnectionWithSameDescriptor ( const scbParseInfo& info );
	int InvalidExtendedBlockCountArgument ( const scbParseInfo& info );
	int UndefinedPlacementName ( const scbParseInfo& info );
	int IncompatiblePlacement ( const scbParseInfo& info );
	int SimpleDescriptorCantHaveAlternativeNames( const scbParseInfo& info );
	int IncorrectCountOfAlternativeNames ( const scbParseInfo& info );
	int LocationStillOccupied ( const scbParseInfo& info );
	int DeviceCantOccupyTheLocation ( const scbParseInfo& info );
	int InactiveParameter ( const scbParseInfo& info );
    int RequirementDoesntCoverWholeRange ( const scbParseInfo& info );
    int RequirementFromIsGreaterThanTo ( const scbParseInfo& info );
    int NameMustBeTheStatus ( const scbParseInfo& info );
    int NameWasNotFound ( const scbParseInfo& info );
    int IncorrectRepeatOfDescriptor ( const scbParseInfo& info );
    int IncorrectRepeatOfRequirementName ( const scbParseInfo& info );
    int IncorrectRepeatOfRequirementDescriptor ( const scbParseInfo& info );
    int IncorrectRequirementName ( const scbParseInfo& info );
    int IncorrectProbablityClass ( const scbParseInfo& info );
    int IncorrectCountOfOutput ( const scbParseInfo& info );
    int IncorrectGroupTagInDescriptor ( const scbParseInfo& info );
    int MoreThanOneRecordForThisNumberOfRequestingRequirement ( const scbParseInfo& info );
    int UnableToGrantThisRequirement ( const scbParseInfo& info );
    int WholeInputsInRequestingRequirementAreZero ( const scbParseInfo& info );
    int RequirementNameMustBeNonDescriptionName ( const scbParseInfo& info );
    int UnableToUseShortNameTransitCircuit ( const scbParseInfo& info );
};

inline const vector<scbMessage>& scbMessagePool::GetPool () const
{
	return this->m_Pool;
}
