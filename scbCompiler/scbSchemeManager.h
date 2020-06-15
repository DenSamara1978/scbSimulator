#pragma once

#include <memory>
#include "scbManager.h"
#include "scbSchemeObject.h"
#include "scbSchemeDescription.h"
#include "scbSchemeTuning.h"
#include "scbSchemeExternalLink.h"
#include "scbSchemeInternalConnection.h"
#include "scbSchemeExternalConnection.h"
#include "scbSchemeExtendedBlock.h"
#include "scbSchemeGrantingRequirement.h"
#include "scbSchemeRequestedRequirement.h"
#include "scbSchemeEvent.h"
#include "scbSchemeInputDescriptor.h"
#include "scbSchemeOutputDescriptor.h"

using std::unique_ptr;
using std::tuple;

class scbSchemeManager : public scbManager
{
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
	int m_Mode;
	int m_Submode; // �������� - ������ ������ �����

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
	int m_Level;

	wstring m_MainName;
	wstring m_CurrentString;
    wstring m_ObjectNameString;
    wstring m_ObjectGeneralNameString;
    scbComplexName m_CurrentDescriptor;
	int m_CurrentConditionParam;
	scbParseInfo m_BackupParseInfo;
	scbParseInfo m_StartParseInfo;
	int m_BackupIntVar;
	int m_Iteration;
    int m_ObjectPlacement;
    wstring m_ObjectLocation;
    int m_ObjectOrder;
    wstring m_ObjectCable;
    int m_ReqId;

	int m_Multiplicator;
	wstring m_MultiplicatingBlockName;
	bool m_IsWithoutParameter;

	vector<scbSchemeDescription> m_Descriptions;
	vector<scbSchemeTuning> m_Tunings;
	vector<scbSchemeExternalLink> m_ExternalLinks;
	vector<scbSchemeInternalConnection> m_InternalConnections;
	vector<scbSchemeExternalConnection> m_ExternalConnections;
	vector<scbSchemeExtendedBlock> m_ExtendedBlocks;
    vector<scbSchemeGrantingRequirement> m_GrantingRequirements;
    vector<scbSchemeRequestedRequirement> m_RequestedRequirements;
    vector<scbSchemeEvent> m_Events;
    vector<scbSchemeInputDescriptor> m_InputDescriptors;
    vector<scbSchemeOutputDescriptor> m_OutputDescriptors;

	vector<unique_ptr<scbSchemeObject>> m_Objects;

    vector<int> m_RequirementMask;

		// ��� ���������: 0 - ���������� ��������, 1 - ��� ����������, 2 - ��� ����������, 3 - ���������� ������� ������
		// ���������� ����� ��� ������������������ �����������, ���� ��� �������������� ����������, ����� -1
	vector<tuple<wstring, int, int>> m_Parameters;

	bool IsDefinedNameInMainSection ( const wstring& name ) const;
	bool IsDefinedNameInInputSection ( const wstring& name ) const;
	int GetBlockIdByName ( const wstring& name ) const;
    int GetDeviceIdByName ( const wstring& name ) const;
    int GetInputDescriptorIdByName ( const scbComplexName& descriptor, scbSchemeInputDescriptor::Type type ) const;
    int GetOutputDescriptorIdByName ( const scbComplexName& descriptor, scbSchemeOutputDescriptor::Type type ) const;

	int ParseScheme ( const scbParseInfo& info );
	int ParseAlias ( const scbParseInfo& info );
	int ParseTuning ( const scbParseInfo& info );
	int ParseExternalLink ( const scbParseInfo& info );
	int ParseExternalConnection ( const scbParseInfo& info );
	int ParseInternalConnection ( const scbParseInfo& info );
	int ParseBlock ( const scbParseInfo& info );
	int ParseRelay ( const scbParseInfo& info );
	int ParseEquipment ( const scbParseInfo& info );
	int ParseVariable ( const scbParseInfo& info );
	int ParseStatus ( const scbParseInfo& info );
	int ParseEvent ( const scbParseInfo& info );
    int ParseRequestRequirement ( const scbParseInfo& info );
    int ParseTransmitRequirement ( const scbParseInfo& info );
	int ParseGrantRequirement ( const scbParseInfo& info );
	int ParseTransitCircuit ( const scbParseInfo& info );
	int ParseCross ( const scbParseInfo& info );
	int ParseLine ( const scbParseInfo& info );
	int ParseInput ( const scbParseInfo& info );
	int ParseOutput ( const scbParseInfo& info );
	int ParseWorkingCircuit ( const scbParseInfo& info );
	int ParseSensitive ( const scbParseInfo& info );

	int SetConditionParam ( const scbParseInfo& info );
	int ResetConditionParam ( const scbParseInfo& info );

		// ��������� ����� �������� �� ����������� ��������, ������� - ������ ��������� ��� -1 ��� ������
	int DescriptorParameter ( const scbParseInfo& name, int order = -1 );
		// ��������� ����� �������� �� ���������� � ���������, ������� - ������ ��������� ��� -1 ��� ������
	int PlacementNameParameter ( const scbParseInfo& name );
		// ��������� ����� �������� �� ���� � ���������, ������� - ������ ��������� ��� -1 ��� ������
	int AliasParameter ( const scbParseInfo& name );
		// ���������� ������������ ��������������� ��������, ���� ���������� ����� ��������������� ��������, ������� - ������ ��������� ��� -1 ��� ������
	int ExternalLinkParameter ( const scbParseInfo& name );
		/// ������� ������������ ��������, ����� ����������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> UseAnyParameter ( const scbParseInfo& info );
		/// ������� ������������ ���������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> UseAliasParameter ( const scbParseInfo& info );
		/// ������� ������������ ����������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> UsePlacementParameter ( const scbParseInfo& info );
		/// ������� ������������ �������� �� ����������� ��������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
	pair<int, int> UseDescriptorParameter ( const scbParseInfo& info );
        /// ������� ������������ �������� �� ������� ������, ������� - ( 0 - ��� ��, -1 - ������ ), ( ������ ��������� ��� -1 ��� ������ )
    pair<int, int> UseExternalLinkParameter ( const scbParseInfo& info );
        // ��������� � ������������� ���������� ��������� ������� ���, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int TagName ( const scbParseInfo& info );
		// ��������� � ������������� ���������� ������������ ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int TagParamName ( const scbParseInfo& info );
		// ��������� � ������������� ���������� ����� ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int TagNewExternalLinkParamName ( const scbParseInfo& info );
		// ��������� � ������������� ���������� ����� �������� �� ����������� ��������, ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int TagNewDescriptorParamName ( const scbParseInfo& info );
		// ��������� � ������������� ���������� ��������� ��� ( ��������� ), ������� - 0 - ����� ������� ������, 1 - ��������� ������
	int TagGroupName ( const scbParseInfo& info );
		// ��������� ������� �� ������������ �� ����������� ���������� � ���������, ������� : 0 - ����� ������� �����, �� 0 - ����������� ��������
	int CheckConditions ( const scbParseInfo& info, const vector<tuple<int, int, bool>>& conditions );

    int ClearObjectName ();
	int AddPatternToObjectName ( const scbParseInfo& info );
	int AddParamToObjectName ( const scbParseInfo& info );

	int Scheme_AddNew ( const scbParseInfo& info );
	int Scheme_Descriptor ( const scbParseInfo& info );
	int Scheme_SetMultiplicator ( const scbParseInfo& info );
	int Scheme_AddNewPlacementName ( const scbParseInfo& info );
	int Scheme_SetPlacementType ( const scbParseInfo& info );
	int Scheme_AddNewDescriptionGroup ( const scbParseInfo& info );
	int Scheme_AddNewDescriptionTag ( const scbParseInfo& info );
	int Scheme_CheckDescriptionGroup ( const scbParseInfo& info );
	int Scheme_Multiplicate ( const scbParseInfo& info );
	int Scheme_AddNewBlockName ( const scbParseInfo& info );

	int Alias_AddAlias ( const scbParseInfo& info );
	int Alias_PreParamString ( const scbParseInfo& info );
	int Alias_ParamString ( const scbParseInfo& info );
	int Alias_PostParamString ( const scbParseInfo& info );
	int Alias_SortParam ( const scbParseInfo& info );

	int Tuning_AddNew ( const scbParseInfo& info );
	int Tuning_Descriptor ( const scbParseInfo& info );
	int Tuning_CheckDescriptor ( const scbParseInfo& info );
	int Tuning_AddNewDescriptionTag ( const scbParseInfo& info );
	int Tuning_CheckDescriptionAndTuning ( const scbParseInfo& info );

	int ExternalLink_AddNew ( const scbParseInfo& info );
	int ExternalLink_Descriptor ( const scbParseInfo& info );
	int ExternalLink_Necesserily ( const scbParseInfo& info );
	int ExternalLink_DescriptionTag ( const scbParseInfo& info );
	int ExternalLink_AddCondition ( const scbParseInfo& info );
	int ExternalLink_AddConditionGroup ( const scbParseInfo& info );
	int ExternalLink_CheckConditionGroup ( const scbParseInfo& info );

	int ExternalConnection_AddNew ( const scbParseInfo& info );
	int ExternalConnection_Descriptor ( const scbParseInfo& info );
	int ExternalConnection_AddCondition ( const scbParseInfo& info );
	int ExternalConnection_AddConditionGroup ( const scbParseInfo& info );
	int ExternalConnection_CheckConditionGroup ( const scbParseInfo& info );

	int InternalConnection_AddNew ( const scbParseInfo& info );
	int InternalConnection_FirstDescriptor ( const scbParseInfo& info );
	int InternalConnection_SecondDescriptor ( const scbParseInfo& info );
	int InternalConnection_AddCondition ( const scbParseInfo& info );
	int InternalConnection_AddConditionGroup ( const scbParseInfo& info );
	int InternalConnection_CheckConditionGroup ( const scbParseInfo& info );

	int ExtendedBlock_AddNew ( const scbParseInfo& info );
	int ExtendedBlock_Name ( const scbParseInfo& info );
	int ExtendedBlock_DefaultCount ( const scbParseInfo& info );
	int ExtendedBlock_AddConditionGroup ( const scbParseInfo& info );
	int ExtendedBlock_AddCondition ( const scbParseInfo& info );
	int ExtendedBlock_CheckConditionGroup ( const scbParseInfo& info );

	int Block_AddNew ( const scbParseInfo& info );
	int Block_SetTypeName ( const scbParseInfo& info );
	int Block_SetPlacement ( const scbParseInfo& info );
	int Block_SetLocation ( const scbParseInfo& info );
	int Block_AddObjectName ( const scbParseInfo& info );
	int Block_FixMultipleNames ( const scbParseInfo& info );
	int Block_FixSingleName ( const scbParseInfo& info );

	int Relay_AddNew ( const scbParseInfo& info );
	int Relay_SetTypeName ( const scbParseInfo& info );
	int Relay_SetBlock ( const scbParseInfo& info );
	int Relay_SetPlacement ( const scbParseInfo& info );
	int Relay_SetLocation ( const scbParseInfo& info );
	int Relay_AddObjectName ( const scbParseInfo& info );
	int Relay_AddJumper ( const scbParseInfo& info );
	int Relay_AddCondition ( const scbParseInfo& info );
	int Relay_AddConditionGroup ( const scbParseInfo& info );
	int Relay_CheckConditionGroup ( const scbParseInfo& info );
    int Relay_SetRequirement ( const scbParseInfo& info );
	int Relay_SetRequirementFrom ( const scbParseInfo& info );
	int Relay_SetRequirementTo ( const scbParseInfo& info );
	int Relay_FixDescription ( const scbParseInfo& info );
    int Relay_RequirementName ( const scbParseInfo& info );
    int Relay_RequirementPlacement ( const scbParseInfo& info );
    int Relay_FixRequirement ( const scbParseInfo& info );

    int Equipment_AddNew ( const scbParseInfo& info );
    int Equipment_SetType ( const scbParseInfo& info );
    int Equipment_SetNominal ( const scbParseInfo& info );
    int Equipment_SetUnit ( const scbParseInfo& info );
    int Equipment_SetPowerClass ( const scbParseInfo& info );
    int Equipment_SetPlacement ( const scbParseInfo& info );
    int Equipment_SetBlock ( const scbParseInfo& info );
    int Equipment_SetLocation ( const scbParseInfo& info );
    int Equipment_AddObjectName ( const scbParseInfo& info );
    int Equipment_AddJumper ( const scbParseInfo& info );
    int Equipment_AddCondition ( const scbParseInfo& info );
    int Equipment_AddConditionGroup ( const scbParseInfo& info );
    int Equipment_CheckConditionGroup ( const scbParseInfo& info );
    int Equipment_FixDescription ( const scbParseInfo& info );

    int Status_AddNew ( const scbParseInfo& info );
    int Status_SetDefaultOne ( const scbParseInfo& info );

    int Variable_AddNew ( const scbParseInfo& info );

    int Line_AddNew ( const scbParseInfo& info );
    int Line_Descriptor ( const scbParseInfo& info );
    int Line_AddCondition ( const scbParseInfo& info );
    int Line_AddConditionGroup ( const scbParseInfo& info );
    int Line_CheckConditionGroup ( const scbParseInfo& info );

    int Cross_Placement ( const scbParseInfo& info );
    int Cross_Location ( const scbParseInfo& info );
    int Cross_Order ( const scbParseInfo& info );
    int Cross_Cable ( const scbParseInfo& info );
    int Cross_GeneralName ( const scbParseInfo& info );
    int Cross_AddNew ( const scbParseInfo& info );
    int Cross_Name ( const scbParseInfo& info );
    int Cross_AddContact ( const scbParseInfo& info );
    int Cross_Count ( const scbParseInfo& info );
    int Cross_AddCondition ( const scbParseInfo& info );
    int Cross_AddConditionGroup ( const scbParseInfo& info );
    int Cross_CheckConditionGroup ( const scbParseInfo& info );

    int Event_Descriptor ( const scbParseInfo& info );
    int Event_SetStatus ( const scbParseInfo& info );
    int Event_ResetStatus ( const scbParseInfo& info );
    int Event_ProbablityClass ( const scbParseInfo& info );
    int Event_AddCondition ( const scbParseInfo& info );
    int Event_AddConditionGroup ( const scbParseInfo& info );
    int Event_CheckConditionGroup ( const scbParseInfo& info );

    int GrantRequirement_SourceName ( const scbParseInfo& info );
    int GrantRequirement_AddRequirementName ( const scbParseInfo& info );
    int GrantRequirement_CheckOutputDescriptorTemplate ( const scbParseInfo& info );
    int GrantRequirement_SetOutputCount ( const scbParseInfo& info );
    int GrantRequirement_AddNewRecord ( const scbParseInfo& info );
    int GrantRequirement_From ( const scbParseInfo& info );
    int GrantRequirement_To ( const scbParseInfo& info );
    int GrantRequirement_Output ( const scbParseInfo& info );
    int GrantRequirement_FixRecord ( const scbParseInfo& info );
    int GrantRequirement_End ( const scbParseInfo& info );

    int TransmitRequirement_RequestedName ( const scbParseInfo& info );
    int TransmitRequirement_AddGrantingName ( const scbParseInfo& info );
    int TransmitRequirement_Fix ( const scbParseInfo& info );

    int RequestedRequirement_RequestedName ( const scbParseInfo& info );
    int RequestedRequirement_AddInputName ( const scbParseInfo& info );
    int RequestedRequirement_AddFakeInput ( const scbParseInfo& info );
    int RequestedRequirement_Fix ( const scbParseInfo& info );

    int TransitCircuit_TargetOutput ( const scbParseInfo& info );
    int TransitCircuit_Output ( const scbParseInfo& info );
    int TransitCircuit_FreeInput ( const scbParseInfo& info );
    int TransitCircuit_Input ( const scbParseInfo& info );
    int TransitCircuit_Name ( const scbParseInfo& info );
    int TransitCircuit_AddCondition ( const scbParseInfo& info );
    int TransitCircuit_AddConditionGroup ( const scbParseInfo& info );
    int TransitCircuit_CheckConditionGroup ( const scbParseInfo& info );

public:
	scbSchemeManager ();
	virtual ~scbSchemeManager () override;

	virtual int Parse ( const scbParseInfo& info ) override;
	virtual void Clear () override;
	virtual void Compile () override;
	virtual void FlushBinFile ( const ofstream& file ) override;
	virtual void FlushLogFile ( const wofstream& file ) override;
};