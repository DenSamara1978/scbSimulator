#include <algorithm>

#include "scbSchemeManager.h"
#include "scbSchemeObject.h"
#include "scbSchemeStatus.h"
#include "scbSchemeVariable.h"
#include "scbSchemeBlock.h"
#include "scbSchemeLine.h"
#include "scbSchemeCross.h"
#include "scbSchemeInput.h"
#include "scbSchemeOutput.h"

#include "scbSchemeIncorrectRelay.h"

#include "scbRelay_NMSH1_400.h"
#include "scbRelay_NMSH1_1440.h"
#include "scbRelay_NMSHM1_11.h"
#include "scbRelay_NMSHM1_560.h"
#include "scbRelay_NMSHM1_1120.h"
#include "scbRelay_NMSHM1_1000_560.h"

#include "scbRelay_NMSH2_4000.h"
#include "scbRelay_NMSHM2_1_5.h"
#include "scbRelay_NMSHM2_1500.h"
#include "scbRelay_NMSHM2_3000.h"

#include "scbRelay_NMSH3_460_400.h"

#include "scbRelay_NMSH4_2400.h"
#include "scbRelay_NMSH4_3.h"

#include "scbRelay_OMSH2_46.h"

#include "scbRelay_ANVSH2_2400.h"

#include "scbRelay_NMPSH_900.h"
#include "scbRelay_NMPSH2_400.h"
#include "scbRelay_NMPSH3M_02_250.h"

#include "scbRelay_PMPUSH_150_150.h"

#include "scbRelay_KMSH_450.h"
#include "scbRelay_KMSH_750.h"
#include "scbRelay_KMSH_3000.h"

#include "scbRelay_DSSH13A.h"

#include "scbRelay_PPR3_5000.h"

#include "scbRelay_KDR1_200.h"
#include "scbRelay_KDR1_280.h"

#include "scbRelay_KDR1M_3_8.h"
#include "scbRelay_KDR1M_120.h"
#include "scbRelay_KDR1M_280.h"
#include "scbRelay_KDR1M_435.h"

#include "scbSchemeResistor.h"
#include "scbSchemeRheostat.h"
#include "scbSchemeCapacitor.h"
#include "scbSchemeFuse.h"
#include "scbSchemeDiode.h"
#include "scbSchemeTimeBlock.h"
#include "scbSchemeMeasuringPanel.h"
#include "scbSchemeTransformer_ST4.h"
#include "scbSchemeTransformer_ST5.h"
#include "scbSchemeTransformer_SKT.h"

scbSchemeManager::scbSchemeManager () :
    m_Mode ( 0 ),
    m_Submode ( 0 ),
    m_Level ( 0 ),
    m_Multiplicator ( 0 ),
    m_IsWithoutParameter ( false ),
    m_ReqId ( -1 ),
    m_ObjectPlacement ( -1 ),
    m_ObjectOrder ( -1 )
{
    this->m_RequirementMask.resize ( 101, 0 );
}

scbSchemeManager::~scbSchemeManager ()
{
}

void scbSchemeManager::Clear ()
{
	this->m_Mode = 0;
	this->m_Submode = 0;
	this->m_Level = 0;
	this->m_Multiplicator = 0;
	this->m_IsWithoutParameter = false;
	this->m_MultiplicatingBlockName.clear ();
    this->m_ReqId = -1;
    this->m_ObjectPlacement = -1;
    this->m_ObjectOrder = -1;
    this->m_ObjectCable.clear ();
    this->m_ObjectLocation.clear ();
    this->m_RequirementMask.clear ();
    this->m_RequirementMask.resize ( 101, 0 );

    this->m_ObjectNameString.clear ();
    this->m_ObjectGeneralNameString.clear ();
	this->m_MainName.clear ();
	this->m_CurrentString.clear ();
	this->m_CurrentDescriptor.Clear ();
	this->m_BackupParseInfo = { L"", 0, 0 };
	this->m_Descriptions.clear ();
	this->m_Tunings.clear ();
	this->m_ExternalLinks.clear ();
	this->m_InternalConnections.clear ();
	this->m_ExternalConnections.clear ();
	this->m_ExtendedBlocks.clear ();
    this->m_GrantingRequirements.clear ();
    this->m_RequestedRequirements.clear ();
    this->m_Events.clear ();
    this->m_InputDescriptors.clear ();
    this->m_OutputDescriptors.clear ();

	this->m_Objects.clear ();
	this->m_Parameters.clear ();
}

bool scbSchemeManager::IsDefinedNameInMainSection ( const wstring& name ) const
{
	auto elm = find_if ( this->m_Objects.cbegin (), this->m_Objects.cend (), [&name] ( const auto& elm ) -> bool {
		return  (( elm->GetName () == name ) and 
			(( elm->GetObjectType () == scbSchemeObject::ObjectType::Block ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Relay ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Equipment ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Status ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Variable ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Cross ) or
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Line ) or 
            ( elm->GetObjectType () == scbSchemeObject::ObjectType::Output ) ));
    } );
	return ( elm != this->m_Objects.cend ());
}

bool scbSchemeManager::IsDefinedNameInInputSection ( const wstring& name ) const
{
	auto elm = find_if ( this->m_Objects.cbegin (), this->m_Objects.cend (), [&name] ( const auto& elm ) -> bool
	{
		return  ( ( elm->GetName () == name ) and
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Input ) );
	} );
	return ( elm != this->m_Objects.cend () );
}

int scbSchemeManager::GetBlockIdByName ( const wstring& name ) const
{
	const auto cbegin = this->m_Objects.cbegin ();
	const auto cend = this->m_Objects.cend ();
	const auto res = find_if ( this->m_Objects.cbegin (), this->m_Objects.cend (), [&name] ( const auto& elm ) -> bool
	{
		return  ( ( elm->GetName () == name ) and
			( elm->GetObjectType () == scbSchemeObject::ObjectType::Block ) );
	} );
	return ( res == cend ) ? -1 : res - cbegin;
}

int scbSchemeManager::GetDeviceIdByName ( const wstring& name ) const
{
    const auto cbegin = this->m_Objects.cbegin ();
    const auto cend = this->m_Objects.cend ();
    const auto res = find_if ( this->m_Objects.cbegin (), this->m_Objects.cend (), [&name] ( const auto& elm ) -> bool
    {
        return  ( elm->GetName () == name );
    } );
    return ( res == cend ) ? -1 : res - cbegin;
}

int scbSchemeManager::GetInputDescriptorIdByName ( const scbComplexName& descriptor, scbSchemeInputDescriptor::Type type ) const
{
    const auto cbegin = this->m_InputDescriptors.cbegin ();
    const auto cend = this->m_InputDescriptors.cend ();
    const auto res = find_if ( cbegin, cend, [&descriptor, &type] ( const auto& val ) -> bool { return val.CheckDescriptor ( descriptor, type );  } );
    return ( res == cend ) ? -1 : ( res - cbegin );
}

int scbSchemeManager::GetOutputDescriptorIdByName ( const scbComplexName& descriptor, scbSchemeOutputDescriptor::Type type ) const
{
    const auto cbegin = this->m_OutputDescriptors.cbegin ();
    const auto cend = this->m_OutputDescriptors.cend ();
    const auto res = find_if ( cbegin, cend, [&descriptor, &type] ( const auto& val ) -> bool { return val.CheckDescriptor ( descriptor, type ); } );
    return ( res == cend ) ? -1 : ( res - cbegin );
}

int scbSchemeManager::DescriptorParameter ( const scbParseInfo& info, int order )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	if ( cend != find_if ( cbegin, cend, [info] ( const auto& val ) { return ( get<0> ( val ) == info.Token ); } ))
		return -1;
	else
	{
		this->m_Parameters.emplace_back ( info.Token, 0, order );
		return this->m_Parameters.size () - 1;
	}
}

int scbSchemeManager::PlacementNameParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	if ( cend != find_if ( cbegin, cend, [info] ( const auto& val ) { return (( get<0> ( val ) == info.Token ) and ( get<1> ( val ) != 1 )); } ))
		return -1;
	else
	{
		const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return ( get<0> ( val ) == info.Token ); } );
		if ( cend == res )
		{
			this->m_Parameters.emplace_back ( info.Token, 1, -1 );
			return this->m_Parameters.size () - 1;
		}
		else
			return res - cbegin;
	}
}

int scbSchemeManager::AliasParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	if ( cend != find_if ( cbegin, cend, [info] ( const auto& val ) { return ( get<0> ( val ) == info.Token ); } ) )
		return -1;
	else
	{
		this->m_Parameters.emplace_back ( info.Token, 2, -1 );
		return this->m_Parameters.size () - 1;
	}
}

int scbSchemeManager::ExternalLinkParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	if ( cend != find_if ( cbegin, cend, [info] ( const auto& val ) { return ( get<0> ( val ) == info.Token ); } ))
		return -1;
	else
	{
		this->m_Parameters.emplace_back ( info.Token, 3, -1 );
		return this->m_Parameters.size () - 1;
	}
}

pair<int, int> scbSchemeManager::UseAnyParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return (( get<0> ( val ) == info.Token ) and ( get<1> ( val ) != 2 )); } );
	if ( res != cend )
		return pair { 0, res - cbegin };
	else
		return pair { -1, -1 };
}

pair<int, int> scbSchemeManager::UseAliasParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return (( get<0> ( val ) == info.Token ) and ( get<1> ( val ) == 2 )); } );
	if ( res != cend )
		return pair { 0, res - cbegin };
	else
		return pair { -1, -1 };
}

pair<int, int> scbSchemeManager::UseExternalLinkParameter ( const scbParseInfo& info )
{
    const auto cend = this->m_Parameters.cend ();
    const auto cbegin = this->m_Parameters.cbegin ();
    const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return ( ( get<0> ( val ) == info.Token ) and ( get<1> ( val ) == 3 ) ); } );
    if ( res != cend )
        return pair { 0, res - cbegin };
    else
        return pair { -1, -1 };
}

pair<int, int> scbSchemeManager::UsePlacementParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return ( ( get<0> ( val ) == info.Token ) and ( get<1> ( val ) == 1 ) ); } );
	if ( res != cend )
		return pair { 0, res - cbegin };
	else
		return pair { -1, -1 };
}

pair<int, int> scbSchemeManager::UseDescriptorParameter ( const scbParseInfo& info )
{
	const auto cend = this->m_Parameters.cend ();
	const auto cbegin = this->m_Parameters.cbegin ();
	const auto res = find_if ( cbegin, cend, [info] ( const auto& val ) { return (( get<0> ( val ) == info.Token ) and ( get<1> ( val ) == 0 )); } );
	if ( res != cend )
		return pair { 0, res - cbegin };
	else
		return pair { -1, -1 };
}

int scbSchemeManager::SetConditionParam ( const scbParseInfo& info )
{
	if ( this->m_Descriptions.size () == 1 )
		return this->m_MessagePool->ConditionParamIsNotRequired ( info );
	else
	{
		const auto [res, id] = this->UseDescriptorParameter ( info );
		if ( res != 0 )
			return this->m_MessagePool->IncorrectParameter ( info );
		else
		{
			this->m_CurrentConditionParam = id;
			return 0;
		}
	}
}

int scbSchemeManager::ResetConditionParam ( const scbParseInfo& info )
{
	if (( this->m_Descriptions.size () != 1 ) and ( this->m_ExternalLinks.size () == 0 ))
		return this->m_MessagePool->ConditionParamIsRequired ( info );
	else
	{
		this->m_CurrentConditionParam = -1;
		return 0;
	}
}

int scbSchemeManager::TagName ( const scbParseInfo& info )
{
	auto res = this->m_CurrentDescriptor.AddTagName ( info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptorTagOrder ( info );
	case 1:
		return this->m_MessagePool->IncorrectDescriptorTag ( info );
	}
	return 0;
}

int scbSchemeManager::TagParamName ( const scbParseInfo& info )
{
	const auto [ res, id ] = this->UseAnyParameter ( info );
	if ( res != 0 )
		return this->m_MessagePool->IncorrectParameter ( info );
	else if ( this->m_CurrentDescriptor.AddParamTagId ( scbManager::ParameterNameShift + id ) != 0 )
		return this->m_MessagePool->IncorrectDescriptorTagOrder ( info );
	else
		return 0;
}

int scbSchemeManager::TagNewDescriptorParamName ( const scbParseInfo& info )
{
	const auto id = this->DescriptorParameter ( info );
	if ( id == -1 )
		return this->m_MessagePool->IncorrectRepeatOfParameter ( info );
	else if ( this->m_CurrentDescriptor.AddParamTagId ( scbManager::ParameterNameShift + id ) != 0 )
		return this->m_MessagePool->IncorrectDescriptorTagOrder ( info );
	else
		return 0;
}

int scbSchemeManager::TagNewExternalLinkParamName ( const scbParseInfo& info )
{
	const auto id = this->ExternalLinkParameter ( info );
	if ( id == -1 )
		return this->m_MessagePool->IncorrectRepeatOfParameter ( info );
	else if ( this->m_CurrentDescriptor.AddParamTagId ( scbManager::ParameterNameShift + id ) != 0 )
		return this->m_MessagePool->IncorrectDescriptorTagOrder ( info );
	else
		return 0;
}

int scbSchemeManager::TagGroupName ( const scbParseInfo& info )
{
	auto res = this->m_CurrentDescriptor.AddGroupTagName ( info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptorTagOrder ( info );
	case 1:
		return this->m_MessagePool->IncorrectDescriptorGroupTag ( info );
	}
	return 0;
}

int scbSchemeManager::CheckConditions ( const scbParseInfo& info, const vector<tuple<int, int, bool>>& conditions )
{
	for ( const auto& tuning : this->m_Tunings )
	{
		if ( !( tuning.CheckConditionsForAchievable ( conditions ) ))
			return this->m_MessagePool->UnachievableDescriptionCombination ( info );
	}
	for ( const auto& desc : this->m_Descriptions )
	{
		if ( desc.CheckConditionsForAchievable ( conditions ) )
			return 0;
	}
	return this->m_MessagePool->UnachievableDescriptionCombination ( info );
}

int scbSchemeManager::ClearObjectName ()
{
    this->m_ObjectNameString.clear ();
    return 0;
}

int scbSchemeManager::AddPatternToObjectName ( const scbParseInfo& info )
{
	this->m_ObjectNameString += info.Token;
	return 0;
}

int scbSchemeManager::AddParamToObjectName ( const scbParseInfo& info )
{
	int param_id = -1;
	auto [res, id] = this->UseDescriptorParameter ( info );
	if ( res == 0 )
		param_id = id;
	else
	{
		auto [res1, id1] = this->UseAliasParameter ( info );
		if ( res1 == 0 )
			param_id = id1;
        else
        {
            auto [res2, id2] = this->UseExternalLinkParameter ( info );
            if ( res2 == 0 )
                param_id = id2;
        }
	}
	if ( param_id != -1 )
	{
		this->m_ObjectNameString += L"%";
		this->m_ObjectNameString += to_wstring ( param_id );
		this->m_ObjectNameString += L"%";
		const auto type = get<1> ( this->m_Parameters [param_id] );
		const auto order = get<2> ( this->m_Parameters [param_id] );
		if (( this->m_Iteration == 0 ) or ( ( type == 0 ) and ( order <= this->m_Iteration ) ))
			return 0;
		else
			return this->m_MessagePool->InactiveParameter ( info );
	}
	else
		return this->m_MessagePool->IncorrectParameter ( info );
}

int scbSchemeManager::Scheme_AddNew ( const scbParseInfo& info )
{
	this->m_CurrentDescriptor.Clear ();
	this->m_Descriptions.emplace_back ();
	if ( this->m_IsWithoutParameter )
		return this->m_MessagePool->DescriptorWithoutParameterMustBeSingle ( info );
	else
		return 0;
}


int scbSchemeManager::Scheme_SetMultiplicator ( const scbParseInfo& info )
{
	const auto mult = this->m_Descriptions.back ().SetMultiplicator ( info.Token );
	if ( mult == -1 )
		return this->m_MessagePool->InvalidMultiplicatorArgument ( info );
	else
	{
		if ( this->m_Multiplicator > 0 )
			return this->m_MessagePool->MultiplicatingDescriptorMustBeSingle ( info );
		else
		{
			this->m_Multiplicator = mult;
			return 0;
		}
	}
}

int scbSchemeManager::Scheme_Descriptor ( const scbParseInfo& info )
{
	this->m_Descriptions.back ().GetDescriptor () = this->m_CurrentDescriptor;
	this->m_CurrentDescriptor.Clear ();
	if ( this->m_Multiplicator > 0 )
		return this->m_MessagePool->MultiplicatingDescriptorMustBeSingle ( info );
	else
	{
		const auto count = this->m_Descriptions.size ();
		if ( this->m_Descriptions.back ().GetDescriptor ().ExtractParamTag () == -1 )
		{
			if ( count == 1 )
				this->m_IsWithoutParameter = true;
			else
				return this->m_MessagePool->DescriptorWithoutParameterMustBeSingle ( info );
		}
		for ( size_t i = 0; i < count - 1; ++i )
		{
			if ( this->m_Descriptions [i].GetDescriptor ().IsEqualForDescription ( this->m_Descriptions.back ().GetDescriptor () ) )
				return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
		}
		return 0;
	}
}

int scbSchemeManager::Scheme_AddNewPlacementName ( const scbParseInfo& info )
{
	this->m_BackupIntVar = this->PlacementNameParameter ( info );
	if ( this->m_BackupIntVar == -1 )
		return this->m_MessagePool->IncorrectRepeatOfParameter ( info );
	else
	{
		if ( this->m_Descriptions.back ().AddNewPlacement ( this->m_BackupIntVar ) != 0 )
			return this->m_MessagePool->IncorrectRepeatOfPlacementName ( info );
		else
			return 0;
	}
}

int scbSchemeManager::Scheme_SetPlacementType ( const scbParseInfo& info )
{
	// Ñíà÷àëà ïðîâåðêà ñîîòâåòñòâèÿ òèïîâ è èìåí âíóòðè ñâîåãî Îïèñàíèÿ...
	const auto [res, id] = this->m_Descriptions.back ().SetPlacementType ( info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectPlacementType ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfPlacementType ( info );
	}
	// ...çàòåì ïðîâåðêà ñîîòâåòñòâèÿ òèïîâ è èìåí ìåæäó âñåìè Îïèñàíèÿìè è òåêóùèì
	const auto count = this->m_Descriptions.size ();
	for ( size_t index = 0; index < count - 1; ++index )
	{
		if ( !( this->m_Descriptions [index].CanExistAnotherPlacement ( this->m_BackupIntVar, id ) ) )
			return this->m_MessagePool->InexactRepeatOfPlacement ( info );
	}
	return 0;
}

int scbSchemeManager::Scheme_AddNewDescriptionGroup ( const scbParseInfo& info )
{
	this->m_Descriptions.back ().AddNewDescriptionGroup ();
	return 0;
}

int scbSchemeManager::Scheme_AddNewDescriptionTag ( const scbParseInfo& info )
{
	int res = 0;
	switch ( this->m_Descriptions.back ().AddNewDescription ( info.Token ))
	{
	case 1:
		res = this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
		break;
	case -1:
		res = this->m_MessagePool->IncorrectDescriptionTag ( info );
		break;
	}
	return res;
}

int scbSchemeManager::Scheme_CheckDescriptionGroup ( const scbParseInfo& info )
{
	if ( this->m_Descriptions.back ().CheckDescriptionGroups () )
		return 0;
	else
		return this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
}

int scbSchemeManager::Scheme_Multiplicate ( const scbParseInfo& info )
{
	if ( this->m_Multiplicator > 0 )
	{
		const auto cbegin = this->m_Parameters.cbegin ();
		const auto cend = this->m_Parameters.cend ();
		auto res = find_if ( cbegin, cend, [] ( const auto& val ) { return ( get<1> ( val ) == 0 ); } );
		const wstring baseName = get<0> ( *res );
		get<0> ( this->m_Parameters [res - cbegin] ) += L"1";
		get<2> ( this->m_Parameters [res - cbegin] ) = 1;
		for ( int counter = 2; counter <= this->m_Multiplicator; ++counter )
		{
			scbParseInfo new_info = info;
			new_info.Token = baseName + to_wstring ( counter );
			this->m_Descriptions.push_back ( this->m_Descriptions.back () );
			this->m_Descriptions.back ().GetDescriptor ().SetSecondTag ( scbManager::ParameterNameShift + this->DescriptorParameter ( new_info, counter ) );
		}
	}
	return 0;
}

int scbSchemeManager::Scheme_AddNewBlockName ( const scbParseInfo& info )
{
	if ( this->m_Multiplicator == 0 )
		return this->m_MessagePool->IncorrectSectionBlockInAloneDescriptor ( info );
	else if ( !( this->m_MultiplicatingBlockName.empty () ) )
		return this->m_MessagePool->TooMuchSectionBlockInDescriptor ( info );
	else
	{
		this->m_MultiplicatingBlockName = info.Token;
		return 0;
	}
}

int scbSchemeManager::Alias_AddAlias ( const scbParseInfo& info )
{
	if ( this->m_Multiplicator > 0 )
		return this->m_MessagePool->MultiplicatingDescriptorCantHaveAnyAliases ( info );
	const auto id = this->AliasParameter ( info );
	if ( id != -1 )
		return 0;
	else
		return this->m_MessagePool->IncorrectRepeatOfParameter ( info );
}

int scbSchemeManager::Alias_PreParamString ( const scbParseInfo& info )
{
	return 0;
}

int scbSchemeManager::Alias_ParamString ( const scbParseInfo& info )
{
	return 0;
}

int scbSchemeManager::Alias_PostParamString ( const scbParseInfo& info )
{
	return 0;
}

int scbSchemeManager::Alias_SortParam ( const scbParseInfo& info )
{
	return 0;
}


int scbSchemeManager::Tuning_AddNew ( const scbParseInfo& info )
{
	this->m_CurrentDescriptor.Clear ();
	this->m_Tunings.emplace_back ();
	return 0;
}

int scbSchemeManager::Tuning_Descriptor ( const scbParseInfo& info )
{
	this->m_Tunings.back ().GetDescriptor () = this->m_CurrentDescriptor;
	this->m_CurrentDescriptor.Clear ();
	if (( this->m_Descriptions.size () == 1 ) or ( this->m_Multiplicator > 0 ) )
		return this->m_MessagePool->IncorrectDescriptorPresence ( info );
	else
	{
		for ( const auto& desc : this->m_Descriptions )
			if ( desc.GetDescriptor ().IsEqual ( this->m_Tunings.back ().GetDescriptor () ) )
				return 0;
	}
	return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::Tuning_CheckDescriptor ( const scbParseInfo& info )
{
	if ((( this->m_Multiplicator == 0 ) and  ( this->m_Descriptions.size () > 1 )) and ( this->m_Tunings.back ().GetDescriptor ().GetType () == scbComplexName::ComplexNameType::Empty ) )
		return this->m_MessagePool->IncorrectDescriptorAbsence ( info );
	else
		return 0;
}

int scbSchemeManager::Tuning_AddNewDescriptionTag ( const scbParseInfo& info )
{
	int res = 0;
	switch ( this->m_Tunings.back ().AddNewDescription ( info.Token ) )
	{
	case 1:
		res = this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
		break;
	case -1:
		res = this->m_MessagePool->IncorrectDescriptionTag ( info );
		break;
	}
	return res;
}

int scbSchemeManager::Tuning_CheckDescriptionAndTuning ( const scbParseInfo& info )
{
	for ( const auto& description : this->m_Descriptions )
	{
		auto [param, tunings] = this->m_Tunings.back ().GetDescriptionTags ();
		if ( this->m_Tunings.back ().GetDescriptor ().IsEqual ( description.GetDescriptor ()) )
		{
			if ( !( description.CheckForTuning ( tunings )))
				return this->m_MessagePool->UnachievableDescriptionCombination ( info );
		}
	}
	const auto count = this->m_Tunings.size () - 1;
	for ( size_t index = 0; index < count; ++index )
	{
		if ( this->m_Tunings [index].IsIdentical ( this->m_Tunings.back () ) )
			return this->m_MessagePool->IncorrectCoincidingDescriptionSets ( info );
	}
	return 0;
}

int scbSchemeManager::ExternalLink_AddNew ( const scbParseInfo& info )
{
	this->m_ExternalLinks.emplace_back ();
	this->m_CurrentDescriptor.Clear ();
	this->m_CurrentConditionParam = -1;
	this->m_StartParseInfo = info;
	if ( this->m_Multiplicator > 0 )
		return this->m_MessagePool->MultiplicatingDescriptorCantHaveAnyExternalLink ( info );
	else if ( this->m_IsWithoutParameter )
		return this->m_MessagePool->CantHaveAnyExternalLinks ( info );
	else
		return 0;
}

int scbSchemeManager::ExternalLink_Descriptor ( const scbParseInfo& info )
{
	for ( const auto& desc : this->m_Descriptions )
		if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
			return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
	const auto count = this->m_ExternalLinks.size () - 1;
	for ( size_t index = 0; index < count; ++index )
		if ( this->m_ExternalLinks [index].GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
			return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
	this->m_ExternalLinks.back ().GetDescriptor () = this->m_CurrentDescriptor;
	this->m_CurrentDescriptor.Clear ();
	return 0;
}

int scbSchemeManager::ExternalLink_Necesserily ( const scbParseInfo& info )
{
	this->m_ExternalLinks.back ().SetNecesserily ();
	return 0;
}

int scbSchemeManager::ExternalLink_DescriptionTag ( const scbParseInfo& info )
{
	auto [res, id] = this->m_ExternalLinks.back ().SetDescriptionTag ( info.Token );
	if ( res != 0 )
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	else
	{
		for ( const auto& description : this->m_Descriptions )
		{
			if ( !( description.CheckForExternalLinkDescription ( id )))
				return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
		}
		for ( const auto& tuning : this->m_Tunings )
		{
			if ( !( tuning.CheckForExternalLinkDescription ( id ) ) )
				return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
		}
		const auto count = this->m_ExternalLinks.size () - 1;
		for ( size_t index = 0; index < count; ++index )
		{
			if ( this->m_ExternalLinks [index].CheckPresenceInConditionsAndDescription ( id ) )
				return this->m_MessagePool->IncorrectDescriptionTag ( info );
		}
		return 0;
	}
}

int scbSchemeManager::ExternalLink_AddConditionGroup ( const scbParseInfo& info )
{
	this->m_ExternalLinks.back ().AddNewConditionGroup ();
	return 0;
}

int scbSchemeManager::ExternalLink_AddCondition ( const scbParseInfo& info )
{
	auto [ res, id ] = this->m_ExternalLinks.back ().AddCondition ( this->m_CurrentConditionParam, info.Token );
	for ( const auto& extLink : this->m_ExternalLinks )
	{
		if ( extLink.GetDescriptionTag () == id )
			return this->m_MessagePool->IncorrectDescriptionTag ( info );
	}
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
	}
	return 0;
}

int scbSchemeManager::ExternalLink_CheckConditionGroup ( const scbParseInfo& info )
{
	int res = 0;
	if ( this->m_ExternalLinks.back ().CheckForEqualConditions () )
		res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
	return max ( this->CheckConditions ( info, this->m_ExternalLinks.back ().GetLastConditions () ), res );
}

int scbSchemeManager::ExternalConnection_AddNew ( const scbParseInfo& info )
{
	this->m_CurrentDescriptor.Clear ();
	this->m_ExternalConnections.emplace_back ();
	if ( this->m_Multiplicator > 0 )
		return this->m_MessagePool->MultiplicatingDescriptorCantHaveAnyConnection ( info );
	else if ( this->m_IsWithoutParameter )
		return this->m_MessagePool->CantHaveAnyExternalConnections ( info );
	else
		return 0;
}

int scbSchemeManager::ExternalConnection_Descriptor ( const scbParseInfo& info )
{
	for ( const auto& desc : this->m_Descriptions )
	{
		if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
		{
			const auto count = this->m_ExternalConnections.size () - 1;
			for ( size_t index = 0; index < count; ++index )
				if ( this->m_ExternalConnections [index].GetDescriptor ().IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			for ( const auto& connection : this->m_InternalConnections )
			{
				if ( connection.GetDescriptor ( 0 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
				if ( connection.GetDescriptor ( 1 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			}
			this->m_ExternalConnections.back ().GetDescriptor () = this->m_CurrentDescriptor;
			this->m_CurrentDescriptor.Clear ();
			return 0;
		}
	}
	return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::ExternalConnection_AddConditionGroup ( const scbParseInfo& info )
{
	this->m_ExternalConnections.back ().AddNewConditionGroup ();
	return 0;
}

int scbSchemeManager::ExternalConnection_AddCondition ( const scbParseInfo& info )
{
	auto [res, id] = this->m_ExternalConnections.back ().AddCondition ( this->m_CurrentConditionParam, info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
	}
	for ( const auto& link : this->m_ExternalLinks )
		if ( link.GetDescriptionTag () == id )
			return this->m_MessagePool->IncorrectRepeatOfDescription ( info );
	return 0;
}

int scbSchemeManager::ExternalConnection_CheckConditionGroup ( const scbParseInfo& info )
{
	int res = 0;
	if ( this->m_ExternalConnections.back ().CheckForEqualConditions () )
		res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
	return max ( this->CheckConditions ( info, this->m_ExternalConnections.back ().GetLastConditions () ), res );
}

int scbSchemeManager::InternalConnection_AddNew ( const scbParseInfo& info )
{
	this->m_CurrentDescriptor.Clear ();
	this->m_InternalConnections.emplace_back ();
	if ( this->m_Multiplicator > 0 )
		return this->m_MessagePool->MultiplicatingDescriptorCantHaveAnyConnection ( info );
	else if ( this->m_Descriptions.size () == 1 )
		return this->m_MessagePool->CantHaveAnyInternalConnections ( info );
	else
		return 0;
}

int scbSchemeManager::InternalConnection_FirstDescriptor ( const scbParseInfo& info )
{
	for ( const auto& desc : this->m_Descriptions )
	{
		if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
		{
			const auto count = this->m_InternalConnections.size () - 1;
			for ( size_t index = 0; index < count; ++index )
			{
				if ( this->m_InternalConnections [index].GetDescriptor ( 0 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
				if ( this->m_InternalConnections [index].GetDescriptor ( 1 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			}
			for ( const auto& connection : this->m_ExternalConnections )
				if ( connection.GetDescriptor ().IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			this->m_InternalConnections.back ().GetDescriptor ( 0 ) = this->m_CurrentDescriptor;
			this->m_CurrentDescriptor.Clear ();
			return 0;
		}
	}
	return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::InternalConnection_SecondDescriptor ( const scbParseInfo& info )
{
	for ( const auto& desc : this->m_Descriptions )
	{
		if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
		{
			if ( this->m_InternalConnections.back ().GetDescriptor ( 0 ).IsEqual ( this->m_CurrentDescriptor ) )
				return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			const auto count = this->m_InternalConnections.size () - 1;
			for ( size_t index = 0; index < count; ++index )
			{
				if ( this->m_InternalConnections [index].GetDescriptor ( 0 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
				if ( this->m_InternalConnections [index].GetDescriptor ( 1 ).IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			}
			for ( const auto& connection : this->m_ExternalConnections )
				if ( connection.GetDescriptor ().IsEqual ( this->m_CurrentDescriptor ) )
					return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
			if ( this->m_InternalConnections.back ().GetDescriptor ( 0 ).IsEqualForDescription ( this->m_CurrentDescriptor ) )
				this->m_MessagePool->UsingInternalConnectionWithSameDescriptor ( info );
			this->m_InternalConnections.back ().GetDescriptor ( 1 ) = this->m_CurrentDescriptor;
			this->m_CurrentDescriptor.Clear ();
			return 0;
		}
	}
	return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::InternalConnection_AddConditionGroup ( const scbParseInfo& info )
{
	this->m_InternalConnections.back ().AddNewConditionGroup ();
	return 0;
}

int scbSchemeManager::InternalConnection_AddCondition ( const scbParseInfo& info )
{
	auto [res, id] = this->m_InternalConnections.back ().AddCondition ( this->m_CurrentConditionParam, info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
	}
	for ( const auto& link : this->m_ExternalLinks )
		if ( link.GetDescriptionTag () == id )
			return this->m_MessagePool->IncorrectRepeatOfDescription ( info );
	return 0;
}

int scbSchemeManager::InternalConnection_CheckConditionGroup ( const scbParseInfo& info )
{
	int res = 0;
	if ( this->m_InternalConnections.back ().CheckForEqualConditions () )
		res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
	return max ( this->CheckConditions ( info, this->m_InternalConnections.back ().GetLastConditions () ), res );
}

int scbSchemeManager::ExtendedBlock_AddNew ( const scbParseInfo& info )
{
	this->m_ExtendedBlocks.emplace_back ();
	if ( this->m_Multiplicator > 1 )
		return this->m_MessagePool->MultiplicatingDescriptorCantHaveAnyExtendedBlock ( info );
	else if ( this->m_IsWithoutParameter )
		return this->m_MessagePool->CantHaveAnyExtendedBlocks ( info );
	else
		return 0;
}

int scbSchemeManager::ExtendedBlock_Name ( const scbParseInfo& info )
{
	const wstring& name = info.Token;
	const auto count = this->m_ExtendedBlocks.size () - 1;
	for ( size_t index = 0; index < count; ++index )
		if ( this->m_ExtendedBlocks [index].GetName () == name )
			return this->m_MessagePool->NameAlwaysUsed ( info );
	this->m_ExtendedBlocks.back ().SetName ( name );
	return 0;
}

int scbSchemeManager::ExtendedBlock_DefaultCount ( const scbParseInfo& info )
{
	if ( this->m_ExtendedBlocks.back ().SetDefaultCount ( info.Token ) == -1 )
		return this->m_MessagePool->InvalidExtendedBlockCountArgument ( info );
	else
		return 0;
}

int scbSchemeManager::ExtendedBlock_AddConditionGroup ( const scbParseInfo& info )
{
	this->m_ExtendedBlocks.back ().AddNewConditionGroup ();
	if ( this->m_ExtendedBlocks.back ().AddNewConditionCount ( info.Token ) == -1 )
		return this->m_MessagePool->InvalidExtendedBlockCountArgument ( info );
	else
		return 0;
}

int scbSchemeManager::ExtendedBlock_AddCondition ( const scbParseInfo& info )
{
	auto [res, id] = this->m_ExtendedBlocks.back ().AddCondition ( this->m_CurrentConditionParam, info.Token );
	if (( this->m_Descriptions.size () > 1 ) and ( this->m_CurrentConditionParam == -1 ))
	{
		bool mark = false;
		for ( const auto& extLink : this->m_ExternalLinks )
		{
			if ( extLink.GetDescriptionTag () == id )
			{
				mark = true;
				break;
			}
		}
		if ( !mark )
			return this->m_MessagePool->ConditionParamIsRequired ( info );
	}
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
	}
	return 0;
}

int scbSchemeManager::ExtendedBlock_CheckConditionGroup ( const scbParseInfo& info )
{
	int res = 0;
	if ( this->m_ExtendedBlocks.back ().CheckForEqualConditions () )
		res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
	return max ( this->CheckConditions ( info, this->m_ExtendedBlocks.back ().GetLastConditions () ), res );
}

int scbSchemeManager::Block_AddNew ( const scbParseInfo& info )
{
	if ( !( this->IsDefinedNameInMainSection ( info.Token ) ))
	{
		this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeBlock ( info.Token  ) ));
		return 0;
	}
	else
		return this->m_MessagePool->NameAlwaysUsed ( info );
}

int scbSchemeManager::Block_SetTypeName ( const scbParseInfo& info )
{
	if ( this->m_Objects.back ()->SetTypeName ( info.Token ) == 0 )
		return 0;
	else
		return this->m_MessagePool->UnknownTypeOfBlock ( info, this->m_Objects.back ()->GetName () );
}

int scbSchemeManager::Block_SetPlacement ( const scbParseInfo& info )
{
	auto [res, id] = this->UsePlacementParameter ( info );
	if ( res == 0 )
	{
		this->m_BackupIntVar = id;
		scbDescription::PlacementType pl_type = scbDescription::PlacementType::No;
		for ( const auto& desc : this->m_Descriptions )
			if ( ( pl_type = desc.GetPlacementType ( id ) ) != scbDescription::PlacementType::No )
				break;
		if ( ( pl_type != scbDescription::PlacementType::No ) and ( this->m_Objects.back ()->SetPlacement ( id, pl_type ) == 0 ))
			return 0;
		else
			return this->m_MessagePool->IncompatiblePlacement ( info );
	}
	else
		return this->m_MessagePool->UndefinedPlacementName ( info );
}

int scbSchemeManager::Block_SetLocation ( const scbParseInfo& info )
{
	const auto count = this->m_Objects.size () - 1;
	for ( size_t index = 0; index < count; ++index )
		if ( this->m_Objects [index]->CheckLocation ( -1, this->m_BackupIntVar, info.Token ) )
			return this->m_MessagePool->LocationStillOccupied ( info );
	if ( this->m_Objects.back ()->SetLocation ( info.Token ) == 0 )
		return 0;
	else
		return this->m_MessagePool->DeviceCantOccupyTheLocation ( info );
}

int scbSchemeManager::Block_AddObjectName ( const scbParseInfo& info )
{
	this->m_Objects.back ()->AddNewObjectName ( this->m_CurrentString );
	this->m_CurrentString.clear ();
	return 0;
}

int scbSchemeManager::Block_FixMultipleNames ( const scbParseInfo& info )
{
	const auto namesCount = this->m_Objects.back ()->GetObjectNamesCount ();
	const auto descCount = this->m_Descriptions.size ();
	if ( this->m_Multiplicator < 2 )
	{
		if ( namesCount == 1 )
			return 0;
		else
			return this->m_MessagePool->SimpleDescriptorCantHaveAlternativeNames ( info );
	}
	else
	{
		if (( namesCount == descCount ) or ( namesCount == 1 ))
			return 0;
		else
			return this->m_MessagePool->IncorrectCountOfAlternativeNames ( info );
	}
}

int scbSchemeManager::Block_FixSingleName ( const scbParseInfo& info )
{
	return 0;
}

int scbSchemeManager::Relay_AddNew ( const scbParseInfo& info )
{
	if ( !( this->IsDefinedNameInMainSection ( info.Token ) ) )
	{
		this->m_MainName = info.Token;
		return 0;
	}
	else
		return this->m_MessagePool->NameAlwaysUsed ( info );
}

int scbSchemeManager::Relay_SetTypeName ( const scbParseInfo& info )
{
	scbSchemeObject* pObject = nullptr;
	bool incorrectType = false;
    const wstring& type = info.Token;

	if ( type == L"ÍÌØ1-400" )
		pObject = new scbRelay_NMSH1_400 ( this->m_MainName, true );
	else if ( type == L"ÍÌ1-400" )
		pObject = new scbRelay_NMSH1_400 ( this->m_MainName, false );
	else if ( type == L"ÍÌØ1-1440" )
		pObject = new scbRelay_NMSH1_1440 ( this->m_MainName, true );
	else if ( type == L"ÍÌ1-1440" )
		pObject = new scbRelay_NMSH1_1440 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ1-11" )
		pObject = new scbRelay_NMSHM1_11 ( this->m_MainName, true );
	else if ( type == L"ÍÌÌ1-11" )
		pObject = new scbRelay_NMSHM1_11 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ1-560" )
		pObject = new scbRelay_NMSHM1_560 ( this->m_MainName, true );
	else if ( type == L"ÍÌÌ1-560" )
		pObject = new scbRelay_NMSHM1_560 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ1-1120" )
		pObject = new scbRelay_NMSHM1_1120 ( this->m_MainName, true );
	else if ( type == L"ÍÌÌ1-1120" )
		pObject = new scbRelay_NMSHM1_1120 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ1-1000/560" )
		pObject = new scbRelay_NMSHM1_1000_560 ( this->m_MainName, true );
	else if ( type == L"ÍÌÌ1-1000/560" )
		pObject = new scbRelay_NMSHM1_1000_560 ( this->m_MainName, false );

	else if ( type == L"ÍÌØ2-4000" )
		pObject = new scbRelay_NMSH2_4000 ( this->m_MainName, true );
	else if ( type == L"ÍÌ2-4000" )
		pObject = new scbRelay_NMSH2_4000 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ2-1.5" )
		pObject = new scbRelay_NMSHM2_1_5 ( this->m_MainName, true );
	else if ( type == L"ÍÌÌ2-1.5" )
		pObject = new scbRelay_NMSHM2_1_5 ( this->m_MainName, false );
	else if ( type == L"ÍÌØÌ2-1500" )
		pObject = new scbRelay_NMSHM2_1500 ( this->m_MainName );
	else if ( type == L"ÍÌØÌ2-3000" )
		pObject = new scbRelay_NMSHM2_3000 ( this->m_MainName );

	else if ( type == L"ÍÌØ3-460/400" )
		pObject = new scbRelay_NMSH3_460_400 ( this->m_MainName );

	else if ( type == L"ÍÌØ4-2400" )
		pObject = new scbRelay_NMSH4_2400 ( this->m_MainName, true );
	else if ( type == L"ÍÌ4-2400" )
		pObject = new scbRelay_NMSH4_2400 ( this->m_MainName, false );
	else if ( type == L"ÍÌØ4-3" )
		pObject = new scbRelay_NMSH4_3 ( this->m_MainName, true );
	else if ( type == L"ÍÌ4-3" )
		pObject = new scbRelay_NMSH4_3 ( this->m_MainName, false );

	else if ( type == L"ÎÌØ2-46" )
		pObject = new scbRelay_OMSH2_46 ( this->m_MainName, true );
	else if ( type == L"ÎÌ2-46" )
		pObject = new scbRelay_OMSH2_46 ( this->m_MainName, false );

	else if ( type == L"ÀÍÂØ2-2400" )
		pObject = new scbRelay_ANVSH2_2400 ( this->m_MainName );

	else if ( type == L"ÍÌÏØ2-400" )
		pObject = new scbRelay_NMPSH2_400 ( this->m_MainName );
	else if ( type == L"ÍÌÏØ-900" )
		pObject = new scbRelay_NMPSH_900 ( this->m_MainName );
	else if ( type == L"ÍÌÏØ3Ì-0.2/250" )
		pObject = new scbRelay_NMPSH3M_02_250 ( this->m_MainName, true );
	else if ( type == L"ÍÌÏ3Ì-0.2/250" )
		pObject = new scbRelay_NMPSH3M_02_250 ( this->m_MainName, false );

	else if ( type == L"ÏÌÏÓØ-150/150" )
		pObject = new scbRelay_PMPUSH_150_150 ( this->m_MainName, true );
	else if ( type == L"ÏÌÏÓ-150/150" )
		pObject = new scbRelay_PMPUSH_150_150 ( this->m_MainName, false );

	else if ( type == L"ÊÌØ-450" )
		pObject = new scbRelay_KMSH_450 ( this->m_MainName, true );
	else if ( type == L"ÊÌ-450" )
		pObject = new scbRelay_KMSH_450 ( this->m_MainName, false );
	else if ( type == L"ÊÌØ-750" )
		pObject = new scbRelay_KMSH_750 ( this->m_MainName );
	else if ( type == L"ÊÌØ-3000" )
		pObject = new scbRelay_KMSH_3000 ( this->m_MainName, true );
	else if ( type == L"ÊÌ-3000" )
		pObject = new scbRelay_KMSH_3000 ( this->m_MainName, false );

	else if ( type == L"ÄÑØ-13À" )
		pObject = new scbRelay_DSSH13A ( this->m_MainName );

	else if ( type == L"ÏÏÐ3-5000" )
		pObject = new scbRelay_PPR3_5000 ( this->m_MainName );

	else if ( type == L"ÊÄÐ1-200" )
		pObject = new scbRelay_KDR1_200 ( this->m_MainName );
	else if ( type == L"ÊÄÐ1-280" )
		pObject = new scbRelay_KDR1_280 ( this->m_MainName );
	else if ( type == L"ÊÄÐ1Ì-3.8" )
		pObject = new scbRelay_KDR1M_3_8 ( this->m_MainName );
	else if ( type == L"ÊÄÐ1Ì-120" )
		pObject = new scbRelay_KDR1M_120 ( this->m_MainName );
	else if ( type == L"ÊÄÐ1Ì-280" )
		pObject = new scbRelay_KDR1M_280 ( this->m_MainName );
	else if ( type == L"ÊÄÐ1Ì-435" )
		pObject = new scbRelay_KDR1M_435 ( this->m_MainName );

	else
	{
		incorrectType = true;
		pObject = new scbSchemeIncorrectRelay ( this->m_MainName );
	}

	this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( pObject ) );
	if ( incorrectType )
		return this->m_MessagePool->UnknownTypeOfRelay ( this->m_MainName, type, info );
    else
    	return 0;
}

int scbSchemeManager::Relay_SetBlock ( const scbParseInfo& info )
{
	const auto id = this->GetBlockIdByName ( info.Token );
	if ( id == -1 )
		return this->m_MessagePool->UndefinedPlacementName ( info );
	else
	{
		this->m_BackupIntVar = -id - 1;
		if ( this->m_Objects.back ()->SetBlock ( id ) == 0 )
			return 0;
		else
			return this->m_MessagePool->IncompatiblePlacement ( info );
	}
}

int scbSchemeManager::Relay_SetPlacement ( const scbParseInfo& info )
{
	const auto [res, id] = this->UsePlacementParameter ( info );
	if ( res == 0 )
	{
		this->m_BackupIntVar = id;
		scbDescription::PlacementType pl_type = scbDescription::PlacementType::No;
		for ( const auto& desc : this->m_Descriptions )
			if ( ( pl_type = desc.GetPlacementType ( id ) ) != scbDescription::PlacementType::No )
				break;
		if ( ( pl_type != scbDescription::PlacementType::No ) and ( this->m_Objects.back ()->SetPlacement ( id, pl_type ) == 0 ) )
			return 0;
		else
			return this->m_MessagePool->IncompatiblePlacement ( info );
	}
	else
		return this->m_MessagePool->UndefinedPlacementName ( info );
}

int scbSchemeManager::Relay_SetLocation ( const scbParseInfo& info )
{
	const auto count = this->m_Objects.size () - 1;
	const auto block = ( this->m_BackupIntVar < 0 ) ? -this->m_BackupIntVar - 1 : -1;
	const auto placement = ( this->m_BackupIntVar >= 0 ) ? this->m_BackupIntVar : -1;
	for ( size_t index = 0; index < count; ++index )
		if ( this->m_Objects [index]->CheckLocation ( block, placement, info.Token ) )
			return this->m_MessagePool->LocationStillOccupied ( info );
	if ( this->m_Objects.back ()->SetLocation ( info.Token ) == 0 )
		return 0;
	else
		return this->m_MessagePool->DeviceCantOccupyTheLocation ( info );
}

int scbSchemeManager::Relay_AddObjectName ( const scbParseInfo& info )
{
	this->m_Objects.back ()->AddNewObjectName ( this->m_CurrentString );
	this->m_CurrentString.clear ();
	return 0;
}

int scbSchemeManager::Relay_AddJumper ( const scbParseInfo& info )
{
	switch ( this->m_Objects.back ()->SetJumper ( info.Token ) )
	{
	case -1:
		return this->m_MessagePool->DeviceCantHaveAnyJumper ( info, this->m_Objects.back ()->GetTypeName () );
	case 1:
		return this->m_MessagePool->DeviceCantHaveThisJumper ( info, this->m_Objects.back ()->GetTypeName () );
    case 2:
        return this->m_MessagePool->IncorrectRepeatOfJumper ( info );
	}
	return 0;
}

int scbSchemeManager::Relay_AddCondition ( const scbParseInfo& info )
{
	auto [res, id] = this->m_Objects.back ()->AddCondition ( this->m_CurrentConditionParam, info.Token );
	switch ( res )
	{
	case -1:
		return this->m_MessagePool->IncorrectDescriptionTag ( info );
	case 1:
		return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
	}
	if ( this->m_CurrentConditionParam == -1 )
	{
		for ( const auto& extLink : this->m_ExternalLinks )
			if ( extLink.GetDescriptionTag () == id )
				return 0;
		if ( this->m_Descriptions.size () > 1 )
			return this->m_MessagePool->ConditionParamIsRequired ( info );
	}
	return 0;
}

int scbSchemeManager::Relay_AddConditionGroup ( const scbParseInfo& info )
{
	this->m_Objects.back ()->AddNewConditionGroup ();
	return 0;
}

int scbSchemeManager::Relay_CheckConditionGroup ( const scbParseInfo& info )
{
	int res = 0;
	if ( this->m_Objects.back ()->CheckForEqualConditions () )
		res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
	return max ( this->CheckConditions ( info, this->m_Objects.back ()->GetLastConditions () ), res );
}

int scbSchemeManager::Relay_SetRequirement ( const scbParseInfo& info )
{
    if ( this->m_Objects.back ()->SetRequirement ( this->m_ReqId ) == -1 )
        return this->m_MessagePool->RelayCantUseToCoverAnyRequirement ( info, this->m_Objects.back ()->GetTypeName () );
    scbDescription::PlacementType pl_type = scbDescription::PlacementType::No;
    for ( const auto& desc : this->m_Descriptions )
        if ( ( pl_type = desc.GetPlacementType ( this->m_ObjectPlacement ) ) != scbDescription::PlacementType::No )
            break;
    if ( ( pl_type != scbDescription::PlacementType::No ) and ( this->m_Objects.back ()->SetPlacement ( this->m_ObjectPlacement, pl_type ) == 0 ) )
        return 0;
    else
    {
        scbParseInfo new_info = info;
        new_info.Token = get<0> ( this->m_Parameters [this->m_ObjectPlacement] );
        return this->m_MessagePool->IncompatiblePlacement ( new_info );
    }
}

int scbSchemeManager::Relay_SetRequirementFrom ( const scbParseInfo& info )
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi ( info.Token, &pos );
		if (( pos < info.Token.length () ) or ( res < 0 ))
			res = -1;
	}
	catch ( std::invalid_argument )
	{
		res = -1;
	}
	if ( res == -1 )
		return this->m_MessagePool->NumberExcepted ( info );
	else if ( ( res < 0 ) or ( res > 100 ) )
		return this->m_MessagePool->NumberIsOutOfRange ( info );
    this->m_BackupIntVar = res;
    this->m_Objects.back ()->SetRequirementTo ( res );
    return 0;
}

int scbSchemeManager::Relay_SetRequirementTo ( const scbParseInfo& info )
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi ( info.Token, &pos );
		if ( ( pos < info.Token.length () ) or ( res < 0 ) )
			res = -1;
	}
	catch ( std::invalid_argument )
	{
		res = -1;
	}
	if ( res == -1 )
		return this->m_MessagePool->NumberExcepted ( info );
	else if ( ( res < 0 ) or ( res > 100 ) )
		return this->m_MessagePool->NumberIsOutOfRange ( info );
    for ( int index = this->m_BackupIntVar; index <= res; ++index )
        this->m_RequirementMask [index] = 1;
    this->m_GrantingRequirements [this->m_ReqId].SetMaxRequesting ( res );
    res = this->m_Objects.back ()->SetRequirementTo ( res );
    if ( res == 1 )
        return this->m_MessagePool->RequirementFromIsGreaterThanTo ( info );
    else
        return 0;
}

int scbSchemeManager::Relay_FixDescription ( const scbParseInfo& info )
{
	switch ( this->m_Objects.back ()->FixDescription () )
	{
	case 1:
		return this->m_MessagePool->DeviceHasIncompleteSetOfJumpers ( info );
	case 2:
		return this->m_MessagePool->DeviceHasIncompatibleSetOfJumpers ( info );
	}
	return 0;
}

int scbSchemeManager::Relay_RequirementName ( const scbParseInfo& info )
{
    bool mark = false;
    for ( const auto& req : this->m_GrantingRequirements )
    {
        if ( req.GetName () == info.Token )
        {
            mark = true;
            break;
        }
    }
    this->m_GrantingRequirements.emplace_back ( info.Token );
    this->m_ReqId = this->m_GrantingRequirements.size () - 1;
    this->m_RequirementMask.clear ();
    this->m_RequirementMask.resize ( 101, 0 );
    if ( mark )
        return this->m_MessagePool->NameAlwaysUsed ( info );
    else if ( scbDescription::GetDescriptionIdByName ( info.Token ) != -1 )
        return this->m_MessagePool->RequirementNameMustBeNonDescriptionName ( info );
    else
        return 0;
}

int scbSchemeManager::Relay_RequirementPlacement ( const scbParseInfo& info )
{
    auto [ res, id ] = this->UsePlacementParameter ( info );
    this->m_ObjectPlacement = id;
    if ( res == 0 )
        return 0;
    else
        return this->m_MessagePool->UndefinedPlacementName ( info );
}

int scbSchemeManager::Relay_FixRequirement ( const scbParseInfo& info )
{
    int status = 0;
    const auto count = this->m_RequirementMask.size ();
    for ( size_t index = 1; index < count; ++index )
    {
        if ( ( this->m_RequirementMask [index] == 1 ) and ( status == 2 ) )
            return this->m_MessagePool->RequirementDoesntCoverWholeRange ( info );
        if ( ( this->m_RequirementMask [index] == 0 ) and ( status == 1 ) )
            status = 2;
        if ( ( this->m_RequirementMask [index] == 1 ) and ( status == 0 ) )
            status = 1;
    }
    return 0;
}

int scbSchemeManager::Status_AddNew ( const scbParseInfo& info )
{
    if ( this->IsDefinedNameInMainSection ( info.Token ) )
        return this->m_MessagePool->NameAlwaysUsed ( info );
    else
    {
        this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeStatus ( info.Token ) ) );
        return 0;
    }
}

int scbSchemeManager::Status_SetDefaultOne ( const scbParseInfo& info )
{
    this->m_Objects.back ()->DefaultSettingStatus ();
    return 0;
}

int scbSchemeManager::Variable_AddNew ( const scbParseInfo& info )
{
    if ( this->IsDefinedNameInMainSection ( info.Token ) )
        return this->m_MessagePool->NameAlwaysUsed ( info );
    else
    {
        this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeVariable ( info.Token ) ) );
        return 0;
    }
}

int scbSchemeManager::Line_AddNew ( const scbParseInfo& info )
{
    this->m_CurrentDescriptor.Clear ();
    if ( this->IsDefinedNameInMainSection ( info.Token ) )
        return this->m_MessagePool->NameAlwaysUsed ( info );
    else
    {
        this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeLine ( info.Token ) ) );
        return 0;
    }
}

int scbSchemeManager::Line_Descriptor ( const scbParseInfo& info )
{
    this->m_Objects.back ()->SetDescriptor ( this->m_CurrentDescriptor );
    return 0;
}

int scbSchemeManager::Line_AddCondition ( const scbParseInfo& info )
{
    auto [res, id] = this->m_Objects.back ()->AddCondition ( this->m_CurrentConditionParam, info.Token );
    switch ( res )
    {
    case -1:
        return this->m_MessagePool->IncorrectDescriptionTag ( info );
    case 1:
        return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
    }
    if ( this->m_CurrentConditionParam == -1 )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
            if ( extLink.GetDescriptionTag () == id )
                return 0;
        if ( this->m_Descriptions.size () > 1 )
            return this->m_MessagePool->ConditionParamIsRequired ( info );
    }
    return 0;
}

int scbSchemeManager::Line_AddConditionGroup ( const scbParseInfo& info )
{
    this->m_Objects.back ()->AddNewConditionGroup ();
    return 0;
}

int scbSchemeManager::Line_CheckConditionGroup ( const scbParseInfo& info )
{
    int res = 0;
    if ( this->m_Objects.back ()->CheckForEqualConditions () )
        res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
    return max ( this->CheckConditions ( info, this->m_Objects.back ()->GetLastConditions () ), res );
}

int scbSchemeManager::Cross_Placement ( const scbParseInfo& info )
{
    const auto [res, id] = this->UsePlacementParameter ( info );
    if ( res == 0 )
    {
        this->m_ObjectPlacement = id;
        this->m_ObjectLocation.clear ();
        this->m_ObjectCable.clear ();
        this->m_ObjectOrder = -1;
        return 0;
    }
    else
        return this->m_MessagePool->UndefinedPlacementName ( info );
}

int scbSchemeManager::Cross_Location ( const scbParseInfo& info )
{
    this->m_ObjectLocation = info.Token;
    return 0;
}

int scbSchemeManager::Cross_Order ( const scbParseInfo& info )
{
    size_t pos = 0;
    int res = 0;
    try
    {
        res = std::stoi ( info.Token, &pos );
        if ( ( pos < info.Token.length () ) or ( res < 0 ) )
            res = -1;
    }
    catch ( std::invalid_argument )
    {
        res = -1;
    }
    if ( res == -1 )
        return this->m_MessagePool->NumberExcepted ( info );
    else
    {
        this->m_ObjectOrder = res;
        return 0;
    }
}

int scbSchemeManager::Cross_Cable ( const scbParseInfo& info )
{
    this->m_ObjectCable = info.Token;
    return 0;
}

int scbSchemeManager::Cross_GeneralName ( const scbParseInfo& info )
{
    this->m_ObjectGeneralNameString = this->m_ObjectNameString;
    return 0;
}

int scbSchemeManager::Cross_AddNew ( const scbParseInfo& info )
{
    this->m_CurrentDescriptor.Clear ();
    if ( this->IsDefinedNameInMainSection ( info.Token ) )
        return this->m_MessagePool->NameAlwaysUsed ( info );
    else
    {
        this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeCross ( info.Token ) ) );

        // Çàäàåì ðàçìåùåíèå
        scbDescription::PlacementType pl_type = scbDescription::PlacementType::No;
        for ( const auto& desc : this->m_Descriptions )
            if ( ( pl_type = desc.GetPlacementType ( this->m_ObjectPlacement ) ) != scbDescription::PlacementType::No )
                break;
        if ( ( pl_type != scbDescription::PlacementType::No ) and ( this->m_Objects.back ()->SetPlacement ( this->m_ObjectPlacement, pl_type ) == 0 ) )
        {
            // Çàäàåì ìåñòî â ðàçìåùåíèè
            if ( this->m_Objects.back ()->SetLocation ( this->m_ObjectLocation ) == 0 )
            {
                // Çàäàåì êàáåëü è ïîðÿäîê
                this->m_Objects.back ()->SetCable ( this->m_ObjectCable );
                this->m_Objects.back ()->SetOrder ( this->m_ObjectOrder );
                return 0;
            }
            else
                return this->m_MessagePool->DeviceCantOccupyTheLocation ( info );
        }
        else
            return this->m_MessagePool->IncompatiblePlacement ( info );
    }
}

int scbSchemeManager::Cross_Name ( const scbParseInfo& info )
{
    wstring name = this->m_ObjectGeneralNameString + this->m_ObjectNameString;
    this->m_Objects.back ()->AddNewObjectName ( name );
    return 0;
}

int scbSchemeManager::Cross_AddContact ( const scbParseInfo& info )
{
    switch ( this->m_Objects.back ()->SetContact ( info.Token ) )
    {
    case -1:
        return this->m_MessagePool->DeviceCantHaveThisContact ( info );
    case 1:
        return this->m_MessagePool->IncorrectRepeatOfContact ( info );
    }
    return 0;
}

int scbSchemeManager::Cross_Count ( const scbParseInfo& info )
{
    size_t pos = 0;
    int res = 0;
    try
    {
        res = std::stoi ( info.Token, &pos );
        if ( ( pos < info.Token.length () ) or ( res <= 0 ) )
            res = -1;
    }
    catch ( std::invalid_argument )
    {
        res = -1;
    }
    if ( res == -1 )
        return this->m_MessagePool->NumberExcepted ( info );
    else
    {
        this->m_Objects.back ()->SetCount ( res );
        return 0;
    }
}

int scbSchemeManager::Cross_AddCondition ( const scbParseInfo& info )
{
    auto [res, id] = this->m_Objects.back ()->AddCondition ( this->m_CurrentConditionParam, info.Token );
    switch ( res )
    {
    case -1:
        return this->m_MessagePool->IncorrectDescriptionTag ( info );
    case 1:
        return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
    }
    if ( this->m_CurrentConditionParam == -1 )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
            if ( extLink.GetDescriptionTag () == id )
                return 0;
        if ( this->m_Descriptions.size () > 1 )
            return this->m_MessagePool->ConditionParamIsRequired ( info );
    }
    return 0;
}

int scbSchemeManager::Cross_AddConditionGroup ( const scbParseInfo& info )
{
    this->m_Objects.back ()->AddNewConditionGroup ();
    return 0;
}

int scbSchemeManager::Cross_CheckConditionGroup ( const scbParseInfo& info )
{
    int res = 0;
    if ( this->m_Objects.back ()->CheckForEqualConditions () )
        res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
    return max ( this->CheckConditions ( info, this->m_Objects.back ()->GetLastConditions () ), res );
}

int scbSchemeManager::Equipment_AddNew ( const scbParseInfo& info )
{
    if ( !( this->IsDefinedNameInMainSection ( info.Token ) ) )
    {
        this->m_MainName = info.Token;
        return 0;
    }
    else
        return this->m_MessagePool->NameAlwaysUsed ( info );
}

int scbSchemeManager::Equipment_SetType ( const scbParseInfo& info )
{
    scbSchemeObject* pObject = nullptr;
    bool incorrectType = false;
    const wstring& type = info.Token;
    
    if ( type == L"Ïðåäîõðàíèòåëü" )
        pObject = new scbSchemeFuse ( this->m_MainName );

    else if ( type == L"ÊÝÃ-1-30Â" )
        pObject = new scbSchemeCapacitor ( this->m_MainName, scbSchemeCapacitor::Type::KEG_1_30V );
    else if ( type == L"ÊÝÃ-2-30Â" )
        pObject = new scbSchemeCapacitor ( this->m_MainName, scbSchemeCapacitor::Type::KEG_2_30V );
    else if ( type == L"ÌÁÃ×-1-1-250Â" )
        pObject = new scbSchemeCapacitor ( this->m_MainName, scbSchemeCapacitor::Type::MBGCH_1_1_250V );
    else if ( type == L"ÌÁÃ×-1-2À-250Â" )
        pObject = new scbSchemeCapacitor ( this->m_MainName, scbSchemeCapacitor::Type::MBGCH_1_2A_250V );
    else if ( type == L"ÝÃÖ-30Â" )
        pObject = new scbSchemeCapacitor ( this->m_MainName, scbSchemeCapacitor::Type::EGC_30V );

    else if ( type == L"Ðåîñòàò" )
        pObject = new scbSchemeRheostat ( this->m_MainName );

    else if ( type == L"ÌËÒ-1" )
        pObject = new scbSchemeResistor ( this->m_MainName, scbSchemeResistor::Type::MLT_1 );
    else if ( type == L"ÌËÒ-2" )
        pObject = new scbSchemeResistor ( this->m_MainName, scbSchemeResistor::Type::MLT_2 );
    else if ( type == L"ÏÝÂ-25" )
        pObject = new scbSchemeResistor ( this->m_MainName, scbSchemeResistor::Type::PEV_25 );
    else if ( type == L"ÏÝÂ-50" )
        pObject = new scbSchemeResistor ( this->m_MainName, scbSchemeResistor::Type::PEV_50 );

    else if ( type == L"Ä226Á" )
        pObject = new scbSchemeDiode ( this->m_MainName, scbSchemeDiode::Type::D226B );

    else if ( type == L"ÁÂÌØ" )
        pObject = new scbSchemeTimeBlock ( this->m_MainName, scbSchemeTimeBlock::Type::BVMSH );
    else if ( type == L"ÁÂÂ-Ì" )
        pObject = new scbSchemeTimeBlock ( this->m_MainName, scbSchemeTimeBlock::Type::BVV_M );
    else if ( type == L"ÁÂÂ-Ö" )
        pObject = new scbSchemeTimeBlock ( this->m_MainName, scbSchemeTimeBlock::Type::BVV_C );

    else if ( type == L"Èçìåðèòåëüíàÿïàíåëü" )
        pObject = new scbSchemeMeasuringPanel ( this->m_MainName );

    else if ( type == L"ÑÒ-4À" )
        pObject = new scbSchemeTransformer_ST4 ( this->m_MainName, scbSchemeTransformer_ST4::Type::ST4A );
    else if ( type == L"ÑÒ-4Ì" )
        pObject = new scbSchemeTransformer_ST4 ( this->m_MainName, scbSchemeTransformer_ST4::Type::ST4M );
    else if ( type == L"ÑÒ-4ÌÏ" )
        pObject = new scbSchemeTransformer_ST4 ( this->m_MainName, scbSchemeTransformer_ST4::Type::ST4MP );
    else if ( type == L"ÑÒ-4Ã" )
        pObject = new scbSchemeTransformer_ST4 ( this->m_MainName, scbSchemeTransformer_ST4::Type::ST4G );

    else if ( type == L"ÑÒ-5À" )
        pObject = new scbSchemeTransformer_ST5 ( this->m_MainName, scbSchemeTransformer_ST5::Type::ST5A );
    else if ( type == L"ÑÒ-5Ì" )
        pObject = new scbSchemeTransformer_ST5 ( this->m_MainName, scbSchemeTransformer_ST5::Type::ST5M );
    else if ( type == L"ÑÒ-5ÌÏ" )
        pObject = new scbSchemeTransformer_ST5 ( this->m_MainName, scbSchemeTransformer_ST5::Type::ST5MP );
    else if ( type == L"ÑÒ-5Ã" )
        pObject = new scbSchemeTransformer_ST5 ( this->m_MainName, scbSchemeTransformer_ST5::Type::ST5G );

    else if ( type == L"ÑÊÒ-1" )
        pObject = new scbSchemeTransformer_SKT ( this->m_MainName );

    else
    {
        incorrectType = true;
        pObject = new scbSchemeIncorrectRelay ( this->m_MainName );
    }

    this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( pObject ) );
    if ( incorrectType )
        return this->m_MessagePool->UnknownTypeOfEquipment ( this->m_MainName, type, info );
    else
        return 0;
}

int scbSchemeManager::Equipment_SetNominal ( const scbParseInfo& info )
{
    switch ( this->m_Objects.back ()->SetNominal ( info.Token ) )
    {
    case -1:
        return this->m_MessagePool->DeviceCantHaveNominal ( info, this->m_Objects.back ()->GetTypeName () );
    case 1:
        return this->m_MessagePool->NumberExcepted ( info );
    }
    return 0;
}

int scbSchemeManager::Equipment_SetUnit ( const scbParseInfo& info )
{
    if ( this->m_Objects.back ()->SetUnitOfNominal ( info.Token ) == 0 )
        return 0;
    else
        return this->m_MessagePool->DeviceCantHaveThisUnit ( info, this->m_Objects.back ()->GetTypeName () );
}

int scbSchemeManager::Equipment_SetPowerClass ( const scbParseInfo& info )
{
    switch ( this->m_Objects.back ()->SetPowerClass ( info.Token ) )
    {
    case 1:
        return this->m_MessagePool->IncorrectPowerClass ( info );
    case -1:
        return this->m_MessagePool->DeviceCantHavePowerClass ( info, this->m_Objects.back ()->GetTypeName () );
    }
    return 0;
}

int scbSchemeManager::Equipment_SetPlacement ( const scbParseInfo& info )
{
    const auto [res, id] = this->UsePlacementParameter ( info );
    if ( res == 0 )
    {
        this->m_BackupIntVar = id;
        scbDescription::PlacementType pl_type = scbDescription::PlacementType::No;
        for ( const auto& desc : this->m_Descriptions )
            if ( ( pl_type = desc.GetPlacementType ( id ) ) != scbDescription::PlacementType::No )
                break;
        if ( ( pl_type != scbDescription::PlacementType::No ) and ( this->m_Objects.back ()->SetPlacement ( id, pl_type ) == 0 ) )
            return 0;
        else
            return this->m_MessagePool->IncompatiblePlacement ( info );
    }
    else
        return this->m_MessagePool->UndefinedPlacementName ( info );
}

int scbSchemeManager::Equipment_SetBlock ( const scbParseInfo& info )
{
    const auto id = this->GetBlockIdByName ( info.Token );
    if ( id == -1 )
        return this->m_MessagePool->UndefinedPlacementName ( info );
    else
    {
        this->m_BackupIntVar = -id - 1;
        if ( this->m_Objects.back ()->SetBlock ( id ) == 0 )
            return 0;
        else
            return this->m_MessagePool->IncompatiblePlacement ( info );
    }
}

int scbSchemeManager::Equipment_SetLocation ( const scbParseInfo& info )
{
    const auto count = this->m_Objects.size () - 1;
    const auto block = ( this->m_BackupIntVar < 0 ) ? -this->m_BackupIntVar - 1 : -1;
    const auto placement = ( this->m_BackupIntVar >= 0 ) ? this->m_BackupIntVar : -1;
    for ( size_t index = 0; index < count; ++index )
        if ( this->m_Objects [index]->CheckLocation ( block, placement, info.Token ) )
            return this->m_MessagePool->LocationStillOccupied ( info );
    if ( this->m_Objects.back ()->SetLocation ( info.Token ) == 0 )
        return 0;
    else
        return this->m_MessagePool->DeviceCantOccupyTheLocation ( info );
}

int scbSchemeManager::Equipment_AddObjectName ( const scbParseInfo& info )
{
    this->m_Objects.back ()->AddNewObjectName ( this->m_CurrentString );
    this->m_CurrentString.clear ();
    return 0;
}

int scbSchemeManager::Equipment_AddJumper ( const scbParseInfo& info )
{
    switch ( this->m_Objects.back ()->SetJumper ( info.Token ) )
    {
    case -1:
        return this->m_MessagePool->DeviceCantHaveAnyJumper ( info, this->m_Objects.back ()->GetTypeName () );
    case 1:
        return this->m_MessagePool->DeviceCantHaveThisJumper ( info, this->m_Objects.back ()->GetTypeName () );
    case 2:
        return this->m_MessagePool->IncorrectRepeatOfJumper ( info );
    }
    return 0;
}

int scbSchemeManager::Equipment_AddCondition ( const scbParseInfo& info )
{
    auto [res, id] = this->m_Objects.back ()->AddCondition ( this->m_CurrentConditionParam, info.Token );
    switch ( res )
    {
    case -1:
        return this->m_MessagePool->IncorrectDescriptionTag ( info );
    case 1:
        return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
    }
    if ( this->m_CurrentConditionParam == -1 )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
            if ( extLink.GetDescriptionTag () == id )
                return 0;
        if ( this->m_Descriptions.size () > 1 )
            return this->m_MessagePool->ConditionParamIsRequired ( info );
    }
    return 0;
}

int scbSchemeManager::Equipment_AddConditionGroup ( const scbParseInfo& info )
{
    this->m_Objects.back ()->AddNewConditionGroup ();
    return 0;
}

int scbSchemeManager::Equipment_CheckConditionGroup ( const scbParseInfo& info )
{
    int res = 0;
    if ( this->m_Objects.back ()->CheckForEqualConditions () )
        res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
    return max ( this->CheckConditions ( info, this->m_Objects.back ()->GetLastConditions () ), res );
}

int scbSchemeManager::Equipment_FixDescription ( const scbParseInfo& info )
{
    switch ( this->m_Objects.back ()->FixDescription () )
    {
    case 1:
        return this->m_MessagePool->DeviceHasIncompleteSetOfJumpers ( info );
    case 2:
        return this->m_MessagePool->DeviceHasIncompatibleSetOfJumpers ( info );
    case 3:
        return this->m_MessagePool->DeviceMustHaveNominal ( info, this->m_Objects.back ()->GetTypeName () );
    case 4:
        return this->m_MessagePool->DeviceMustHavePowerClass ( info, this->m_Objects.back ()->GetTypeName () );
    case 5:
        return this->m_MessagePool->DeviceMustHaveObjectName ( info, this->m_Objects.back ()->GetTypeName () );
    }
    return 0;
}

int scbSchemeManager::Event_Descriptor ( const scbParseInfo& info )
{
    this->m_Events.emplace_back ();
    for ( const auto& desc : this->m_Descriptions )
    {
        if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            const auto count = this->m_Events.size () - 1;
            for ( size_t index = 0; index < count; ++index )
            {
                if ( this->m_Events [index].GetDescriptor ().IsFullyEqual ( this->m_CurrentDescriptor ) )
                {
                    this->m_CurrentDescriptor.Clear ();
                    return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
                }
            }
            this->m_Events.back ().GetDescriptor () = this->m_CurrentDescriptor;
            this->m_CurrentDescriptor.Clear ();
            return 0;
        }
    }
    for ( const auto& extLink : this->m_ExternalLinks )
    {
        if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            const auto count = this->m_Events.size () - 1;
            for ( size_t index = 0; index < count; ++index )
            {
                if ( this->m_Events [index].GetDescriptor ().IsFullyEqual ( this->m_CurrentDescriptor ) )
                {
                    this->m_CurrentDescriptor.Clear ();
                    return this->m_MessagePool->IncorrectCoincidingDescriptors ( info );
                }
            }
            this->m_Events.back ().GetDescriptor () = this->m_CurrentDescriptor;
            this->m_CurrentDescriptor.Clear ();
            return 0;
        }
    }
    this->m_CurrentDescriptor.Clear ();
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::Event_SetStatus ( const scbParseInfo& info )
{
    const auto id = this->GetDeviceIdByName ( info.Token );
    if ( id == -1 )
        return this->m_MessagePool->NameWasNotFound ( info );
    else
    {
        if ( this->m_Objects [id]->GetObjectType () == scbSchemeObject::ObjectType::Status )
        {
            this->m_Events.back ().StatusSet ( id );
            return 0;
        }
        else
            return this->m_MessagePool->NameMustBeTheStatus ( info );
    }
}

int scbSchemeManager::Event_ResetStatus ( const scbParseInfo& info )
{
    const auto id = this->GetDeviceIdByName ( info.Token );
    if ( id == -1 )
        return this->m_MessagePool->NameWasNotFound ( info );
    else
    {
        if ( this->m_Objects [id]->GetObjectType () == scbSchemeObject::ObjectType::Status )
        {
            this->m_Events.back ().StatusReset ( id );
            return 0;
        }
        else
            return this->m_MessagePool->NameMustBeTheStatus ( info );
    }
}

int scbSchemeManager::Event_ProbablityClass ( const scbParseInfo& info )
{
    if ( this->m_Events.back ().SetProbablityClass ( info.Token ) == 0 )
        return 0;
    else
        return this->m_MessagePool->IncorrectProbablityClass ( info );
}

int scbSchemeManager::Event_AddCondition ( const scbParseInfo& info )
{
    auto [res, id] = this->m_Events.back ().AddCondition ( this->m_CurrentConditionParam, info.Token );
    switch ( res )
    {
    case -1:
        return this->m_MessagePool->IncorrectDescriptionTag ( info );
    case 1:
        return this->m_MessagePool->IncorrectRepeatOfDescriptionTag ( info );
    }
    if ( this->m_CurrentConditionParam == -1 )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
            if ( extLink.GetDescriptionTag () == id )
                return 0;
        if ( this->m_Descriptions.size () > 1 )
            return this->m_MessagePool->ConditionParamIsRequired ( info );
    }
    return 0;
}

int scbSchemeManager::Event_AddConditionGroup ( const scbParseInfo& info )
{
    this->m_Events.back ().AddNewConditionGroup ();
    return 0;
}

int scbSchemeManager::Event_CheckConditionGroup ( const scbParseInfo& info )
{
    int res = 0;
    if ( this->m_Events.back ().CheckForEqualConditions () )
        res = this->m_MessagePool->DifferentDescriptionGroupsAreEqual ( info );
    return max ( this->CheckConditions ( info, this->m_Events.back ().GetLastConditions () ), res );
}

int scbSchemeManager::GrantRequirement_SourceName ( const scbParseInfo& info )
{
    this->m_RequirementMask.clear ();
    this->m_RequirementMask.resize ( 101, 0 );
    const auto cbegin = this->m_GrantingRequirements.cbegin ();
    const auto cend = this->m_GrantingRequirements.cend ();
    const wstring& name = info.Token;
    const auto res = find_if ( cbegin, cend, [&name] ( const auto& elm ) -> bool { return ( elm.GetName () == name ); } );
    if ( res == cend )
    {
        this->m_ReqId = -1;
        return this->m_MessagePool->IncorrectRequirementName ( info );
    }
    else
    {
        this->m_ReqId = res - cbegin;
        if ( this->m_GrantingRequirements [this->m_ReqId].IsSourceEnable () )
            return this->m_MessagePool->IncorrectRepeatOfRequirementName ( info );
        else
            return 0;
    }
}

int scbSchemeManager::GrantRequirement_AddRequirementName ( const scbParseInfo& info )
{
    bool ability = false;
    if ( this->m_ReqId != -1 )
    {
        for ( const auto& desc : this->m_Descriptions )
        {
            if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            for ( const auto& extLink : this->m_ExternalLinks )
            {
                if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
        }
        if ( ability and this->m_CurrentDescriptor.IsGroupDescriptor () )
        {
            for ( const auto& conn : this->m_ExternalConnections )
            {
                ability = false;
                if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
            if ( !ability )
            {
                this->m_CurrentDescriptor.Clear ();
                return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
            }
        }
        if ( ability )
        {
            for ( const auto& req : this->m_GrantingRequirements )
            {
                if ( req.CheckRequirementNames ( this->m_CurrentDescriptor ) )
                {
                    this->m_CurrentDescriptor.Clear ();
                    return this->m_MessagePool->IncorrectRepeatOfDescriptor ( info );
                }
            }
            if ( this->m_GrantingRequirements [this->m_ReqId].AddRequirementName ( this->m_CurrentDescriptor ) == 0 )
            {
                this->m_CurrentDescriptor.Clear ();
                return 0;
            }
            else
            {
                this->m_CurrentDescriptor.Clear ();
                return this->m_MessagePool->IncorrectRepeatOfDescriptor ( info );
            }
        }
    }
    this->m_CurrentDescriptor.Clear ();
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::GrantRequirement_CheckOutputDescriptorTemplate ( const scbParseInfo& info )
{
    bool ability = false;
    if ( this->m_ReqId != -1 )
    {
        for ( const auto& desc : this->m_Descriptions )
        {
            if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            for ( const auto& extLink : this->m_ExternalLinks )
            {
                if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
        }
        if ( ability )
            return 0;
    }
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::GrantRequirement_SetOutputCount ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        size_t pos = 0;
        int res = 0;
        const wstring& name = info.Token;
        try
        {
            res = std::stoi ( name, &pos );
            if ( ( pos < name.length () ) || ( res < 1 ) )
                res = -1;
        }
        catch ( std::invalid_argument )
        {
            res = -1;
        }
        if ( res == -1 )
            return this->m_MessagePool->NumberExcepted ( info );
        if ( this->m_GrantingRequirements [this->m_ReqId].SourceSetCount ( res ) == -1 )
            return this->m_MessagePool->NumberIsOutOfRange ( info );
        else
            return 0;
    }
    return 0;
}

int scbSchemeManager::GrantRequirement_AddNewRecord ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
        this->m_GrantingRequirements [this->m_ReqId].SourceNewRecord ();
    return 0;
}

int scbSchemeManager::GrantRequirement_From ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        size_t pos = 0;
        int res = 0;
        const wstring& name = info.Token;
        try
        {
            res = std::stoi ( name, &pos );
            if ( ( pos < name.length () ) || ( res < 1 ) )
                res = -1;
        }
        catch ( std::invalid_argument )
        {
            res = -1;
        }
        if ( res == -1 )
            return this->m_MessagePool->NumberExcepted ( info );
        if ( this->m_GrantingRequirements [this->m_ReqId].SourceSetFrom ( res ) == -1 )
            return this->m_MessagePool->NumberIsOutOfRange ( info );
        else
        {
            this->m_BackupIntVar = res;
            return 0;
        }
    }
    return 0;
}

int scbSchemeManager::GrantRequirement_To ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        size_t pos = 0;
        int res = 0;
        const wstring& name = info.Token;
        try
        {
            res = std::stoi ( name, &pos );
            if ( ( pos < name.length () ) || ( res < 1 ) )
                res = -1;
        }
        catch ( std::invalid_argument )
        {
            res = -1;
        }
        if ( res == -1 )
            return this->m_MessagePool->NumberExcepted ( info );
        if ( this->m_GrantingRequirements [this->m_ReqId].SourceSetTo ( res ) == -1 )
            return this->m_MessagePool->RequirementFromIsGreaterThanTo ( info );
        else
        {
            if ( this->m_GrantingRequirements [this->m_ReqId].GetMaxRequesting () < res )
                return this->m_MessagePool->UnableToGrantThisRequirement ( info );
            bool mark = false;
            for ( int index = this->m_BackupIntVar; index <= res; ++index )
            {
                if ( this->m_RequirementMask [index] == 1 )
                    mark = true;
                this->m_RequirementMask [index] = 1;
            }
            return mark ? this->m_MessagePool->MoreThanOneRecordForThisNumberOfRequestingRequirement ( info ) : 0;
        }
    }
    return 0;
}

int scbSchemeManager::GrantRequirement_Output ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        const auto& name = info.Token;
        if ( this->IsDefinedNameInMainSection ( name ) )
            return this->m_MessagePool->NameAlwaysUsed ( info );
        this->m_Objects.push_back ( unique_ptr<scbSchemeObject> ( new scbSchemeOutput ( name, scbSchemeOutput::Type::Requirement ) ) );
        if ( this->m_GrantingRequirements [this->m_ReqId].SourceAddOutput ( this->m_Objects.size () - 1 ) == 0 )
        {
            this->m_CurrentDescriptor.ReplaceFourthTag ( name );
            this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::Requirement );
            return 0;
        }
        else
            return this->m_MessagePool->IncorrectCountOfOutput ( info );
    }
    return 0;
}

int scbSchemeManager::GrantRequirement_FixRecord ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        if ( this->m_GrantingRequirements [this->m_ReqId].SourceFixRecord () == 0 )
            return 0;
        else
            return this->m_MessagePool->IncorrectCountOfOutput ( info );
    }
    return 0;
}

int scbSchemeManager::GrantRequirement_End ( const scbParseInfo& info )
{
    this->m_CurrentDescriptor.Clear ();
    const auto count = this->m_RequirementMask.size ();
    bool mark = false;
    for ( size_t index = 1; index < count; ++index )
    {
        if ( mark and ( this->m_RequirementMask [index] == 1 ) )
            return this->m_MessagePool->RequirementDoesntCoverWholeRange ( info );
        if ( this->m_RequirementMask [index] == 0 )
            mark = true;
    }
    return 0;
}

int scbSchemeManager::TransmitRequirement_RequestedName ( const scbParseInfo& info )
{
    this->m_BackupIntVar = -1;
    bool ability = false;
    for ( const auto& desc : this->m_Descriptions )
    {
        if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            ability = true;
            break;
        }
    }
    if ( !ability )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
        {
            if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
    }
    if ( ability and this->m_CurrentDescriptor.IsGroupDescriptor () )
    {
        for ( const auto& conn : this->m_ExternalConnections )
        {
            ability = false;
            if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
        }
    }
    if ( ability )
    {
        this->m_ReqId = -1;
        const auto count = this->m_RequestedRequirements.size ();
        for ( size_t index = 0; index < count; ++index )
        {
            if ( this->m_RequestedRequirements [index].GetDescriptor ().IsFullyEqual ( this->m_CurrentDescriptor ) )
                this->m_ReqId = index;
        }
        if ( this->m_ReqId == -1 )
        {
            this->m_RequestedRequirements.emplace_back ();
            this->m_RequestedRequirements.back ().SetDescriptor ( this->m_CurrentDescriptor );
            this->m_ReqId = this->m_RequestedRequirements.size () - 1;
        }
        this->m_CurrentDescriptor.Clear ();
        return 0;
    }
    this->m_CurrentDescriptor.Clear ();
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::TransmitRequirement_AddGrantingName ( const scbParseInfo& info )
{
    bool ability = false;
    if ( this->m_ReqId != -1 )
    {
        for ( const auto& desc : this->m_Descriptions )
        {
            if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            for ( const auto& extLink : this->m_ExternalLinks )
            {
                if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
        }
        if ( ability and this->m_CurrentDescriptor.IsGroupDescriptor () )
        {
            for ( const auto& conn : this->m_ExternalConnections )
            {
                ability = false;
                if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
            if ( !ability )
            {
                this->m_CurrentDescriptor.Clear ();
                return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
            }
        }
        if ( ability )
        {
            if ( this->m_BackupIntVar == -1 )
            {
                const auto count = this->m_GrantingRequirements.size ();
                for ( size_t index = 0; index < count; ++index )
                {
                    if ( this->m_GrantingRequirements [index].CheckRequirementNames ( this->m_CurrentDescriptor ) )
                    {
                        this->m_CurrentDescriptor.Clear ();
                        return this->m_MessagePool->IncorrectRepeatOfDescriptor ( info );
                    }
                    if ( m_GrantingRequirements [index].GetLinkedRequestedRequirement () == this->m_ReqId )
                        this->m_BackupIntVar = index;
                }
                if ( this->m_BackupIntVar == -1 )
                {
                    this->m_GrantingRequirements.emplace_back ( this->m_ReqId );
                    this->m_BackupIntVar = this->m_GrantingRequirements.size () - 1;
                }
            }
            if ( this->m_GrantingRequirements [this->m_BackupIntVar].AddRequirementName ( this->m_CurrentDescriptor ) == 0 )
            {
                this->m_CurrentDescriptor.Clear ();
                this->m_RequestedRequirements [this->m_ReqId].SetLinkedGrantingRequirements ( this->m_BackupIntVar );
                return 0;
            }
            else
            {
                this->m_CurrentDescriptor.Clear ();
                return this->m_MessagePool->IncorrectRepeatOfDescriptor ( info );
            }
        }
    }
    this->m_CurrentDescriptor.Clear ();
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::TransmitRequirement_Fix ( const scbParseInfo& info )
{
    return 0;
}

int scbSchemeManager::RequestedRequirement_RequestedName ( const scbParseInfo& info )
{
    this->m_BackupIntVar = -1;
    bool ability = false;
    for ( const auto& desc : this->m_Descriptions )
    {
        if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            ability = true;
            break;
        }
    }
    if ( !ability )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
        {
            if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
    }
    if ( ability and this->m_CurrentDescriptor.IsGroupDescriptor () )
    {
        for ( const auto& conn : this->m_ExternalConnections )
        {
            ability = false;
            if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
        }
    }
    if ( ability )
    {
        this->m_ReqId = -1;
        const auto count = this->m_RequestedRequirements.size ();
        for ( size_t index = 0; index < count; ++index )
        {
            if ( this->m_RequestedRequirements [index].GetDescriptor ().IsFullyEqual ( this->m_CurrentDescriptor ) )
                this->m_ReqId = index;
        }
        if ( this->m_ReqId == -1 )
        {
            this->m_RequestedRequirements.emplace_back ();
            this->m_RequestedRequirements.back ().SetDescriptor ( this->m_CurrentDescriptor );
            this->m_ReqId = this->m_RequestedRequirements.size () - 1;
        }
        this->m_CurrentDescriptor.Clear ();
        this->m_RequestedRequirements [this->m_ReqId].AddNewInputGroup ();
        return 0;
    }
    this->m_CurrentDescriptor.Clear ();
    return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
}

int scbSchemeManager::RequestedRequirement_AddInputName ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
    {
        bool ability = false;
        for ( const auto& desc : this->m_Descriptions )
        {
            if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            for ( const auto& extLink : this->m_ExternalLinks )
            {
                if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
        }
        if ( ability )
        {
            const auto count = this->m_InputDescriptors.size ();
            size_t index = 0;
            bool mark = false;
            for ( index = 0; index < count; ++index )
            {
                if ( this->m_InputDescriptors [index].GetDescriptor ().IsFullyEqual ( this->m_CurrentDescriptor ) )
                {
                    mark = true;
                    break;
                }
            }
            if ( !mark )
            {
                this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::FreeInput );
                index = this->m_InputDescriptors.size () - 1;
            }
            this->m_RequestedRequirements [this->m_ReqId].AddNewInput ( index );
        }
        else
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
        }
    }
    this->m_CurrentDescriptor.Clear ();
    return 0;
}

int scbSchemeManager::RequestedRequirement_AddFakeInput ( const scbParseInfo& info )
{
    if ( this->m_ReqId != -1 )
        this->m_RequestedRequirements [this->m_ReqId].AddNewFakeInput ();
    return 0;
}

int scbSchemeManager::RequestedRequirement_Fix ( const scbParseInfo& info )
{
    if ( ( this->m_ReqId != -1 ) and ( this->m_RequestedRequirements [this->m_ReqId].FixInputGroup () == 0 ) )
        return 0;
    else
        return this->m_MessagePool->WholeInputsInRequestingRequirementAreZero ( info );
}

int scbSchemeManager::TransitCircuit_TargetOutput ( const scbParseInfo& info )
{
            // Ñâîáîäíûé âûõîä
    const auto count = this->m_OutputDescriptors.size ();
    size_t index = 0;
    for ( index = 0; index < count; ++index )
        if ( this->m_OutputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::TargetOutput ) )
            break;
    if ( index == count )
        this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::TargetOutput );
    // index
    this->m_CurrentDescriptor.Clear ();
    return 0;
}

int scbSchemeManager::TransitCircuit_Output ( const scbParseInfo& info )
{
    bool ability = false;
    for ( const auto& desc : this->m_Descriptions )
    {
        if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            ability = true;
            break;
        }
    }
    if ( !ability )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
        {
            if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
    }
    const bool group = this->m_CurrentDescriptor.IsGroupDescriptor ();
    if ( ability and group )
    {
        for ( const auto& conn : this->m_ExternalConnections )
        {
            ability = false;
            if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
        }
    }
    if ( ability )
    {
        if ( group )
        {
             // Ãðóïïîâîé âûõîä
            const auto count = this->m_OutputDescriptors.size ();
            size_t index = 0;
            for ( index = 0; index < count; ++index )
                if ( this->m_OutputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput ) )
                    break;
            if ( index == count )
                this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput );
            // index
        }
        else
        {
            // Ñâîáîäíûé âûõîä
            const auto count = this->m_OutputDescriptors.size ();
            size_t index = 0;
            for ( index = 0; index < count; ++index )
                if ( this->m_OutputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::Output ) )
                    break;
            if ( index == count )
                this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::Output );
            // index
        }
        this->m_CurrentDescriptor.Clear ();
        return 0;
    }
    else
    {
        this->m_CurrentDescriptor.Clear ();
        return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
    }
}

int scbSchemeManager::TransitCircuit_FreeInput ( const scbParseInfo& info )
{
    bool ability = false;
    for ( const auto& desc : this->m_Descriptions )
    {
        if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
        {
            ability = true;
            break;
        }
    }
    if ( !ability )
    {
        for ( const auto& extLink : this->m_ExternalLinks )
        {
            if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
    }
    if ( ability and this->m_CurrentDescriptor.IsGroupDescriptor () )
    {
        for ( const auto& conn : this->m_ExternalConnections )
        {
            ability = false;
            if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
        }
    }
    if ( ability )
    {
        // Ñâÿçàííûé âõîä
        const auto count = this->m_InputDescriptors.size ();
        size_t index = 0;
        for ( index = 0; index < count; ++index )
            if ( this->m_InputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::FreeInput ) )
                break;
        if ( index == count )
            this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::FreeInput );
        // index
        this->m_CurrentDescriptor.Clear ();
        return 0;
    }
    else
    {
        this->m_CurrentDescriptor.Clear ();
        return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
    }
}

int scbSchemeManager::TransitCircuit_Input ( const scbParseInfo& info )
{
    bool ability = false;
    if ( this->m_CurrentDescriptor.IsGroupDescriptor ())
    {
        for ( const auto& desc : this->m_Descriptions )
        {
            if ( desc.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
            {
                ability = true;
                break;
            }
        }
        if ( !ability )
        {
            for ( const auto& extLink : this->m_ExternalLinks )
            {
                if ( extLink.GetDescriptor ().IsEqualForDescription ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
        }
        if ( ability )
        {
            for ( const auto& conn : this->m_ExternalConnections )
            {
                ability = false;
                if ( conn.GetDescriptor ().IsInclude ( this->m_CurrentDescriptor ) )
                {
                    ability = true;
                    break;
                }
            }
            if ( !ability )
            {
                this->m_CurrentDescriptor.Clear ();
                return this->m_MessagePool->IncorrectGroupTagInDescriptor ( info );
            }
        }
        if ( ability )
        {
            // Ãðóïïîâîé âõîä
            const auto count = this->m_InputDescriptors.size ();
            size_t index = 0;
            for ( index = 0; index < count; ++index )
                if ( this->m_InputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput ) )
                    break;
            if ( index == count )
                this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput );
            // index
            this->m_CurrentDescriptor.Clear ();
            return 0;
        }
        else
        {
            this->m_CurrentDescriptor.Clear ();
            return this->m_MessagePool->UsingOfIncorrectDescriptor ( info );
        }
    }
    else
    {
        // Ñâÿçàííûé âõîä
        const auto count = this->m_InputDescriptors.size ();
        size_t index = 0;
        for ( index = 0; index < count; ++index )
            if ( this->m_InputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::Input ) )
                break;
        if ( index == count )
            this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::Input );
        // index
        this->m_CurrentDescriptor.Clear ();
        return 0;
    }
}

int scbSchemeManager::TransitCircuit_Name ( const scbParseInfo& info )
{
    if ( this->m_ExternalConnections.size () == 2 )
    {
        const auto& name = info.Token;

        // Ãðóïïîâîé âõîä
        this->m_CurrentDescriptor = this->m_ExternalConnections [0].GetDescriptor ();
        this->m_CurrentDescriptor.AddTagName ( name );
        const auto count = this->m_InputDescriptors.size ();
        size_t index = 0;
        for ( index = 0; index < count; ++index )
            if ( this->m_InputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput ) )
                break;
        if ( index == count )
            this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput );
        // index

        // Ãðóïïîâîé âûõîä
        this->m_CurrentDescriptor = this->m_ExternalConnections [1].GetDescriptor ();
        this->m_CurrentDescriptor.AddTagName ( name );
        const auto count1 = this->m_OutputDescriptors.size ();
        for ( index = 0; index < count1; ++index )
            if ( this->m_OutputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput ) )
                break;
        if ( index == count1 )
            this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput );
        // index


        // Ãðóïïîâîé âõîä
        this->m_CurrentDescriptor = this->m_ExternalConnections [1].GetDescriptor ();
        this->m_CurrentDescriptor.AddTagName ( name );
        const auto count2 = this->m_InputDescriptors.size ();
        for ( index = 0; index < count2; ++index )
            if ( this->m_InputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput ) )
                break;
        if ( index == count2 )
            this->m_InputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeInputDescriptor::Type::GroupInput );
        // index

        // Ãðóïïîâîé âûõîä
        this->m_CurrentDescriptor = this->m_ExternalConnections [0].GetDescriptor ();
        this->m_CurrentDescriptor.AddTagName ( name );
        const auto count3 = this->m_OutputDescriptors.size ();
        for ( index = 0; index < count3; ++index )
            if ( this->m_OutputDescriptors [index].CheckDescriptor ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput ) )
                break;
        if ( index == count3 )
            this->m_OutputDescriptors.emplace_back ( this->m_CurrentDescriptor, scbSchemeOutputDescriptor::Type::GroupOutput );
        // index

        return 0;
    }
    else
        return this->m_MessagePool->UnableToUseShortNameTransitCircuit ( info );
}

int scbSchemeManager::TransitCircuit_AddCondition ( const scbParseInfo& info )
{
    return 0;
}

int scbSchemeManager::TransitCircuit_AddConditionGroup ( const scbParseInfo& info )
{
    return 0;
}

int scbSchemeManager::TransitCircuit_CheckConditionGroup ( const scbParseInfo& info )
{
    return 0;
}

