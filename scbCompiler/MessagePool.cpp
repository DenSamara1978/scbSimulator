#include "MessagePool.h"

MessagePool::MessagePool()
{
}


void MessagePool::clear()
{
	this->pool.clear();
}

int MessagePool::syntaxError(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������������� ������ � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 1;
}

int MessagePool::incorrectTypeOfFile()
{
	this->pool.emplace_back(L"%compilationerror �������� ������ �������� �����.%br");
	return 1;
}

int MessagePool::fatalError()
{
	this->pool.emplace_back(L"%compilationerror ��������� ������, ���������� ��������.%br");
	return 1;
}

int MessagePool::incorrectLevelOfBlock(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������ ������������ ����� ������ %param1 � ������ %row.%br", info.row, info.token);
	return 1;
}

int MessagePool::nameAlwaysUsed(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��������� ������������� ����� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::invalidMultiplicatorArgument(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ �������� ��������������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ��������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������� �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorTagOrder(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ����������� �� �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorGroupTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ��������� ������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ��� ����������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptionTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ��� �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfDescriptionTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��������� ������������� ���� �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectPlacementType(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ��� ���������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::unknownTypeOfRelay(const wstring& name, const wstring& type, const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ��� '%param2' ���� '%param1' � ������ %row.%br", info.row, name, type);
	return 0;
}

int MessagePool::unknownTypeOfEquipment(const wstring& name, const wstring& type, const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ��� '%param2' ������������ '%param1' � ������ %row.%br", info.row, name, type);
	return 0;
}

int MessagePool::unknownTypeOfBlock(const ParseInfo& info, const wstring& name)
{
	this->pool.emplace_back(L"%compilationerror ����������� ��� '%param2' ����� '%param1' � ������ %row.%br", info.row, info.pos, name, info.token);
	return 0;
}

int MessagePool::incorrectOrderOfDescription(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������� ������� ���������� �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfDescription(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ �������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::deviceCantHaveAnyJumper(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ����������, ������� ��� '%param1', �� ����� ����� ���������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHaveThisJumper(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ����������, ������� ��� '%param1', �� ����� ����� ��������� %param2, � ������ %row, ������� %pos.%br", info.row, info.pos, type, info.token);
	return 0;
}

int MessagePool::deviceHasIncompleteSetOfJumpers(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� ����� �������� ����� ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantHaveNominal(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ���������� ���� %param1 �� ����� ����� �������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHaveNominal(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ���������� ���� %param1 ������ ����� �������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHavePowerClass(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ���������� ���� %param1 ������ ����� ����� �������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHaveObjectName(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ���������� ���� %param1 ������ ����� ������������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHaveThisUnit(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror �������� ������� ��������� �������� ���������� ���� %param1, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHavePowerClass(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ���������� ���� %param1 �� ����� ������ �������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::incorrectPowerClass(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ����� �������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfJumper(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfContact(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantHaveThisContact(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� �� ����� ��������� ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceHasIncompatibleSetOfJumpers(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� ����� ������������� ����� ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::relayCantUseToCoverAnyRequirement(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror ����, ������� ��� '%param1', �� ����� ����������� ��� �������������� ������������, � ������ %row, ������� %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::numberExcepted(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��������� ���������� ����� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::numberIsOutOfRange(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����� ����������� ���������� ��������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfPlacementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ����� ���������� '%param1' � ����� ��������, � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfPlacementType(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ���� �� ���� ���������� '%param1' � ����� ��������, � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::inexactRepeatOfPlacement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������� ������ ���������� � ������ ��������� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::multiplicatingDescriptorMustBeSingle(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������������� ���������� ������ ���� ������������ ������������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::differentDescriptionGroupsAreEqual(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationwarning �������� ����������� ������ ��������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectSectionBlockInAloneDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������������� ���������� �� ����� ����� ������ ����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::tooMuchSectionBlockInDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ���������� ������ ����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectCoincidingDescriptors(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������� ����������� �����������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectCoincidingDescriptionSets(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������� ����������� ������ ��������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectDescriptorPresence(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������� ����������� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectDescriptorAbsence(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ���������� ����������� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::usingOfIncorrectDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ���������� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unachievableDescriptionCombination(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ���������� �������� � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyConnection(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������������� ���������� �� ����� ����� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyExternalLink(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������������� ���������� �� ����� ����� ������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyExtendedBlock(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������������� ���������� �� ����� ������������ ��������� ������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyAliases(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������������� ���������� �� ����� ������������ ����������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::conditionParamIsRequired(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������� ������� ��������� ����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::conditionParamIsNotRequired(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������� �� ������� ��������� ����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::cantHaveAnyInternalConnections(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� �������� ����� ���������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExternalConnections(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� �������� ����� ������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExternalLinks(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� �������� ����� ������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExtendedBlocks(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� ������������� ����� ���������� �������������� ������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::descriptorWithoutParameterMustBeSingle(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������������ �������� ���������� ����� ���� ������ ����, � ������ %row ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::usingInternalConnectionWithSameDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ���������� ����� ������ ������ �����������, � ������ %row ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::invalidExtendedBlockCountArgument(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ �������� ���������� ���������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::undefinedPlacementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������������� ��� ���������� '%param1' � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incompatiblePlacement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������ �� ����� ���� ���������� � ���������� '%param1', � ������ %row, ������� %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::simpleDescriptorCantHaveAlternativeNames(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������������� ���������� �� ����� ����� ������ � ��������������� �������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectCountOfAlternativeNames(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������������� ���������� �������������� ���� � ���������������� �����, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::locationStillOccupied(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��������� ����� � ���������� ��� ������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantOccupyTheLocation(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� �� ����� �������� ��������� �����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::inactiveParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������ ������������ ��������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::requirementDoesntCoverWholeRange(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� �� ����������� �������� ����������, � ������ %row.%br", info.row);
	return 0;
}

int MessagePool::requirementFromIsGreaterThanTo(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ������� �� � ������������� �������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::nameMustBeTheStatus(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ��� ������ ���� ���������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::nameWasNotFound(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ��� �� �������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfRequirementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ����� �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfRequirementDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ������������ ������ ����������� �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRequirementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��� ����������� �� �������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectProbablityClass(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������� ����� �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectCountOfOutput(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror �������������� ���������� �������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectGroupTagInDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��������� ��������� ��� ����������� �� ���������� �� ������� ������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::moreThanOneRecordForThisNumberOfRequestingRequirement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����� ����� ������ ��� ���������� ������ �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unableToGrantThisRequirement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ����������� ����������� ������������� ��������� �����������, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::wholeInputsInRequestingRequirementAreZero(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror � ������� ����������� �� ������ �� ���� ����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::requirementNameMustBeNonDescriptionName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ��� ����������� �� ����� ���� ������ ����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unableToUseShortNameTransitCircuit(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror ���������� ������������ ������� ��� ���������� ����, � ������ %row, ������� %pos.%br", info.row, info.pos);
	return 0;
}
