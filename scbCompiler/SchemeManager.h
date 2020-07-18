#pragma once

#include <memory>
#include "Manager.h"
#include "SchemeObject.h"
#include "SchemeDescription.h"
#include "SchemeTuning.h"
#include "SchemeExternalLink.h"
#include "SchemeInternalConnection.h"
#include "SchemeExternalConnection.h"
#include "SchemeExtendedBlock.h"
#include "SchemeGrantingRequirement.h"
#include "SchemeRequestedRequirement.h"
#include "SchemeEvent.h"
#include "SchemeInputDescriptor.h"
#include "SchemeOutputDescriptor.h"

using std::unique_ptr;
using std::tuple;

class SchemeManager : public Manager
{

public:
	SchemeManager();
	virtual ~SchemeManager() override;

	virtual int parse(const ParseInfo& info) override;
	virtual void clear() override;
	virtual void compile() override;
	virtual void flushBinFile(const ofstream& file) override;
	virtual void flushLogFile(const wofstream& file) override;

private:
	/* ����� ��������� - ����� �����
		0 - ����� ����� (�����)
		1 - �������
		2 - ������� �����
		3 - ������� ������
		4 - ����������
		5 - ���������� �����
		6 - �����
		7 - ����
		8 - ������������
		9 - ���������������
		10 - ��������������� ����������
		11 - ���������
		12 - ����������� ���������
		13 - ����������� ���������
		14 - �������
		15 - ��������
		16 - �������� ������������
		17 - ��������������
		18 - �������������� ������������
		19 - ����������
		20 - ���������� ����
		21 - �����
		22 - �����
		23 - ������
		24 - ���������
		25 - ��������� ����
		26 - ����������������
		27 - �����
		28 - ����������
		29 - ������
		30 - ������ ������������
		*/
	int mode;
	int submode; // �������� - ������ ������ �����

	/* ������� ������
	0 - �����
	1 - ����������, ����������� ���������
	2 - ������� ������
	3 - ������� �����, ���������� �����
	4 - �����
	5 - ����, ������������, ��������������� ����������, ���������, �����, �����
	6 - ������ ������������, �������� ������������, �������������� ������������, �������
	7 - �����, ������, ���������� ����
	8 - ��������� ����, ����������������
	*/
	int level;

	wstring mainName;
	wstring currentString;
	wstring objectNameString;
	wstring objectGeneralNameString;
	ComplexName currentDescriptor;
	int currentConditionParam;
	ParseInfo backupParseInfo;
	ParseInfo startParseInfo;
	int backupIntVar;
	int iteration;
	int objectPlacement;
	wstring objectLocation;
	int objectOrder;
	wstring objectCable;
	int reqId;

	int multiplicator;
	wstring multiplicatingBlockName;
	bool isWithoutParameter;

	vector<SchemeDescription> descriptions;
	vector<SchemeTuning> tunings;
	vector<SchemeExternalLink> externalLinks;
	vector<SchemeInternalConnection> internalConnections;
	vector<SchemeExternalConnection> externalConnections;
	vector<SchemeExtendedBlock> extendedBlocks;
	vector<SchemeGrantingRequirement> grantingRequirements;
	vector<SchemeRequestedRequirement> requestedRequirements;
	vector<SchemeEvent> events;
	vector<SchemeInputDescriptor> inputDescriptors;
	vector<SchemeOutputDescriptor> outputDescriptors;

	vector<unique_ptr<SchemeObject>> objects;

	vector<int> requirementMask;

	// ��� ���������: 0 - ���������� ��������, 1 - ��� ����������, 2 - ��� ����������, 3 - ���������� ������� ������
	// ���������� ����� ��� ������������������ �����������, ���� ��� �������������� ����������, ����� -1
	vector<tuple<wstring, int, int>> parameters;

	bool isDefinedNameInMainSection(const wstring& name) const;
	bool isDefinedNameInInputSection(const wstring& name) const;
	int getBlockIdByName(const wstring& name) const;
	int getDeviceIdByName(const wstring& name) const;
	int getInputDescriptorIdByName(const ComplexName& descriptor, SchemeInputDescriptor::Type type) const;
	int getOutputDescriptorIdByName(const ComplexName& descriptor, SchemeOutputDescriptor::Type type) const;

	int parseScheme(const ParseInfo& info);
	int parseAlias(const ParseInfo& info);
	int parseTuning(const ParseInfo& info);
	int parseExternalLink(const ParseInfo& info);
	int parseExternalConnection(const ParseInfo& info);
	int parseInternalConnection(const ParseInfo& info);
	int parseBlock(const ParseInfo& info);
	int parseRelay(const ParseInfo& info);
	int parseEquipment(const ParseInfo& info);
	int parseVariable(const ParseInfo& info);
	int parseStatus(const ParseInfo& info);
	int parseEvent(const ParseInfo& info);
	int parseRequestRequirement(const ParseInfo& info);
	int parseTransmitRequirement(const ParseInfo& info);
	int parseGrantRequirement(const ParseInfo& info);
	int parseTransitCircuit(const ParseInfo& info);
	int parseCross(const ParseInfo& info);
	int parseLine(const ParseInfo& info);
	int parseInput(const ParseInfo& info);
	int parseOutput(const ParseInfo& info);
	int parseWorkingCircuit(const ParseInfo& info);
	int parseSensitive(const ParseInfo& info);

	int setConditionParam(const ParseInfo& info);
	int resetConditionParam(const ParseInfo& info);

	// ��������� ����� �������� �� ����������� ��������, ������� - ������ ��������� ��� -1 ��� ������
	int descriptorParameter(const ParseInfo& name, int order = -1);
	// ��������� ����� �������� �� ���������� � ���������, ������� - ������ ��������� ��� -1 ��� ������
	int placementNameParameter(const ParseInfo& name);
	// ��������� ����� �������� �� ���� � ���������, ������� - ������ ��������� ��� -1 ��� ������
	int aliasParameter(const ParseInfo& name);
	// ���������� ������������ ��������������� ��������, ���� ���������� ����� ��������������� ��������, ������� - ������ ��������� ��� -1 ��� ������
	int externalLinkParameter(const ParseInfo& name);
	/// ������� ������������ ��������, ����� ����������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> useAnyParameter(const ParseInfo& info);
	/// ������� ������������ ���������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> useAliasParameter(const ParseInfo& info);
	/// ������� ������������ ����������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> usePlacementParameter(const ParseInfo& info);
	/// ������� ������������ �������� �� ����������� ��������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> useDescriptorParameter(const ParseInfo& info);
	/// ������� ������������ �������� �� ������� ������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> useExternalLinkParameter(const ParseInfo& info);
	// ��������� � ������������� ���������� ��������� ������� ���, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int tagName(const ParseInfo& info);
	// ��������� � ������������� ���������� ������������ ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int tagParamName(const ParseInfo& info);
	// ��������� � ������������� ���������� ����� ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int tagNewExternalLinkParamName(const ParseInfo& info);
	// ��������� � ������������� ���������� ����� �������� �� ����������� ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int tagNewDescriptorParamName(const ParseInfo& info);
	// ��������� � ������������� ���������� ��������� ��� ( ��������� ), ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int tagGroupName(const ParseInfo& info);
	// ��������� ������� �� ������������ �� ����������� ���������� � ���������, ������� : 0 - ����� ������� �����, �� 0 - ����������� ��������
	int checkConditions(const ParseInfo& info, const vector<tuple<int, int, bool>>& conditions);

	int clearObjectName();
	int addPatternToObjectName(const ParseInfo& info);
	int addParamToObjectName(const ParseInfo& info);

	int schemeAddNew(const ParseInfo& info);
	int schemeDescriptor(const ParseInfo& info);
	int schemeSetMultiplicator(const ParseInfo& info);
	int schemeAddNewPlacementName(const ParseInfo& info);
	int schemeSetPlacementType(const ParseInfo& info);
	int schemeAddNewDescriptionGroup(const ParseInfo& info);
	int schemeAddNewDescriptionTag(const ParseInfo& info);
	int schemeCheckDescriptionGroup(const ParseInfo& info);
	int schemeMultiplicate(const ParseInfo& info);
	int schemeAddNewBlockName(const ParseInfo& info);

	int aliasAddAlias(const ParseInfo& info);
	int aliasPreParamString(const ParseInfo& info);
	int aliasParamString(const ParseInfo& info);
	int aliasPostParamString(const ParseInfo& info);
	int aliasSortParam(const ParseInfo& info);

	int tuningAddNew(const ParseInfo& info);
	int tuningDescriptor(const ParseInfo& info);
	int tuningCheckDescriptor(const ParseInfo& info);
	int tuningAddNewDescriptionTag(const ParseInfo& info);
	int tuningCheckDescriptionAndTuning(const ParseInfo& info);

	int externalLinkAddNew(const ParseInfo& info);
	int externalLinkDescriptor(const ParseInfo& info);
	int externalLinkNecesserily(const ParseInfo& info);
	int externalLinkDescriptionTag(const ParseInfo& info);
	int externalLinkAddCondition(const ParseInfo& info);
	int externalLinkAddConditionGroup(const ParseInfo& info);
	int externalLinkCheckConditionGroup(const ParseInfo& info);

	int externalConnectionAddNew(const ParseInfo& info);
	int externalConnectionDescriptor(const ParseInfo& info);
	int externalConnectionAddCondition(const ParseInfo& info);
	int externalConnectionAddConditionGroup(const ParseInfo& info);
	int externalConnectionCheckConditionGroup(const ParseInfo& info);

	int internalConnectionAddNew(const ParseInfo& info);
	int internalConnectionFirstDescriptor(const ParseInfo& info);
	int internalConnectionSecondDescriptor(const ParseInfo& info);
	int internalConnectionAddCondition(const ParseInfo& info);
	int internalConnectionAddConditionGroup(const ParseInfo& info);
	int internalConnectionCheckConditionGroup(const ParseInfo& info);

	int extendedBlockAddNew(const ParseInfo& info);
	int extendedBlockName(const ParseInfo& info);
	int extendedBlockDefaultCount(const ParseInfo& info);
	int extendedBlockAddConditionGroup(const ParseInfo& info);
	int extendedBlockAddCondition(const ParseInfo& info);
	int extendedBlockCheckConditionGroup(const ParseInfo& info);

	int blockAddNew(const ParseInfo& info);
	int blockSetTypeName(const ParseInfo& info);
	int blockSetPlacement(const ParseInfo& info);
	int blockSetLocation(const ParseInfo& info);
	int blockAddObjectName(const ParseInfo& info);
	int blockFixMultipleNames(const ParseInfo& info);
	int blockFixSingleName(const ParseInfo& info);

	int relayAddNew(const ParseInfo& info);
	int relaySetTypeName(const ParseInfo& info);
	int relaySetBlock(const ParseInfo& info);
	int relaySetPlacement(const ParseInfo& info);
	int relaySetLocation(const ParseInfo& info);
	int relayAddObjectName(const ParseInfo& info);
	int relayAddJumper(const ParseInfo& info);
	int relayAddCondition(const ParseInfo& info);
	int relayAddConditionGroup(const ParseInfo& info);
	int relayCheckConditionGroup(const ParseInfo& info);
	int relaySetRequirement(const ParseInfo& info);
	int relaySetRequirementFrom(const ParseInfo& info);
	int relaySetRequirementTo(const ParseInfo& info);
	int relayFixDescription(const ParseInfo& info);
	int relayRequirementName(const ParseInfo& info);
	int relayRequirementPlacement(const ParseInfo& info);
	int relayFixRequirement(const ParseInfo& info);

	int equipmentAddNew(const ParseInfo& info);
	int equipmentSetType(const ParseInfo& info);
	int equipmentSetNominal(const ParseInfo& info);
	int equipmentSetUnit(const ParseInfo& info);
	int equipmentSetPowerClass(const ParseInfo& info);
	int equipmentSetPlacement(const ParseInfo& info);
	int equipmentSetBlock(const ParseInfo& info);
	int equipmentSetLocation(const ParseInfo& info);
	int equipmentAddObjectName(const ParseInfo& info);
	int equipmentAddJumper(const ParseInfo& info);
	int equipmentAddCondition(const ParseInfo& info);
	int equipmentAddConditionGroup(const ParseInfo& info);
	int equipmentCheckConditionGroup(const ParseInfo& info);
	int equipmentFixDescription(const ParseInfo& info);

	int statusAddNew(const ParseInfo& info);
	int statusSetDefaultOne(const ParseInfo& info);

	int variableAddNew(const ParseInfo& info);

	int lineAddNew(const ParseInfo& info);
	int lineDescriptor(const ParseInfo& info);
	int lineAddCondition(const ParseInfo& info);
	int lineAddConditionGroup(const ParseInfo& info);
	int lineCheckConditionGroup(const ParseInfo& info);

	int crossPlacement(const ParseInfo& info);
	int crossLocation(const ParseInfo& info);
	int crossOrder(const ParseInfo& info);
	int crossCable(const ParseInfo& info);
	int crossGeneralName(const ParseInfo& info);
	int crossAddNew(const ParseInfo& info);
	int crossName(const ParseInfo& info);
	int crossAddContact(const ParseInfo& info);
	int crossCount(const ParseInfo& info);
	int crossAddCondition(const ParseInfo& info);
	int crossAddConditionGroup(const ParseInfo& info);
	int crossCheckConditionGroup(const ParseInfo& info);

	int eventDescriptor(const ParseInfo& info);
	int eventSetStatus(const ParseInfo& info);
	int eventResetStatus(const ParseInfo& info);
	int eventProbablityClass(const ParseInfo& info);
	int eventAddCondition(const ParseInfo& info);
	int eventAddConditionGroup(const ParseInfo& info);
	int eventCheckConditionGroup(const ParseInfo& info);

	int grantRequirementSourceName(const ParseInfo& info);
	int grantRequirementAddRequirementName(const ParseInfo& info);
	int grantRequirementCheckOutputDescriptorTemplate(const ParseInfo& info);
	int grantRequirementSetOutputCount(const ParseInfo& info);
	int grantRequirementAddNewRecord(const ParseInfo& info);
	int grantRequirementFrom(const ParseInfo& info);
	int grantRequirementTo(const ParseInfo& info);
	int grantRequirementOutput(const ParseInfo& info);
	int grantRequirementFixRecord(const ParseInfo& info);
	int grantRequirementEnd(const ParseInfo& info);

	int transmitRequirementRequestedName(const ParseInfo& info);
	int transmitRequirementAddGrantingName(const ParseInfo& info);
	int transmitRequirementFix(const ParseInfo& info);

	int requestedRequirementRequestedName(const ParseInfo& info);
	int requestedRequirementAddInputName(const ParseInfo& info);
	int requestedRequirementAddFakeInput(const ParseInfo& info);
	int requestedRequirementFix(const ParseInfo& info);

	int transitCircuitTargetOutput(const ParseInfo& info);
	int transitCircuitOutput(const ParseInfo& info);
	int transitCircuitFreeInput(const ParseInfo& info);
	int transitCircuitInput(const ParseInfo& info);
	int transitCircuitName(const ParseInfo& info);
	int transitCircuitAddCondition(const ParseInfo& info);
	int transitCircuitAddConditionGroup(const ParseInfo& info);
	int transitCircuitCheckConditionGroup(const ParseInfo& info);

};