#pragma once

#include "Message.h"
#include "ParseInfo.h"
#include <vector>

class MessagePool
{
public:
	MessagePool();

	void clear();
	const vector<Message>& getPool() const;

	int syntaxError(const ParseInfo& info);
	int incorrectTypeOfFile();
	int fatalError();
	int incorrectLevelOfBlock(const ParseInfo& info);
	int nameAlwaysUsed(const ParseInfo& info);
	int invalidMultiplicatorArgument(const ParseInfo& info);
	int incorrectRepeatOfParameter(const ParseInfo& info);
	int incorrectParameter(const ParseInfo& info);
	int incorrectDescriptorTagOrder(const ParseInfo& info);
	int incorrectDescriptorGroupTag(const ParseInfo& info);
	int incorrectDescriptorTag(const ParseInfo& info);
	int incorrectDescriptionTag(const ParseInfo& info);
	int incorrectRepeatOfDescriptionTag(const ParseInfo& info);
	int incorrectPlacementType(const ParseInfo& info);
	int unknownTypeOfRelay(const wstring& name, const wstring& type, const ParseInfo& info);
	int unknownTypeOfEquipment(const wstring& name, const wstring& type, const ParseInfo& info);
	int unknownTypeOfBlock(const ParseInfo& info, const wstring& name);
	int incorrectOrderOfDescription(const ParseInfo& info);
	int incorrectRepeatOfDescription(const ParseInfo& info);
	int deviceCantHaveAnyJumper(const ParseInfo& info, const wstring& type);
	int deviceCantHaveThisJumper(const ParseInfo& info, const wstring& type);
	int deviceCantHaveNominal(const ParseInfo& info, const wstring& type);
	int deviceMustHaveNominal(const ParseInfo& info, const wstring& type);
	int deviceMustHavePowerClass(const ParseInfo& info, const wstring& type);
	int deviceMustHaveObjectName(const ParseInfo& info, const wstring& type);
	int deviceCantHaveThisUnit(const ParseInfo& info, const wstring& type);
	int deviceCantHavePowerClass(const ParseInfo& info, const wstring& type);
	int incorrectPowerClass(const ParseInfo& info);
	int incorrectRepeatOfJumper(const ParseInfo& info);
	int incorrectRepeatOfContact(const ParseInfo& info);
	int deviceCantHaveThisContact(const ParseInfo& info);
	int deviceHasIncompleteSetOfJumpers(const ParseInfo& info);
	int deviceHasIncompatibleSetOfJumpers(const ParseInfo& info);
	int relayCantUseToCoverAnyRequirement(const ParseInfo& info, const wstring& type);
	int numberExcepted(const ParseInfo& info);
	int numberIsOutOfRange(const ParseInfo& info);
	int incorrectRepeatOfPlacementName(const ParseInfo& info);
	int incorrectRepeatOfPlacementType(const ParseInfo& info);
	int inexactRepeatOfPlacement(const ParseInfo& info);
	int multiplicatingDescriptorMustBeSingle(const ParseInfo& info);
	int differentDescriptionGroupsAreEqual(const ParseInfo& info);
	int incorrectSectionBlockInAloneDescriptor(const ParseInfo& info);
	int tooMuchSectionBlockInDescriptor(const ParseInfo& info);
	int incorrectCoincidingDescriptors(const ParseInfo& info);
	int incorrectCoincidingDescriptionSets(const ParseInfo& info);
	int incorrectDescriptorPresence(const ParseInfo& info);
	int incorrectDescriptorAbsence(const ParseInfo& info);
	int usingOfIncorrectDescriptor(const ParseInfo& info);
	int unachievableDescriptionCombination(const ParseInfo& info);
	int multiplicatingDescriptorCantHaveAnyConnection(const ParseInfo& info);
	int multiplicatingDescriptorCantHaveAnyExternalLink(const ParseInfo& info);
	int multiplicatingDescriptorCantHaveAnyExtendedBlock(const ParseInfo& info);
	int multiplicatingDescriptorCantHaveAnyAliases(const ParseInfo& info);
	int conditionParamIsRequired(const ParseInfo& info);
	int conditionParamIsNotRequired(const ParseInfo& info);
	int cantHaveAnyInternalConnections(const ParseInfo& info);
	int cantHaveAnyExternalConnections(const ParseInfo& info);
	int cantHaveAnyExternalLinks(const ParseInfo& info);
	int cantHaveAnyExtendedBlocks(const ParseInfo& info);
	int descriptorWithoutParameterMustBeSingle(const ParseInfo& info);
	int usingInternalConnectionWithSameDescriptor(const ParseInfo& info);
	int invalidExtendedBlockCountArgument(const ParseInfo& info);
	int undefinedPlacementName(const ParseInfo& info);
	int incompatiblePlacement(const ParseInfo& info);
	int simpleDescriptorCantHaveAlternativeNames(const ParseInfo& info);
	int incorrectCountOfAlternativeNames(const ParseInfo& info);
	int locationStillOccupied(const ParseInfo& info);
	int deviceCantOccupyTheLocation(const ParseInfo& info);
	int inactiveParameter(const ParseInfo& info);
	int requirementDoesntCoverWholeRange(const ParseInfo& info);
	int requirementFromIsGreaterThanTo(const ParseInfo& info);
	int nameMustBeTheStatus(const ParseInfo& info);
	int nameWasNotFound(const ParseInfo& info);
	int incorrectRepeatOfDescriptor(const ParseInfo& info);
	int incorrectRepeatOfRequirementName(const ParseInfo& info);
	int incorrectRepeatOfRequirementDescriptor(const ParseInfo& info);
	int incorrectRequirementName(const ParseInfo& info);
	int incorrectProbablityClass(const ParseInfo& info);
	int incorrectCountOfOutput(const ParseInfo& info);
	int incorrectGroupTagInDescriptor(const ParseInfo& info);
	int moreThanOneRecordForThisNumberOfRequestingRequirement(const ParseInfo& info);
	int unableToGrantThisRequirement(const ParseInfo& info);
	int wholeInputsInRequestingRequirementAreZero(const ParseInfo& info);
	int requirementNameMustBeNonDescriptionName(const ParseInfo& info);
	int unableToUseShortNameTransitCircuit(const ParseInfo& info);

private:
	vector<Message> pool;

};

inline const vector<Message>& MessagePool::getPool() const
{
	return this->pool;
}
