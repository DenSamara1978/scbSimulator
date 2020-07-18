#include <algorithm>

#include "SchemeManager.h"
#include "SchemeObject.h"
#include "SchemeStatus.h"
#include "SchemeVariable.h"
#include "SchemeBlock.h"
#include "SchemeLine.h"
#include "SchemeCross.h"
#include "SchemeInput.h"
#include "SchemeOutput.h"

#include "SchemeIncorrectRelay.h"

#include "RelayNmsh1_400.h"
#include "RelayNmsh1_1440.h"
#include "RelayNmshm1_11.h"
#include "RelayNmshm1_560.h"
#include "RelayNmshm1_1120.h"
#include "RelayNmshm1_1000_560.h"

#include "RelayNmsh2_4000.h"
#include "RelayNmshm2_1_5.h"
#include "RelayNmshm2_1500.h"
#include "RelayNmshm2_3000.h"

#include "RelayNmsh3_460_400.h"

#include "RelayNmsh4_2400.h"
#include "RelayNmsh4_3.h"

#include "RelayOmsh2_46.h"

#include "RelayAnvsh2_2400.h"

#include "RelayNmpsh_900.h"
#include "RelayNmpsh2_400.h"
#include "RelayNmpsh3m_02_250.h"

#include "RelayPmpush_150_150.h"

#include "RelayKmsh_450.h"
#include "RelayKmsh_750.h"
#include "RelayKmsh_3000.h"

#include "RelayDssh13a.h"

#include "RelayPpr3_5000.h"

#include "RelayKdr1_200.h"
#include "RelayKdr1_280.h"

#include "RelayKdr1m_3_8.h"
#include "RelayKdr1m_120.h"
#include "RelayKdr1m_280.h"
#include "RelayKdr1m_435.h"

#include "SchemeResistor.h"
#include "SchemeRheostat.h"
#include "SchemeCapacitor.h"
#include "SchemeFuse.h"
#include "SchemeDiode.h"
#include "SchemeTimeBlock.h"
#include "SchemeMeasuringPanel.h"
#include "SchemeTransformerSt4.h"
#include "SchemeTransformerSt5.h"
#include "SchemeTransformerSkt.h"

SchemeManager::SchemeManager() :
	mode(0),
	submode(0),
	level(0),
	multiplicator(0),
	isWithoutParameter(false),
	reqId(-1),
	objectPlacement(-1),
	objectOrder(-1)
{
	this->requirementMask.resize(101, 0);
}

SchemeManager::~SchemeManager()
{
}

void SchemeManager::clear()
{
	this->mode = 0;
	this->submode = 0;
	this->level = 0;
	this->multiplicator = 0;
	this->isWithoutParameter = false;
	this->multiplicatingBlockName.clear();
	this->reqId = -1;
	this->objectPlacement = -1;
	this->objectOrder = -1;
	this->objectCable.clear();
	this->objectLocation.clear();
	this->requirementMask.clear();
	this->requirementMask.resize(101, 0);

	this->objectNameString.clear();
	this->objectGeneralNameString.clear();
	this->mainName.clear();
	this->currentString.clear();
	this->currentDescriptor.clear();
	this->backupParseInfo = {L"", 0, 0};
	this->descriptions.clear();
	this->tunings.clear();
	this->externalLinks.clear();
	this->internalConnections.clear();
	this->externalConnections.clear();
	this->extendedBlocks.clear();
	this->grantingRequirements.clear();
	this->requestedRequirements.clear();
	this->events.clear();
	this->inputDescriptors.clear();
	this->outputDescriptors.clear();

	this->objects.clear();
	this->parameters.clear();
}

bool SchemeManager::isDefinedNameInMainSection(const wstring& name) const
{
	auto elm = find_if(this->objects.cbegin(), this->objects.cend(), [&name] (const auto& elm) -> bool
		{
			return  ((elm->getName() == name) and
				((elm->getObjectType() == SchemeObject::ObjectType::Block) or
					(elm->getObjectType() == SchemeObject::ObjectType::Relay) or
					(elm->getObjectType() == SchemeObject::ObjectType::Equipment) or
					(elm->getObjectType() == SchemeObject::ObjectType::Status) or
					(elm->getObjectType() == SchemeObject::ObjectType::Variable) or
					(elm->getObjectType() == SchemeObject::ObjectType::Cross) or
					(elm->getObjectType() == SchemeObject::ObjectType::Line) or
					(elm->getObjectType() == SchemeObject::ObjectType::Output)));
		});
	return (elm != this->objects.cend());
}

bool SchemeManager::isDefinedNameInInputSection(const wstring& name) const
{
	auto elm = find_if(this->objects.cbegin(), this->objects.cend(), [&name] (const auto& elm) -> bool
		{
			return  ((elm->getName() == name) and
				(elm->getObjectType() == SchemeObject::ObjectType::Input));
		});
	return (elm != this->objects.cend());
}

int SchemeManager::getBlockIdByName(const wstring& name) const
{
	const auto cbegin = this->objects.cbegin();
	const auto cend = this->objects.cend();
	const auto res = find_if(this->objects.cbegin(), this->objects.cend(), [&name] (const auto& elm) -> bool
		{
			return  ((elm->getName() == name) and
				(elm->getObjectType() == SchemeObject::ObjectType::Block));
		});
	return (res == cend) ? -1 : static_cast<int>(res - cbegin);
}

int SchemeManager::getDeviceIdByName(const wstring& name) const
{
	const auto cbegin = this->objects.cbegin();
	const auto cend = this->objects.cend();
	const auto res = find_if(this->objects.cbegin(), this->objects.cend(), [&name] (const auto& elm) -> bool
		{
			return  (elm->getName() == name);
		});
	return (res == cend) ? -1 : static_cast<int>(res - cbegin);
}

int SchemeManager::getInputDescriptorIdByName(const ComplexName& descriptor, SchemeInputDescriptor::Type type) const
{
	const auto cbegin = this->inputDescriptors.cbegin();
	const auto cend = this->inputDescriptors.cend();
	const auto res = find_if(cbegin, cend, [&descriptor, &type] (const auto& val) -> bool { return val.checkDescriptor(descriptor, type); });
	return (res == cend) ? -1 : static_cast<int>(res - cbegin);
}

int SchemeManager::getOutputDescriptorIdByName(const ComplexName& descriptor, SchemeOutputDescriptor::Type type) const
{
	const auto cbegin = this->outputDescriptors.cbegin();
	const auto cend = this->outputDescriptors.cend();
	const auto res = find_if(cbegin, cend, [&descriptor, &type] (const auto& val) -> bool { return val.checkDescriptor(descriptor, type); });
	return (res == cend) ? -1 : static_cast<int>(res - cbegin);
}

int SchemeManager::descriptorParameter(const ParseInfo& info, int order)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	if (cend != find_if(cbegin, cend, [info] (const auto& val) { return (get<0>(val) == info.token); }))
		return -1;
	else
	{
		this->parameters.emplace_back(info.token, 0, order);
		return static_cast<int>(this->parameters.size() - 1);
	}
}

int SchemeManager::placementNameParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	if (cend != find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) != 1)); }))
		return -1;
	else
	{
		const auto res = find_if(cbegin, cend, [info] (const auto& val) { return (get<0>(val) == info.token); });
		if (cend == res)
		{
			this->parameters.emplace_back(info.token, 1, -1);
			return static_cast<int>(this->parameters.size() - 1);
		}
		else
			return static_cast<int>(res - cbegin);
	}
}

int SchemeManager::aliasParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	if (cend != find_if(cbegin, cend, [info] (const auto& val) { return (get<0>(val) == info.token); }))
		return -1;
	else
	{
		this->parameters.emplace_back(info.token, 2, -1);
		return static_cast<int>(this->parameters.size() - 1);
	}
}

int SchemeManager::externalLinkParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	if (cend != find_if(cbegin, cend, [info] (const auto& val) { return (get<0>(val) == info.token); }))
		return -1;
	else
	{
		this->parameters.emplace_back(info.token, 3, -1);
		return static_cast<int>(this->parameters.size() - 1);
	}
}

pair<int, int> SchemeManager::useAnyParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	const auto res = find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) != 2)); });
	if (res != cend)
		return pair {0, static_cast<int>(res - cbegin)};
	else
		return pair {-1, -1};
}

pair<int, int> SchemeManager::useAliasParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	const auto res = find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) == 2)); });
	if (res != cend)
		return pair {0, static_cast<int>(res - cbegin)};
	else
		return pair {-1, -1};
}

pair<int, int> SchemeManager::useExternalLinkParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	const auto res = find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) == 3)); });
	if (res != cend)
		return pair {0, static_cast<int>(res - cbegin)};
	else
		return pair {-1, -1};
}

pair<int, int> SchemeManager::usePlacementParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	const auto res = find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) == 1)); });
	if (res != cend)
		return pair {0, static_cast<int>(res - cbegin)};
	else
		return pair {-1, -1};
}

pair<int, int> SchemeManager::useDescriptorParameter(const ParseInfo& info)
{
	const auto cend = this->parameters.cend();
	const auto cbegin = this->parameters.cbegin();
	const auto res = find_if(cbegin, cend, [info] (const auto& val) { return ((get<0>(val) == info.token) and (get<1>(val) == 0)); });
	if (res != cend)
		return pair {0, static_cast<int>(res - cbegin)};
	else
		return pair {-1, -1};
}

int SchemeManager::setConditionParam(const ParseInfo& info)
{
	if (this->descriptions.size() == 1)
		return this->messagePool->conditionParamIsNotRequired(info);
	else
	{
		const auto [res, id] = this->useDescriptorParameter(info);
		if (res != 0)
			return this->messagePool->incorrectParameter(info);
		else
		{
			this->currentConditionParam = id;
			return 0;
		}
	}
}

int SchemeManager::resetConditionParam(const ParseInfo& info)
{
	if ((this->descriptions.size() != 1) and (this->externalLinks.size() == 0))
		return this->messagePool->conditionParamIsRequired(info);
	else
	{
		this->currentConditionParam = -1;
		return 0;
	}
}

int SchemeManager::tagName(const ParseInfo& info)
{
	auto res = this->currentDescriptor.addTagName(info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptorTagOrder(info);
		case 1:
			return this->messagePool->incorrectDescriptorTag(info);
	}
	return 0;
}

int SchemeManager::tagParamName(const ParseInfo& info)
{
	const auto [res, id] = this->useAnyParameter(info);
	if (res != 0)
		return this->messagePool->incorrectParameter(info);
	else if (this->currentDescriptor.addParamTagId(Manager::parameterNameShift + id) != 0)
		return this->messagePool->incorrectDescriptorTagOrder(info);
	else
		return 0;
}

int SchemeManager::tagNewDescriptorParamName(const ParseInfo& info)
{
	const auto id = this->descriptorParameter(info);
	if (id == -1)
		return this->messagePool->incorrectRepeatOfParameter(info);
	else if (this->currentDescriptor.addParamTagId(Manager::parameterNameShift + id) != 0)
		return this->messagePool->incorrectDescriptorTagOrder(info);
	else
		return 0;
}

int SchemeManager::tagNewExternalLinkParamName(const ParseInfo& info)
{
	const auto id = this->externalLinkParameter(info);
	if (id == -1)
		return this->messagePool->incorrectRepeatOfParameter(info);
	else if (this->currentDescriptor.addParamTagId(Manager::parameterNameShift + id) != 0)
		return this->messagePool->incorrectDescriptorTagOrder(info);
	else
		return 0;
}

int SchemeManager::tagGroupName(const ParseInfo& info)
{
	auto res = this->currentDescriptor.addGroupTagName(info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptorTagOrder(info);
		case 1:
			return this->messagePool->incorrectDescriptorGroupTag(info);
	}
	return 0;
}

int SchemeManager::checkConditions(const ParseInfo& info, const vector<tuple<int, int, bool>>& conditions)
{
	for (const auto& tuning : this->tunings)
	{
		if (!(tuning.checkConditionsForAchievable(conditions)))
			return this->messagePool->unachievableDescriptionCombination(info);
	}
	for (const auto& desc : this->descriptions)
	{
		if (desc.checkConditionsForAchievable(conditions))
			return 0;
	}
	return this->messagePool->unachievableDescriptionCombination(info);
}

int SchemeManager::clearObjectName()
{
	this->objectNameString.clear();
	return 0;
}

int SchemeManager::addPatternToObjectName(const ParseInfo& info)
{
	this->objectNameString += info.token;
	return 0;
}

int SchemeManager::addParamToObjectName(const ParseInfo& info)
{
	int param_id = -1;
	auto [res, id] = this->useDescriptorParameter(info);
	if (res == 0)
		param_id = id;
	else
	{
		auto [res1, id1] = this->useAliasParameter(info);
		if (res1 == 0)
			param_id = id1;
		else
		{
			auto [res2, id2] = this->useExternalLinkParameter(info);
			if (res2 == 0)
				param_id = id2;
		}
	}
	if (param_id != -1)
	{
		this->objectNameString += L"%";
		this->objectNameString += to_wstring(param_id);
		this->objectNameString += L"%";
		const auto type = get<1>(this->parameters[param_id]);
		const auto order = get<2>(this->parameters[param_id]);
		if ((this->iteration == 0) or ((type == 0) and (order <= this->iteration)))
			return 0;
		else
			return this->messagePool->inactiveParameter(info);
	}
	else
		return this->messagePool->incorrectParameter(info);
}

int SchemeManager::schemeAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	this->descriptions.emplace_back();
	if (this->isWithoutParameter)
		return this->messagePool->descriptorWithoutParameterMustBeSingle(info);
	else
		return 0;
}


int SchemeManager::schemeSetMultiplicator(const ParseInfo& info)
{
	const auto mult = this->descriptions.back().setMultiplicator(info.token);
	if (mult == -1)
		return this->messagePool->invalidMultiplicatorArgument(info);
	else
	{
		if (this->multiplicator > 0)
			return this->messagePool->multiplicatingDescriptorMustBeSingle(info);
		else
		{
			this->multiplicator = mult;
			return 0;
		}
	}
}

int SchemeManager::schemeDescriptor(const ParseInfo& info)
{
	this->descriptions.back().getDescriptor() = this->currentDescriptor;
	this->currentDescriptor.clear();
	if (this->multiplicator > 0)
		return this->messagePool->multiplicatingDescriptorMustBeSingle(info);
	else
	{
		const auto count = this->descriptions.size();
		if (this->descriptions.back().getDescriptor().extractParamTag() == -1)
		{
			if (count == 1)
				this->isWithoutParameter = true;
			else
				return this->messagePool->descriptorWithoutParameterMustBeSingle(info);
		}
		for (size_t i = 0; i < count - 1; ++i)
		{
			if (this->descriptions[i].getDescriptor().isEqualForDescription(this->descriptions.back().getDescriptor()))
				return this->messagePool->incorrectCoincidingDescriptors(info);
		}
		return 0;
	}
}

int SchemeManager::schemeAddNewPlacementName(const ParseInfo& info)
{
	this->backupIntVar = this->placementNameParameter(info);
	if (this->backupIntVar == -1)
		return this->messagePool->incorrectRepeatOfParameter(info);
	else
	{
		if (this->descriptions.back().addNewPlacement(this->backupIntVar) != 0)
			return this->messagePool->incorrectRepeatOfPlacementName(info);
		else
			return 0;
	}
}

int SchemeManager::schemeSetPlacementType(const ParseInfo& info)
{
	// Ñíà÷àëà ïðîâåðêà ñîîòâåòñòâèÿ òèïîâ è èìåí âíóòðè ñâîåãî Îïèñàíèÿ...
	const auto [res, id] = this->descriptions.back().setPlacementType(info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectPlacementType(info);
		case 1:
			return this->messagePool->incorrectRepeatOfPlacementType(info);
	}
	// ...çàòåì ïðîâåðêà ñîîòâåòñòâèÿ òèïîâ è èìåí ìåæäó âñåìè Îïèñàíèÿìè è òåêóùèì
	const auto count = this->descriptions.size();
	for (size_t index = 0; index < count - 1; ++index)
	{
		if (!(this->descriptions[index].canExistAnotherPlacement(this->backupIntVar, id)))
			return this->messagePool->inexactRepeatOfPlacement(info);
	}
	return 0;
}

int SchemeManager::schemeAddNewDescriptionGroup(const ParseInfo& info)
{
	this->descriptions.back().addNewDescriptionGroup();
	return 0;
}

int SchemeManager::schemeAddNewDescriptionTag(const ParseInfo& info)
{
	int res = 0;
	switch (this->descriptions.back().addNewDescription(info.token))
	{
		case 1:
			res = this->messagePool->incorrectRepeatOfDescriptionTag(info);
			break;
		case -1:
			res = this->messagePool->incorrectDescriptionTag(info);
			break;
	}
	return res;
}

int SchemeManager::schemeCheckDescriptionGroup(const ParseInfo& info)
{
	if (this->descriptions.back().checkDescriptionGroups())
		return 0;
	else
		return this->messagePool->differentDescriptionGroupsAreEqual(info);
}

int SchemeManager::schemeMultiplicate(const ParseInfo& info)
{
	if (this->multiplicator > 0)
	{
		const auto cbegin = this->parameters.cbegin();
		const auto cend = this->parameters.cend();
		auto res = find_if(cbegin, cend, [] (const auto& val) { return (get<1>(val) == 0); });
		const wstring baseName = get<0>(*res);
		get<0>(this->parameters[res - cbegin]) += L"1";
		get<2>(this->parameters[res - cbegin]) = 1;
		for (int counter = 2; counter <= this->multiplicator; ++counter)
		{
			ParseInfo new_info = info;
			new_info.token = baseName + to_wstring(counter);
			this->descriptions.push_back(this->descriptions.back());
			this->descriptions.back().getDescriptor().setSecondTag(Manager::parameterNameShift + this->descriptorParameter(new_info, counter));
		}
	}
	return 0;
}

int SchemeManager::schemeAddNewBlockName(const ParseInfo& info)
{
	if (this->multiplicator == 0)
		return this->messagePool->incorrectSectionBlockInAloneDescriptor(info);
	else if (!(this->multiplicatingBlockName.empty()))
		return this->messagePool->tooMuchSectionBlockInDescriptor(info);
	else
	{
		this->multiplicatingBlockName = info.token;
		return 0;
	}
}

int SchemeManager::aliasAddAlias(const ParseInfo& info)
{
	if (this->multiplicator > 0)
		return this->messagePool->multiplicatingDescriptorCantHaveAnyAliases(info);
	const auto id = this->aliasParameter(info);
	if (id != -1)
		return 0;
	else
		return this->messagePool->incorrectRepeatOfParameter(info);
}

int SchemeManager::aliasPreParamString(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::aliasParamString(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::aliasPostParamString(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::aliasSortParam(const ParseInfo& info)
{
	return 0;
}


int SchemeManager::tuningAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	this->tunings.emplace_back();
	return 0;
}

int SchemeManager::tuningDescriptor(const ParseInfo& info)
{
	this->tunings.back().getDescriptor() = this->currentDescriptor;
	this->currentDescriptor.clear();
	if ((this->descriptions.size() == 1) or (this->multiplicator > 0))
		return this->messagePool->incorrectDescriptorPresence(info);
	else
	{
		for (const auto& desc : this->descriptions)
			if (desc.getDescriptor().isEqual(this->tunings.back().getDescriptor()))
				return 0;
	}
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::tuningCheckDescriptor(const ParseInfo& info)
{
	if (((this->multiplicator == 0) and (this->descriptions.size() > 1)) and (this->tunings.back().getDescriptor().getType() == ComplexName::ComplexNameType::Empty))
		return this->messagePool->incorrectDescriptorAbsence(info);
	else
		return 0;
}

int SchemeManager::tuningAddNewDescriptionTag(const ParseInfo& info)
{
	int res = 0;
	switch (this->tunings.back().addNewDescription(info.token))
	{
		case 1:
			res = this->messagePool->incorrectRepeatOfDescriptionTag(info);
			break;
		case -1:
			res = this->messagePool->incorrectDescriptionTag(info);
			break;
	}
	return res;
}

int SchemeManager::tuningCheckDescriptionAndTuning(const ParseInfo& info)
{
	for (const auto& description : this->descriptions)
	{
		auto [param, tunings] = this->tunings.back().getDescriptionTags();
		if (this->tunings.back().getDescriptor().isEqual(description.getDescriptor()))
		{
			if (!(description.checkForTuning(tunings)))
				return this->messagePool->unachievableDescriptionCombination(info);
		}
	}
	const auto count = this->tunings.size() - 1;
	for (size_t index = 0; index < count; ++index)
	{
		if (this->tunings[index].isIdentical(this->tunings.back()))
			return this->messagePool->incorrectCoincidingDescriptionSets(info);
	}
	return 0;
}

int SchemeManager::externalLinkAddNew(const ParseInfo& info)
{
	this->externalLinks.emplace_back();
	this->currentDescriptor.clear();
	this->currentConditionParam = -1;
	this->startParseInfo = info;
	if (this->multiplicator > 0)
		return this->messagePool->multiplicatingDescriptorCantHaveAnyExternalLink(info);
	else if (this->isWithoutParameter)
		return this->messagePool->cantHaveAnyExternalLinks(info);
	else
		return 0;
}

int SchemeManager::externalLinkDescriptor(const ParseInfo& info)
{
	for (const auto& desc : this->descriptions)
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			return this->messagePool->usingOfIncorrectDescriptor(info);
	const auto count = this->externalLinks.size() - 1;
	for (size_t index = 0; index < count; ++index)
		if (this->externalLinks[index].getDescriptor().isEqualForDescription(this->currentDescriptor))
			return this->messagePool->incorrectCoincidingDescriptors(info);
	this->externalLinks.back().getDescriptor() = this->currentDescriptor;
	this->currentDescriptor.clear();
	return 0;
}

int SchemeManager::externalLinkNecesserily(const ParseInfo& info)
{
	this->externalLinks.back().setNecesserily();
	return 0;
}

int SchemeManager::externalLinkDescriptionTag(const ParseInfo& info)
{
	auto [res, id] = this->externalLinks.back().setDescriptionTag(info.token);
	if (res != 0)
		return this->messagePool->incorrectDescriptionTag(info);
	else
	{
		for (const auto& description : this->descriptions)
		{
			if (!(description.checkForExternalLinkDescription(id)))
				return this->messagePool->incorrectRepeatOfDescriptionTag(info);
		}
		for (const auto& tuning : this->tunings)
		{
			if (!(tuning.checkForExternalLinkDescription(id)))
				return this->messagePool->incorrectRepeatOfDescriptionTag(info);
		}
		const auto count = this->externalLinks.size() - 1;
		for (size_t index = 0; index < count; ++index)
		{
			if (this->externalLinks[index].checkPresenceInConditionsAndDescription(id))
				return this->messagePool->incorrectDescriptionTag(info);
		}
		return 0;
	}
}

int SchemeManager::externalLinkAddConditionGroup(const ParseInfo& info)
{
	this->externalLinks.back().addNewConditionGroup();
	return 0;
}

int SchemeManager::externalLinkAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->externalLinks.back().addCondition(this->currentConditionParam, info.token);
	for (const auto& extLink : this->externalLinks)
	{
		if (extLink.getDescriptionTag() == id)
			return this->messagePool->incorrectDescriptionTag(info);
	}
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	return 0;
}

int SchemeManager::externalLinkCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->externalLinks.back().checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->externalLinks.back().getLastConditions()), res);
}

int SchemeManager::externalConnectionAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	this->externalConnections.emplace_back();
	if (this->multiplicator > 0)
		return this->messagePool->multiplicatingDescriptorCantHaveAnyConnection(info);
	else if (this->isWithoutParameter)
		return this->messagePool->cantHaveAnyExternalConnections(info);
	else
		return 0;
}

int SchemeManager::externalConnectionDescriptor(const ParseInfo& info)
{
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			const auto count = this->externalConnections.size() - 1;
			for (size_t index = 0; index < count; ++index)
				if (this->externalConnections[index].getDescriptor().isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			for (const auto& connection : this->internalConnections)
			{
				if (connection.getDescriptor(0).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
				if (connection.getDescriptor(1).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			}
			this->externalConnections.back().getDescriptor() = this->currentDescriptor;
			this->currentDescriptor.clear();
			return 0;
		}
	}
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::externalConnectionAddConditionGroup(const ParseInfo& info)
{
	this->externalConnections.back().addNewConditionGroup();
	return 0;
}

int SchemeManager::externalConnectionAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->externalConnections.back().addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	for (const auto& link : this->externalLinks)
		if (link.getDescriptionTag() == id)
			return this->messagePool->incorrectRepeatOfDescription(info);
	return 0;
}

int SchemeManager::externalConnectionCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->externalConnections.back().checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->externalConnections.back().getLastConditions()), res);
}

int SchemeManager::internalConnectionAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	this->internalConnections.emplace_back();
	if (this->multiplicator > 0)
		return this->messagePool->multiplicatingDescriptorCantHaveAnyConnection(info);
	else if (this->descriptions.size() == 1)
		return this->messagePool->cantHaveAnyInternalConnections(info);
	else
		return 0;
}

int SchemeManager::internalConnectionFirstDescriptor(const ParseInfo& info)
{
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			const auto count = this->internalConnections.size() - 1;
			for (size_t index = 0; index < count; ++index)
			{
				if (this->internalConnections[index].getDescriptor(0).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
				if (this->internalConnections[index].getDescriptor(1).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			}
			for (const auto& connection : this->externalConnections)
				if (connection.getDescriptor().isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			this->internalConnections.back().getDescriptor(0) = this->currentDescriptor;
			this->currentDescriptor.clear();
			return 0;
		}
	}
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::internalConnectionSecondDescriptor(const ParseInfo& info)
{
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			if (this->internalConnections.back().getDescriptor(0).isEqual(this->currentDescriptor))
				return this->messagePool->incorrectCoincidingDescriptors(info);
			const auto count = this->internalConnections.size() - 1;
			for (size_t index = 0; index < count; ++index)
			{
				if (this->internalConnections[index].getDescriptor(0).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
				if (this->internalConnections[index].getDescriptor(1).isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			}
			for (const auto& connection : this->externalConnections)
				if (connection.getDescriptor().isEqual(this->currentDescriptor))
					return this->messagePool->incorrectCoincidingDescriptors(info);
			if (this->internalConnections.back().getDescriptor(0).isEqualForDescription(this->currentDescriptor))
				this->messagePool->usingInternalConnectionWithSameDescriptor(info);
			this->internalConnections.back().getDescriptor(1) = this->currentDescriptor;
			this->currentDescriptor.clear();
			return 0;
		}
	}
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::internalConnectionAddConditionGroup(const ParseInfo& info)
{
	this->internalConnections.back().addNewConditionGroup();
	return 0;
}

int SchemeManager::internalConnectionAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->internalConnections.back().addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	for (const auto& link : this->externalLinks)
		if (link.getDescriptionTag() == id)
			return this->messagePool->incorrectRepeatOfDescription(info);
	return 0;
}

int SchemeManager::internalConnectionCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->internalConnections.back().checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->internalConnections.back().getLastConditions()), res);
}

int SchemeManager::extendedBlockAddNew(const ParseInfo& info)
{
	this->extendedBlocks.emplace_back();
	if (this->multiplicator > 1)
		return this->messagePool->multiplicatingDescriptorCantHaveAnyExtendedBlock(info);
	else if (this->isWithoutParameter)
		return this->messagePool->cantHaveAnyExtendedBlocks(info);
	else
		return 0;
}

int SchemeManager::extendedBlockName(const ParseInfo& info)
{
	const wstring& name = info.token;
	const auto count = this->extendedBlocks.size() - 1;
	for (size_t index = 0; index < count; ++index)
		if (this->extendedBlocks[index].getName() == name)
			return this->messagePool->nameAlwaysUsed(info);
	this->extendedBlocks.back().setName(name);
	return 0;
}

int SchemeManager::extendedBlockDefaultCount(const ParseInfo& info)
{
	if (this->extendedBlocks.back().setDefaultCount(info.token) == -1)
		return this->messagePool->invalidExtendedBlockCountArgument(info);
	else
		return 0;
}

int SchemeManager::extendedBlockAddConditionGroup(const ParseInfo& info)
{
	this->extendedBlocks.back().addNewConditionGroup();
	if (this->extendedBlocks.back().addNewConditionCount(info.token) == -1)
		return this->messagePool->invalidExtendedBlockCountArgument(info);
	else
		return 0;
}

int SchemeManager::extendedBlockAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->extendedBlocks.back().addCondition(this->currentConditionParam, info.token);
	if ((this->descriptions.size() > 1) and (this->currentConditionParam == -1))
	{
		bool mark = false;
		for (const auto& extLink : this->externalLinks)
		{
			if (extLink.getDescriptionTag() == id)
			{
				mark = true;
				break;
			}
		}
		if (!mark)
			return this->messagePool->conditionParamIsRequired(info);
	}
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	return 0;
}

int SchemeManager::extendedBlockCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->extendedBlocks.back().checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->extendedBlocks.back().getLastConditions()), res);
}

int SchemeManager::blockAddNew(const ParseInfo& info)
{
	if (!(this->isDefinedNameInMainSection(info.token)))
	{
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeBlock(info.token)));
		return 0;
	}
	else
		return this->messagePool->nameAlwaysUsed(info);
}

int SchemeManager::blockSetTypeName(const ParseInfo& info)
{
	if (this->objects.back()->setTypeName(info.token) == 0)
		return 0;
	else
		return this->messagePool->unknownTypeOfBlock(info, this->objects.back()->getName());
}

int SchemeManager::blockSetPlacement(const ParseInfo& info)
{
	auto [res, id] = this->usePlacementParameter(info);
	if (res == 0)
	{
		this->backupIntVar = id;
		Description::PlacementType pl_type = Description::PlacementType::No;
		for (const auto& desc : this->descriptions)
			if ((pl_type = desc.getPlacementType(id)) != Description::PlacementType::No)
				break;
		if ((pl_type != Description::PlacementType::No) and (this->objects.back()->setPlacement(id, pl_type) == 0))
			return 0;
		else
			return this->messagePool->incompatiblePlacement(info);
	}
	else
		return this->messagePool->undefinedPlacementName(info);
}

int SchemeManager::blockSetLocation(const ParseInfo& info)
{
	const auto count = this->objects.size() - 1;
	for (size_t index = 0; index < count; ++index)
		if (this->objects[index]->checkLocation(-1, this->backupIntVar, info.token))
			return this->messagePool->locationStillOccupied(info);
	if (this->objects.back()->setLocation(info.token) == 0)
		return 0;
	else
		return this->messagePool->deviceCantOccupyTheLocation(info);
}

int SchemeManager::blockAddObjectName(const ParseInfo& info)
{
	this->objects.back()->addNewObjectName(this->currentString);
	this->currentString.clear();
	return 0;
}

int SchemeManager::blockFixMultipleNames(const ParseInfo& info)
{
	const auto namesCount = this->objects.back()->getObjectNamesCount();
	const auto descCount = this->descriptions.size();
	if (this->multiplicator < 2)
	{
		if (namesCount == 1)
			return 0;
		else
			return this->messagePool->simpleDescriptorCantHaveAlternativeNames(info);
	}
	else
	{
		if ((namesCount == descCount) or (namesCount == 1))
			return 0;
		else
			return this->messagePool->incorrectCountOfAlternativeNames(info);
	}
}

int SchemeManager::blockFixSingleName(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::relayAddNew(const ParseInfo& info)
{
	if (!(this->isDefinedNameInMainSection(info.token)))
	{
		this->mainName = info.token;
		return 0;
	}
	else
		return this->messagePool->nameAlwaysUsed(info);
}

int SchemeManager::relaySetTypeName(const ParseInfo& info)
{
	SchemeObject* pObject = nullptr;
	bool incorrectType = false;
	const wstring& type = info.token;

	if (type == L"ÍÌØ1-400")
		pObject = new RelayNmsh1_400(this->mainName, true);
	else if (type == L"ÍÌ1-400")
		pObject = new RelayNmsh1_400(this->mainName, false);
	else if (type == L"ÍÌØ1-1440")
		pObject = new RelayNmsh1_1440(this->mainName, true);
	else if (type == L"ÍÌ1-1440")
		pObject = new RelayNmsh1_1440(this->mainName, false);
	else if (type == L"ÍÌØÌ1-11")
		pObject = new RelayNmshm1_11(this->mainName, true);
	else if (type == L"ÍÌÌ1-11")
		pObject = new RelayNmshm1_11(this->mainName, false);
	else if (type == L"ÍÌØÌ1-560")
		pObject = new RelayNmshm1_560(this->mainName, true);
	else if (type == L"ÍÌÌ1-560")
		pObject = new RelayNmshm1_560(this->mainName, false);
	else if (type == L"ÍÌØÌ1-1120")
		pObject = new RelayNmshm1_1120(this->mainName, true);
	else if (type == L"ÍÌÌ1-1120")
		pObject = new RelayNmshm1_1120(this->mainName, false);
	else if (type == L"ÍÌØÌ1-1000/560")
		pObject = new RelayNmshm1_1000_560(this->mainName, true);
	else if (type == L"ÍÌÌ1-1000/560")
		pObject = new RelayNmshm1_1000_560(this->mainName, false);

	else if (type == L"ÍÌØ2-4000")
		pObject = new RelayNmsh2_4000(this->mainName, true);
	else if (type == L"ÍÌ2-4000")
		pObject = new RelayNmsh2_4000(this->mainName, false);
	else if (type == L"ÍÌØÌ2-1.5")
		pObject = new RelayNmshm2_1_5(this->mainName, true);
	else if (type == L"ÍÌÌ2-1.5")
		pObject = new RelayNmshm2_1_5(this->mainName, false);
	else if (type == L"ÍÌØÌ2-1500")
		pObject = new RelayNmshm2_1500(this->mainName);
	else if (type == L"ÍÌØÌ2-3000")
		pObject = new RelayNmshm2_3000(this->mainName);

	else if (type == L"ÍÌØ3-460/400")
		pObject = new RelayNmsh3_460_400(this->mainName);

	else if (type == L"ÍÌØ4-2400")
		pObject = new RelayNmsh4_2400(this->mainName, true);
	else if (type == L"ÍÌ4-2400")
		pObject = new RelayNmsh4_2400(this->mainName, false);
	else if (type == L"ÍÌØ4-3")
		pObject = new RelayNmsh4_3(this->mainName, true);
	else if (type == L"ÍÌ4-3")
		pObject = new RelayNmsh4_3(this->mainName, false);

	else if (type == L"ÎÌØ2-46")
		pObject = new RelayOmsh2_46(this->mainName, true);
	else if (type == L"ÎÌ2-46")
		pObject = new RelayOmsh2_46(this->mainName, false);

	else if (type == L"ÀÍÂØ2-2400")
		pObject = new RelayAnvsh2_2400(this->mainName);

	else if (type == L"ÍÌÏØ2-400")
		pObject = new RelayNmpsh2_400(this->mainName);
	else if (type == L"ÍÌÏØ-900")
		pObject = new RelayNmpsh_900(this->mainName);
	else if (type == L"ÍÌÏØ3Ì-0.2/250")
		pObject = new RelayNmpsh3m_02_250(this->mainName, true);
	else if (type == L"ÍÌÏ3Ì-0.2/250")
		pObject = new RelayNmpsh3m_02_250(this->mainName, false);

	else if (type == L"ÏÌÏÓØ-150/150")
		pObject = new RelayPmpush_150_150(this->mainName, true);
	else if (type == L"ÏÌÏÓ-150/150")
		pObject = new RelayPmpush_150_150(this->mainName, false);

	else if (type == L"ÊÌØ-450")
		pObject = new RelayKmsh_450(this->mainName, true);
	else if (type == L"ÊÌ-450")
		pObject = new RelayKmsh_450(this->mainName, false);
	else if (type == L"ÊÌØ-750")
		pObject = new RelayKmsh_750(this->mainName);
	else if (type == L"ÊÌØ-3000")
		pObject = new RelayKmsh_3000(this->mainName, true);
	else if (type == L"ÊÌ-3000")
		pObject = new RelayKmsh_3000(this->mainName, false);

	else if (type == L"ÄÑØ-13À")
		pObject = new RelayDssh13a(this->mainName);

	else if (type == L"ÏÏÐ3-5000")
		pObject = new RelayPpr3_5000(this->mainName);

	else if (type == L"ÊÄÐ1-200")
		pObject = new RelayKdr1_200(this->mainName);
	else if (type == L"ÊÄÐ1-280")
		pObject = new RelayKdr1_280(this->mainName);
	else if (type == L"ÊÄÐ1Ì-3.8")
		pObject = new RelayKdr1m_3_8(this->mainName);
	else if (type == L"ÊÄÐ1Ì-120")
		pObject = new RelayKdr1m_120(this->mainName);
	else if (type == L"ÊÄÐ1Ì-280")
		pObject = new RelayKdr1m_280(this->mainName);
	else if (type == L"ÊÄÐ1Ì-435")
		pObject = new RelayKdr1m_435(this->mainName);

	else
	{
		incorrectType = true;
		pObject = new SchemeIncorrectRelay(this->mainName);
	}

	this->objects.push_back(unique_ptr<SchemeObject>(pObject));
	if (incorrectType)
		return this->messagePool->unknownTypeOfRelay(this->mainName, type, info);
	else
		return 0;
}

int SchemeManager::relaySetBlock(const ParseInfo& info)
{
	const auto id = this->getBlockIdByName(info.token);
	if (id == -1)
		return this->messagePool->undefinedPlacementName(info);
	else
	{
		this->backupIntVar = -id - 1;
		if (this->objects.back()->setBlock(id) == 0)
			return 0;
		else
			return this->messagePool->incompatiblePlacement(info);
	}
}

int SchemeManager::relaySetPlacement(const ParseInfo& info)
{
	const auto [res, id] = this->usePlacementParameter(info);
	if (res == 0)
	{
		this->backupIntVar = id;
		Description::PlacementType pl_type = Description::PlacementType::No;
		for (const auto& desc : this->descriptions)
			if ((pl_type = desc.getPlacementType(id)) != Description::PlacementType::No)
				break;
		if ((pl_type != Description::PlacementType::No) and (this->objects.back()->setPlacement(id, pl_type) == 0))
			return 0;
		else
			return this->messagePool->incompatiblePlacement(info);
	}
	else
		return this->messagePool->undefinedPlacementName(info);
}

int SchemeManager::relaySetLocation(const ParseInfo& info)
{
	const auto count = this->objects.size() - 1;
	const auto block = (this->backupIntVar < 0) ? -this->backupIntVar - 1 : -1;
	const auto placement = (this->backupIntVar >= 0) ? this->backupIntVar : -1;
	for (size_t index = 0; index < count; ++index)
		if (this->objects[index]->checkLocation(block, placement, info.token))
			return this->messagePool->locationStillOccupied(info);
	if (this->objects.back()->setLocation(info.token) == 0)
		return 0;
	else
		return this->messagePool->deviceCantOccupyTheLocation(info);
}

int SchemeManager::relayAddObjectName(const ParseInfo& info)
{
	this->objects.back()->addNewObjectName(this->currentString);
	this->currentString.clear();
	return 0;
}

int SchemeManager::relayAddJumper(const ParseInfo& info)
{
	switch (this->objects.back()->setJumper(info.token))
	{
		case -1:
			return this->messagePool->deviceCantHaveAnyJumper(info, this->objects.back()->getTypeName());
		case 1:
			return this->messagePool->deviceCantHaveThisJumper(info, this->objects.back()->getTypeName());
		case 2:
			return this->messagePool->incorrectRepeatOfJumper(info);
	}
	return 0;
}

int SchemeManager::relayAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->objects.back()->addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	if (this->currentConditionParam == -1)
	{
		for (const auto& extLink : this->externalLinks)
			if (extLink.getDescriptionTag() == id)
				return 0;
		if (this->descriptions.size() > 1)
			return this->messagePool->conditionParamIsRequired(info);
	}
	return 0;
}

int SchemeManager::relayAddConditionGroup(const ParseInfo& info)
{
	this->objects.back()->addNewConditionGroup();
	return 0;
}

int SchemeManager::relayCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->objects.back()->checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->objects.back()->getLastConditions()), res);
}

int SchemeManager::relaySetRequirement(const ParseInfo& info)
{
	if (this->objects.back()->setRequirement(this->reqId) == -1)
		return this->messagePool->relayCantUseToCoverAnyRequirement(info, this->objects.back()->getTypeName());
	Description::PlacementType pl_type = Description::PlacementType::No;
	for (const auto& desc : this->descriptions)
		if ((pl_type = desc.getPlacementType(this->objectPlacement)) != Description::PlacementType::No)
			break;
	if ((pl_type != Description::PlacementType::No) and (this->objects.back()->setPlacement(this->objectPlacement, pl_type) == 0))
		return 0;
	else
	{
		ParseInfo new_info = info;
		new_info.token = get<0>(this->parameters[this->objectPlacement]);
		return this->messagePool->incompatiblePlacement(new_info);
	}
}

int SchemeManager::relaySetRequirementFrom(const ParseInfo& info)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi(info.token, &pos);
		if ((pos < info.token.length()) or (res < 0))
			res = -1;
	}
	catch (std::invalid_argument)
	{
		res = -1;
	}
	if (res == -1)
		return this->messagePool->numberExcepted(info);
	else if ((res < 0) or (res > 100))
		return this->messagePool->numberIsOutOfRange(info);
	this->backupIntVar = res;
	this->objects.back()->setRequirementTo(res);
	return 0;
}

int SchemeManager::relaySetRequirementTo(const ParseInfo& info)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi(info.token, &pos);
		if ((pos < info.token.length()) or (res < 0))
			res = -1;
	}
	catch (std::invalid_argument)
	{
		res = -1;
	}
	if (res == -1)
		return this->messagePool->numberExcepted(info);
	else if ((res < 0) or (res > 100))
		return this->messagePool->numberIsOutOfRange(info);
	for (int index = this->backupIntVar; index <= res; ++index)
		this->requirementMask[index] = 1;
	this->grantingRequirements[this->reqId].setMaxRequesting(res);
	res = this->objects.back()->setRequirementTo(res);
	if (res == 1)
		return this->messagePool->requirementFromIsGreaterThanTo(info);
	else
		return 0;
}

int SchemeManager::relayFixDescription(const ParseInfo& info)
{
	switch (this->objects.back()->fixDescription())
	{
		case 1:
			return this->messagePool->deviceHasIncompleteSetOfJumpers(info);
		case 2:
			return this->messagePool->deviceHasIncompatibleSetOfJumpers(info);
	}
	return 0;
}

int SchemeManager::relayRequirementName(const ParseInfo& info)
{
	bool mark = false;
	for (const auto& req : this->grantingRequirements)
	{
		if (req.getName() == info.token)
		{
			mark = true;
			break;
		}
	}
	this->grantingRequirements.emplace_back(info.token);
	this->reqId = static_cast<int>(this->grantingRequirements.size() - 1);
	this->requirementMask.clear();
	this->requirementMask.resize(101, 0);
	if (mark)
		return this->messagePool->nameAlwaysUsed(info);
	else if (Description::getDescriptionIdByName(info.token) != -1)
		return this->messagePool->requirementNameMustBeNonDescriptionName(info);
	else
		return 0;
}

int SchemeManager::relayRequirementPlacement(const ParseInfo& info)
{
	auto [res, id] = this->usePlacementParameter(info);
	this->objectPlacement = id;
	if (res == 0)
		return 0;
	else
		return this->messagePool->undefinedPlacementName(info);
}

int SchemeManager::relayFixRequirement(const ParseInfo& info)
{
	int status = 0;
	const auto count = this->requirementMask.size();
	for (size_t index = 1; index < count; ++index)
	{
		if ((this->requirementMask[index] == 1) and (status == 2))
			return this->messagePool->requirementDoesntCoverWholeRange(info);
		if ((this->requirementMask[index] == 0) and (status == 1))
			status = 2;
		if ((this->requirementMask[index] == 1) and (status == 0))
			status = 1;
	}
	return 0;
}

int SchemeManager::statusAddNew(const ParseInfo& info)
{
	if (this->isDefinedNameInMainSection(info.token))
		return this->messagePool->nameAlwaysUsed(info);
	else
	{
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeStatus(info.token)));
		return 0;
	}
}

int SchemeManager::statusSetDefaultOne(const ParseInfo& info)
{
	this->objects.back()->defaultSettingStatus();
	return 0;
}

int SchemeManager::variableAddNew(const ParseInfo& info)
{
	if (this->isDefinedNameInMainSection(info.token))
		return this->messagePool->nameAlwaysUsed(info);
	else
	{
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeVariable(info.token)));
		return 0;
	}
}

int SchemeManager::lineAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	if (this->isDefinedNameInMainSection(info.token))
		return this->messagePool->nameAlwaysUsed(info);
	else
	{
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeLine(info.token)));
		return 0;
	}
}

int SchemeManager::lineDescriptor(const ParseInfo& info)
{
	this->objects.back()->setDescriptor(this->currentDescriptor);
	return 0;
}

int SchemeManager::lineAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->objects.back()->addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	if (this->currentConditionParam == -1)
	{
		for (const auto& extLink : this->externalLinks)
			if (extLink.getDescriptionTag() == id)
				return 0;
		if (this->descriptions.size() > 1)
			return this->messagePool->conditionParamIsRequired(info);
	}
	return 0;
}

int SchemeManager::lineAddConditionGroup(const ParseInfo& info)
{
	this->objects.back()->addNewConditionGroup();
	return 0;
}

int SchemeManager::lineCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->objects.back()->checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->objects.back()->getLastConditions()), res);
}

int SchemeManager::crossPlacement(const ParseInfo& info)
{
	const auto [res, id] = this->usePlacementParameter(info);
	if (res == 0)
	{
		this->objectPlacement = id;
		this->objectLocation.clear();
		this->objectCable.clear();
		this->objectOrder = -1;
		return 0;
	}
	else
		return this->messagePool->undefinedPlacementName(info);
}

int SchemeManager::crossLocation(const ParseInfo& info)
{
	this->objectLocation = info.token;
	return 0;
}

int SchemeManager::crossOrder(const ParseInfo& info)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi(info.token, &pos);
		if ((pos < info.token.length()) or (res < 0))
			res = -1;
	}
	catch (std::invalid_argument)
	{
		res = -1;
	}
	if (res == -1)
		return this->messagePool->numberExcepted(info);
	else
	{
		this->objectOrder = res;
		return 0;
	}
}

int SchemeManager::crossCable(const ParseInfo& info)
{
	this->objectCable = info.token;
	return 0;
}

int SchemeManager::crossGeneralName(const ParseInfo& info)
{
	this->objectGeneralNameString = this->objectNameString;
	return 0;
}

int SchemeManager::crossAddNew(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	if (this->isDefinedNameInMainSection(info.token))
		return this->messagePool->nameAlwaysUsed(info);
	else
	{
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeCross(info.token)));

		// Çàäàåì ðàçìåùåíèå
		Description::PlacementType pl_type = Description::PlacementType::No;
		for (const auto& desc : this->descriptions)
			if ((pl_type = desc.getPlacementType(this->objectPlacement)) != Description::PlacementType::No)
				break;
		if ((pl_type != Description::PlacementType::No) and (this->objects.back()->setPlacement(this->objectPlacement, pl_type) == 0))
		{
			// Çàäàåì ìåñòî â ðàçìåùåíèè
			if (this->objects.back()->setLocation(this->objectLocation) == 0)
			{
				// Çàäàåì êàáåëü è ïîðÿäîê
				this->objects.back()->setCable(this->objectCable);
				this->objects.back()->setOrder(this->objectOrder);
				return 0;
			}
			else
				return this->messagePool->deviceCantOccupyTheLocation(info);
		}
		else
			return this->messagePool->incompatiblePlacement(info);
	}
}

int SchemeManager::crossName(const ParseInfo& info)
{
	wstring name = this->objectGeneralNameString + this->objectNameString;
	this->objects.back()->addNewObjectName(name);
	return 0;
}

int SchemeManager::crossAddContact(const ParseInfo& info)
{
	switch (this->objects.back()->setContact(info.token))
	{
		case -1:
			return this->messagePool->deviceCantHaveThisContact(info);
		case 1:
			return this->messagePool->incorrectRepeatOfContact(info);
	}
	return 0;
}

int SchemeManager::crossCount(const ParseInfo& info)
{
	size_t pos = 0;
	int res = 0;
	try
	{
		res = std::stoi(info.token, &pos);
		if ((pos < info.token.length()) or (res <= 0))
			res = -1;
	}
	catch (std::invalid_argument)
	{
		res = -1;
	}
	if (res == -1)
		return this->messagePool->numberExcepted(info);
	else
	{
		this->objects.back()->setCount(res);
		return 0;
	}
}

int SchemeManager::crossAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->objects.back()->addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	if (this->currentConditionParam == -1)
	{
		for (const auto& extLink : this->externalLinks)
			if (extLink.getDescriptionTag() == id)
				return 0;
		if (this->descriptions.size() > 1)
			return this->messagePool->conditionParamIsRequired(info);
	}
	return 0;
}

int SchemeManager::crossAddConditionGroup(const ParseInfo& info)
{
	this->objects.back()->addNewConditionGroup();
	return 0;
}

int SchemeManager::crossCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->objects.back()->checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->objects.back()->getLastConditions()), res);
}

int SchemeManager::equipmentAddNew(const ParseInfo& info)
{
	if (!(this->isDefinedNameInMainSection(info.token)))
	{
		this->mainName = info.token;
		return 0;
	}
	else
		return this->messagePool->nameAlwaysUsed(info);
}

int SchemeManager::equipmentSetType(const ParseInfo& info)
{
	SchemeObject* pObject = nullptr;
	bool incorrectType = false;
	const wstring& type = info.token;

	if (type == L"Ïðåäîõðàíèòåëü")
		pObject = new SchemeFuse(this->mainName);

	else if (type == L"ÊÝÃ-1-30Â")
		pObject = new SchemeCapacitor(this->mainName, SchemeCapacitor::Type::KEG_1_30V);
	else if (type == L"ÊÝÃ-2-30Â")
		pObject = new SchemeCapacitor(this->mainName, SchemeCapacitor::Type::KEG_2_30V);
	else if (type == L"ÌÁÃ×-1-1-250Â")
		pObject = new SchemeCapacitor(this->mainName, SchemeCapacitor::Type::MBGCH_1_1_250V);
	else if (type == L"ÌÁÃ×-1-2À-250Â")
		pObject = new SchemeCapacitor(this->mainName, SchemeCapacitor::Type::MBGCH_1_2A_250V);
	else if (type == L"ÝÃÖ-30Â")
		pObject = new SchemeCapacitor(this->mainName, SchemeCapacitor::Type::EGC_30V);

	else if (type == L"Ðåîñòàò")
		pObject = new SchemeRheostat(this->mainName);

	else if (type == L"ÌËÒ-1")
		pObject = new SchemeResistor(this->mainName, SchemeResistor::Type::MLT_1);
	else if (type == L"ÌËÒ-2")
		pObject = new SchemeResistor(this->mainName, SchemeResistor::Type::MLT_2);
	else if (type == L"ÏÝÂ-25")
		pObject = new SchemeResistor(this->mainName, SchemeResistor::Type::PEV_25);
	else if (type == L"ÏÝÂ-50")
		pObject = new SchemeResistor(this->mainName, SchemeResistor::Type::PEV_50);

	else if (type == L"Ä226Á")
		pObject = new SchemeDiode(this->mainName, SchemeDiode::Type::D226B);

	else if (type == L"ÁÂÌØ")
		pObject = new SchemeTimeBlock(this->mainName, SchemeTimeBlock::Type::BVMSH);
	else if (type == L"ÁÂÂ-Ì")
		pObject = new SchemeTimeBlock(this->mainName, SchemeTimeBlock::Type::BVV_M);
	else if (type == L"ÁÂÂ-Ö")
		pObject = new SchemeTimeBlock(this->mainName, SchemeTimeBlock::Type::BVV_C);

	else if (type == L"Èçìåðèòåëüíàÿïàíåëü")
		pObject = new SchemeMeasuringPanel(this->mainName);

	else if (type == L"ÑÒ-4À")
		pObject = new SchemeTransformerSt4(this->mainName, SchemeTransformerSt4::Type::ST4A);
	else if (type == L"ÑÒ-4Ì")
		pObject = new SchemeTransformerSt4(this->mainName, SchemeTransformerSt4::Type::ST4M);
	else if (type == L"ÑÒ-4ÌÏ")
		pObject = new SchemeTransformerSt4(this->mainName, SchemeTransformerSt4::Type::ST4MP);
	else if (type == L"ÑÒ-4Ã")
		pObject = new SchemeTransformerSt4(this->mainName, SchemeTransformerSt4::Type::ST4G);

	else if (type == L"ÑÒ-5À")
		pObject = new SchemeTransformerSt5(this->mainName, SchemeTransformerSt5::Type::ST5A);
	else if (type == L"ÑÒ-5Ì")
		pObject = new SchemeTransformerSt5(this->mainName, SchemeTransformerSt5::Type::ST5M);
	else if (type == L"ÑÒ-5ÌÏ")
		pObject = new SchemeTransformerSt5(this->mainName, SchemeTransformerSt5::Type::ST5MP);
	else if (type == L"ÑÒ-5Ã")
		pObject = new SchemeTransformerSt5(this->mainName, SchemeTransformerSt5::Type::ST5G);

	else if (type == L"ÑÊÒ-1")
		pObject = new SchemeTransformerSkt(this->mainName);

	else
	{
		incorrectType = true;
		pObject = new SchemeIncorrectRelay(this->mainName);
	}

	this->objects.push_back(unique_ptr<SchemeObject>(pObject));
	if (incorrectType)
		return this->messagePool->unknownTypeOfEquipment(this->mainName, type, info);
	else
		return 0;
}

int SchemeManager::equipmentSetNominal(const ParseInfo& info)
{
	switch (this->objects.back()->setNominal(info.token))
	{
		case -1:
			return this->messagePool->deviceCantHaveNominal(info, this->objects.back()->getTypeName());
		case 1:
			return this->messagePool->numberExcepted(info);
	}
	return 0;
}

int SchemeManager::equipmentSetUnit(const ParseInfo& info)
{
	if (this->objects.back()->setUnitOfNominal(info.token) == 0)
		return 0;
	else
		return this->messagePool->deviceCantHaveThisUnit(info, this->objects.back()->getTypeName());
}

int SchemeManager::equipmentSetPowerClass(const ParseInfo& info)
{
	switch (this->objects.back()->setPowerClass(info.token))
	{
		case 1:
			return this->messagePool->incorrectPowerClass(info);
		case -1:
			return this->messagePool->deviceCantHavePowerClass(info, this->objects.back()->getTypeName());
	}
	return 0;
}

int SchemeManager::equipmentSetPlacement(const ParseInfo& info)
{
	const auto [res, id] = this->usePlacementParameter(info);
	if (res == 0)
	{
		this->backupIntVar = id;
		Description::PlacementType pl_type = Description::PlacementType::No;
		for (const auto& desc : this->descriptions)
			if ((pl_type = desc.getPlacementType(id)) != Description::PlacementType::No)
				break;
		if ((pl_type != Description::PlacementType::No) and (this->objects.back()->setPlacement(id, pl_type) == 0))
			return 0;
		else
			return this->messagePool->incompatiblePlacement(info);
	}
	else
		return this->messagePool->undefinedPlacementName(info);
}

int SchemeManager::equipmentSetBlock(const ParseInfo& info)
{
	const auto id = this->getBlockIdByName(info.token);
	if (id == -1)
		return this->messagePool->undefinedPlacementName(info);
	else
	{
		this->backupIntVar = -id - 1;
		if (this->objects.back()->setBlock(id) == 0)
			return 0;
		else
			return this->messagePool->incompatiblePlacement(info);
	}
}

int SchemeManager::equipmentSetLocation(const ParseInfo& info)
{
	const auto count = this->objects.size() - 1;
	const auto block = (this->backupIntVar < 0) ? -this->backupIntVar - 1 : -1;
	const auto placement = (this->backupIntVar >= 0) ? this->backupIntVar : -1;
	for (size_t index = 0; index < count; ++index)
		if (this->objects[index]->checkLocation(block, placement, info.token))
			return this->messagePool->locationStillOccupied(info);
	if (this->objects.back()->setLocation(info.token) == 0)
		return 0;
	else
		return this->messagePool->deviceCantOccupyTheLocation(info);
}

int SchemeManager::equipmentAddObjectName(const ParseInfo& info)
{
	this->objects.back()->addNewObjectName(this->currentString);
	this->currentString.clear();
	return 0;
}

int SchemeManager::equipmentAddJumper(const ParseInfo& info)
{
	switch (this->objects.back()->setJumper(info.token))
	{
		case -1:
			return this->messagePool->deviceCantHaveAnyJumper(info, this->objects.back()->getTypeName());
		case 1:
			return this->messagePool->deviceCantHaveThisJumper(info, this->objects.back()->getTypeName());
		case 2:
			return this->messagePool->incorrectRepeatOfJumper(info);
	}
	return 0;
}

int SchemeManager::equipmentAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->objects.back()->addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	if (this->currentConditionParam == -1)
	{
		for (const auto& extLink : this->externalLinks)
			if (extLink.getDescriptionTag() == id)
				return 0;
		if (this->descriptions.size() > 1)
			return this->messagePool->conditionParamIsRequired(info);
	}
	return 0;
}

int SchemeManager::equipmentAddConditionGroup(const ParseInfo& info)
{
	this->objects.back()->addNewConditionGroup();
	return 0;
}

int SchemeManager::equipmentCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->objects.back()->checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->objects.back()->getLastConditions()), res);
}

int SchemeManager::equipmentFixDescription(const ParseInfo& info)
{
	switch (this->objects.back()->fixDescription())
	{
		case 1:
			return this->messagePool->deviceHasIncompleteSetOfJumpers(info);
		case 2:
			return this->messagePool->deviceHasIncompatibleSetOfJumpers(info);
		case 3:
			return this->messagePool->deviceMustHaveNominal(info, this->objects.back()->getTypeName());
		case 4:
			return this->messagePool->deviceMustHavePowerClass(info, this->objects.back()->getTypeName());
		case 5:
			return this->messagePool->deviceMustHaveObjectName(info, this->objects.back()->getTypeName());
	}
	return 0;
}

int SchemeManager::eventDescriptor(const ParseInfo& info)
{
	this->events.emplace_back();
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			const auto count = this->events.size() - 1;
			for (size_t index = 0; index < count; ++index)
			{
				if (this->events[index].getDescriptor().isFullyEqual(this->currentDescriptor))
				{
					this->currentDescriptor.clear();
					return this->messagePool->incorrectCoincidingDescriptors(info);
				}
			}
			this->events.back().getDescriptor() = this->currentDescriptor;
			this->currentDescriptor.clear();
			return 0;
		}
	}
	for (const auto& extLink : this->externalLinks)
	{
		if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			const auto count = this->events.size() - 1;
			for (size_t index = 0; index < count; ++index)
			{
				if (this->events[index].getDescriptor().isFullyEqual(this->currentDescriptor))
				{
					this->currentDescriptor.clear();
					return this->messagePool->incorrectCoincidingDescriptors(info);
				}
			}
			this->events.back().getDescriptor() = this->currentDescriptor;
			this->currentDescriptor.clear();
			return 0;
		}
	}
	this->currentDescriptor.clear();
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::eventSetStatus(const ParseInfo& info)
{
	const auto id = this->getDeviceIdByName(info.token);
	if (id == -1)
		return this->messagePool->nameWasNotFound(info);
	else
	{
		if (this->objects[id]->getObjectType() == SchemeObject::ObjectType::Status)
		{
			this->events.back().statusSet(id);
			return 0;
		}
		else
			return this->messagePool->nameMustBeTheStatus(info);
	}
}

int SchemeManager::eventResetStatus(const ParseInfo& info)
{
	const auto id = this->getDeviceIdByName(info.token);
	if (id == -1)
		return this->messagePool->nameWasNotFound(info);
	else
	{
		if (this->objects[id]->getObjectType() == SchemeObject::ObjectType::Status)
		{
			this->events.back().statusReset(id);
			return 0;
		}
		else
			return this->messagePool->nameMustBeTheStatus(info);
	}
}

int SchemeManager::eventProbablityClass(const ParseInfo& info)
{
	if (this->events.back().setProbablityClass(info.token) == 0)
		return 0;
	else
		return this->messagePool->incorrectProbablityClass(info);
}

int SchemeManager::eventAddCondition(const ParseInfo& info)
{
	auto [res, id] = this->events.back().addCondition(this->currentConditionParam, info.token);
	switch (res)
	{
		case -1:
			return this->messagePool->incorrectDescriptionTag(info);
		case 1:
			return this->messagePool->incorrectRepeatOfDescriptionTag(info);
	}
	if (this->currentConditionParam == -1)
	{
		for (const auto& extLink : this->externalLinks)
			if (extLink.getDescriptionTag() == id)
				return 0;
		if (this->descriptions.size() > 1)
			return this->messagePool->conditionParamIsRequired(info);
	}
	return 0;
}

int SchemeManager::eventAddConditionGroup(const ParseInfo& info)
{
	this->events.back().addNewConditionGroup();
	return 0;
}

int SchemeManager::eventCheckConditionGroup(const ParseInfo& info)
{
	int res = 0;
	if (this->events.back().checkForEqualConditions())
		res = this->messagePool->differentDescriptionGroupsAreEqual(info);
	return max(this->checkConditions(info, this->events.back().getLastConditions()), res);
}

int SchemeManager::grantRequirementSourceName(const ParseInfo& info)
{
	this->requirementMask.clear();
	this->requirementMask.resize(101, 0);
	const auto cbegin = this->grantingRequirements.cbegin();
	const auto cend = this->grantingRequirements.cend();
	const wstring& name = info.token;
	const auto res = find_if(cbegin, cend, [&name] (const auto& elm) -> bool { return (elm.getName() == name); });
	if (res == cend)
	{
		this->reqId = -1;
		return this->messagePool->incorrectRequirementName(info);
	}
	else
	{
		this->reqId = static_cast<int>(res - cbegin);
		if (this->grantingRequirements[this->reqId].isSourceEnable())
			return this->messagePool->incorrectRepeatOfRequirementName(info);
		else
			return 0;
	}
}

int SchemeManager::grantRequirementAddRequirementName(const ParseInfo& info)
{
	bool ability = false;
	if (this->reqId != -1)
	{
		for (const auto& desc : this->descriptions)
		{
			if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			for (const auto& extLink : this->externalLinks)
			{
				if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
		}
		if (ability and this->currentDescriptor.isGroupDescriptor())
		{
			for (const auto& conn : this->externalConnections)
			{
				ability = false;
				if (conn.getDescriptor().isInclude(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
			if (!ability)
			{
				this->currentDescriptor.clear();
				return this->messagePool->incorrectGroupTagInDescriptor(info);
			}
		}
		if (ability)
		{
			for (const auto& req : this->grantingRequirements)
			{
				if (req.checkRequirementNames(this->currentDescriptor))
				{
					this->currentDescriptor.clear();
					return this->messagePool->incorrectRepeatOfDescriptor(info);
				}
			}
			if (this->grantingRequirements[this->reqId].addRequirementName(this->currentDescriptor) == 0)
			{
				this->currentDescriptor.clear();
				return 0;
			}
			else
			{
				this->currentDescriptor.clear();
				return this->messagePool->incorrectRepeatOfDescriptor(info);
			}
		}
	}
	this->currentDescriptor.clear();
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::grantRequirementCheckOutputDescriptorTemplate(const ParseInfo& info)
{
	bool ability = false;
	if (this->reqId != -1)
	{
		for (const auto& desc : this->descriptions)
		{
			if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			for (const auto& extLink : this->externalLinks)
			{
				if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
		}
		if (ability)
			return 0;
	}
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::grantRequirementSetOutputCount(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		size_t pos = 0;
		int res = 0;
		const wstring& name = info.token;
		try
		{
			res = std::stoi(name, &pos);
			if ((pos < name.length()) || (res < 1))
				res = -1;
		}
		catch (std::invalid_argument)
		{
			res = -1;
		}
		if (res == -1)
			return this->messagePool->numberExcepted(info);
		if (this->grantingRequirements[this->reqId].sourceSetCount(res) == -1)
			return this->messagePool->numberIsOutOfRange(info);
		else
			return 0;
	}
	return 0;
}

int SchemeManager::grantRequirementAddNewRecord(const ParseInfo& info)
{
	if (this->reqId != -1)
		this->grantingRequirements[this->reqId].sourceNewRecord();
	return 0;
}

int SchemeManager::grantRequirementFrom(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		size_t pos = 0;
		int res = 0;
		const wstring& name = info.token;
		try
		{
			res = std::stoi(name, &pos);
			if ((pos < name.length()) || (res < 1))
				res = -1;
		}
		catch (std::invalid_argument)
		{
			res = -1;
		}
		if (res == -1)
			return this->messagePool->numberExcepted(info);
		if (this->grantingRequirements[this->reqId].sourceSetFrom(res) == -1)
			return this->messagePool->numberIsOutOfRange(info);
		else
		{
			this->backupIntVar = res;
			return 0;
		}
	}
	return 0;
}

int SchemeManager::grantRequirementTo(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		size_t pos = 0;
		int res = 0;
		const wstring& name = info.token;
		try
		{
			res = std::stoi(name, &pos);
			if ((pos < name.length()) || (res < 1))
				res = -1;
		}
		catch (std::invalid_argument)
		{
			res = -1;
		}
		if (res == -1)
			return this->messagePool->numberExcepted(info);
		if (this->grantingRequirements[this->reqId].sourceSetTo(res) == -1)
			return this->messagePool->requirementFromIsGreaterThanTo(info);
		else
		{
			if (this->grantingRequirements[this->reqId].getMaxRequesting() < res)
				return this->messagePool->unableToGrantThisRequirement(info);
			bool mark = false;
			for (int index = this->backupIntVar; index <= res; ++index)
			{
				if (this->requirementMask[index] == 1)
					mark = true;
				this->requirementMask[index] = 1;
			}
			return mark ? this->messagePool->moreThanOneRecordForThisNumberOfRequestingRequirement(info) : 0;
		}
	}
	return 0;
}

int SchemeManager::grantRequirementOutput(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		const auto& name = info.token;
		if (this->isDefinedNameInMainSection(name))
			return this->messagePool->nameAlwaysUsed(info);
		this->objects.push_back(unique_ptr<SchemeObject>(new SchemeOutput(name, SchemeOutput::Type::Requirement)));
		if (this->grantingRequirements[this->reqId].sourceAddOutput(static_cast<int>(this->objects.size() - 1)) == 0)
		{
			this->currentDescriptor.replaceFourthTag(name);
			this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::Requirement);
			return 0;
		}
		else
			return this->messagePool->incorrectCountOfOutput(info);
	}
	return 0;
}

int SchemeManager::grantRequirementFixRecord(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		if (this->grantingRequirements[this->reqId].sourceFixRecord() == 0)
			return 0;
		else
			return this->messagePool->incorrectCountOfOutput(info);
	}
	return 0;
}

int SchemeManager::grantRequirementEnd(const ParseInfo& info)
{
	this->currentDescriptor.clear();
	const auto count = this->requirementMask.size();
	bool mark = false;
	for (size_t index = 1; index < count; ++index)
	{
		if (mark and (this->requirementMask[index] == 1))
			return this->messagePool->requirementDoesntCoverWholeRange(info);
		if (this->requirementMask[index] == 0)
			mark = true;
	}
	return 0;
}

int SchemeManager::transmitRequirementRequestedName(const ParseInfo& info)
{
	this->backupIntVar = -1;
	bool ability = false;
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			ability = true;
			break;
		}
	}
	if (!ability)
	{
		for (const auto& extLink : this->externalLinks)
		{
			if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
	}
	if (ability and this->currentDescriptor.isGroupDescriptor())
	{
		for (const auto& conn : this->externalConnections)
		{
			ability = false;
			if (conn.getDescriptor().isInclude(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			this->currentDescriptor.clear();
			return this->messagePool->incorrectGroupTagInDescriptor(info);
		}
	}
	if (ability)
	{
		this->reqId = -1;
		const auto count = this->requestedRequirements.size();
		for (size_t index = 0; index < count; ++index)
		{
			if (this->requestedRequirements[index].getDescriptor().isFullyEqual(this->currentDescriptor))
				this->reqId = static_cast<int>(index);
		}
		if (this->reqId == -1)
		{
			this->requestedRequirements.emplace_back();
			this->requestedRequirements.back().setDescriptor(this->currentDescriptor);
			this->reqId = static_cast<int>(this->requestedRequirements.size() - 1);
		}
		this->currentDescriptor.clear();
		return 0;
	}
	this->currentDescriptor.clear();
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::transmitRequirementAddGrantingName(const ParseInfo& info)
{
	bool ability = false;
	if (this->reqId != -1)
	{
		for (const auto& desc : this->descriptions)
		{
			if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			for (const auto& extLink : this->externalLinks)
			{
				if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
		}
		if (ability and this->currentDescriptor.isGroupDescriptor())
		{
			for (const auto& conn : this->externalConnections)
			{
				ability = false;
				if (conn.getDescriptor().isInclude(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
			if (!ability)
			{
				this->currentDescriptor.clear();
				return this->messagePool->incorrectGroupTagInDescriptor(info);
			}
		}
		if (ability)
		{
			if (this->backupIntVar == -1)
			{
				const auto count = this->grantingRequirements.size();
				for (size_t index = 0; index < count; ++index)
				{
					if (this->grantingRequirements[index].checkRequirementNames(this->currentDescriptor))
					{
						this->currentDescriptor.clear();
						return this->messagePool->incorrectRepeatOfDescriptor(info);
					}
					if (grantingRequirements[index].getLinkedRequestedRequirement() == this->reqId)
						this->backupIntVar = static_cast<int>(index);
				}
				if (this->backupIntVar == -1)
				{
					this->grantingRequirements.emplace_back(this->reqId);
					this->backupIntVar = static_cast<int>(this->grantingRequirements.size() - 1);
				}
			}
			if (this->grantingRequirements[this->backupIntVar].addRequirementName(this->currentDescriptor) == 0)
			{
				this->currentDescriptor.clear();
				this->requestedRequirements[this->reqId].setLinkedGrantingRequirements(this->backupIntVar);
				return 0;
			}
			else
			{
				this->currentDescriptor.clear();
				return this->messagePool->incorrectRepeatOfDescriptor(info);
			}
		}
	}
	this->currentDescriptor.clear();
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::transmitRequirementFix(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::requestedRequirementRequestedName(const ParseInfo& info)
{
	this->backupIntVar = -1;
	bool ability = false;
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			ability = true;
			break;
		}
	}
	if (!ability)
	{
		for (const auto& extLink : this->externalLinks)
		{
			if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
	}
	if (ability and this->currentDescriptor.isGroupDescriptor())
	{
		for (const auto& conn : this->externalConnections)
		{
			ability = false;
			if (conn.getDescriptor().isInclude(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			this->currentDescriptor.clear();
			return this->messagePool->incorrectGroupTagInDescriptor(info);
		}
	}
	if (ability)
	{
		this->reqId = -1;
		const auto count = this->requestedRequirements.size();
		for (size_t index = 0; index < count; ++index)
		{
			if (this->requestedRequirements[index].getDescriptor().isFullyEqual(this->currentDescriptor))
				this->reqId = static_cast<int>(index);
		}
		if (this->reqId == -1)
		{
			this->requestedRequirements.emplace_back();
			this->requestedRequirements.back().setDescriptor(this->currentDescriptor);
			this->reqId = static_cast<int>(this->requestedRequirements.size() - 1);
		}
		this->currentDescriptor.clear();
		this->requestedRequirements[this->reqId].addNewInputGroup();
		return 0;
	}
	this->currentDescriptor.clear();
	return this->messagePool->usingOfIncorrectDescriptor(info);
}

int SchemeManager::requestedRequirementAddInputName(const ParseInfo& info)
{
	if (this->reqId != -1)
	{
		bool ability = false;
		for (const auto& desc : this->descriptions)
		{
			if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			for (const auto& extLink : this->externalLinks)
			{
				if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
		}
		if (ability)
		{
			const auto count = this->inputDescriptors.size();
			size_t index = 0;
			bool mark = false;
			for (index = 0; index < count; ++index)
			{
				if (this->inputDescriptors[index].getDescriptor().isFullyEqual(this->currentDescriptor))
				{
					mark = true;
					break;
				}
			}
			if (!mark)
			{
				this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::FreeInput);
				index = this->inputDescriptors.size() - 1;
			}
			this->requestedRequirements[this->reqId].addNewInput(static_cast<int>(index));
		}
		else
		{
			this->currentDescriptor.clear();
			return this->messagePool->usingOfIncorrectDescriptor(info);
		}
	}
	this->currentDescriptor.clear();
	return 0;
}

int SchemeManager::requestedRequirementAddFakeInput(const ParseInfo& info)
{
	if (this->reqId != -1)
		this->requestedRequirements[this->reqId].addNewFakeInput();
	return 0;
}

int SchemeManager::requestedRequirementFix(const ParseInfo& info)
{
	if ((this->reqId != -1) and (this->requestedRequirements[this->reqId].fixInputGroup() == 0))
		return 0;
	else
		return this->messagePool->wholeInputsInRequestingRequirementAreZero(info);
}

int SchemeManager::transitCircuitTargetOutput(const ParseInfo& info)
{
	// Ñâîáîäíûé âûõîä
	const auto count = this->outputDescriptors.size();
	size_t index = 0;
	for (index = 0; index < count; ++index)
		if (this->outputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeOutputDescriptor::Type::TargetOutput))
			break;
	if (index == count)
		this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::TargetOutput);
	// index
	this->currentDescriptor.clear();
	return 0;
}

int SchemeManager::transitCircuitOutput(const ParseInfo& info)
{
	bool ability = false;
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			ability = true;
			break;
		}
	}
	if (!ability)
	{
		for (const auto& extLink : this->externalLinks)
		{
			if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
	}
	const bool group = this->currentDescriptor.isGroupDescriptor();
	if (ability and group)
	{
		for (const auto& conn : this->externalConnections)
		{
			ability = false;
			if (conn.getDescriptor().isInclude(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			this->currentDescriptor.clear();
			return this->messagePool->incorrectGroupTagInDescriptor(info);
		}
	}
	if (ability)
	{
		if (group)
		{
			// Ãðóïïîâîé âûõîä
			const auto count = this->outputDescriptors.size();
			size_t index = 0;
			for (index = 0; index < count; ++index)
				if (this->outputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput))
					break;
			if (index == count)
				this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput);
			// index
		}
		else
		{
			// Ñâîáîäíûé âûõîä
			const auto count = this->outputDescriptors.size();
			size_t index = 0;
			for (index = 0; index < count; ++index)
				if (this->outputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeOutputDescriptor::Type::Output))
					break;
			if (index == count)
				this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::Output);
			// index
		}
		this->currentDescriptor.clear();
		return 0;
	}
	else
	{
		this->currentDescriptor.clear();
		return this->messagePool->usingOfIncorrectDescriptor(info);
	}
}

int SchemeManager::transitCircuitFreeInput(const ParseInfo& info)
{
	bool ability = false;
	for (const auto& desc : this->descriptions)
	{
		if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
		{
			ability = true;
			break;
		}
	}
	if (!ability)
	{
		for (const auto& extLink : this->externalLinks)
		{
			if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
	}
	if (ability and this->currentDescriptor.isGroupDescriptor())
	{
		for (const auto& conn : this->externalConnections)
		{
			ability = false;
			if (conn.getDescriptor().isInclude(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			this->currentDescriptor.clear();
			return this->messagePool->incorrectGroupTagInDescriptor(info);
		}
	}
	if (ability)
	{
		// Ñâÿçàííûé âõîä
		const auto count = this->inputDescriptors.size();
		size_t index = 0;
		for (index = 0; index < count; ++index)
			if (this->inputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeInputDescriptor::Type::FreeInput))
				break;
		if (index == count)
			this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::FreeInput);
		// index
		this->currentDescriptor.clear();
		return 0;
	}
	else
	{
		this->currentDescriptor.clear();
		return this->messagePool->usingOfIncorrectDescriptor(info);
	}
}

int SchemeManager::transitCircuitInput(const ParseInfo& info)
{
	bool ability = false;
	if (this->currentDescriptor.isGroupDescriptor())
	{
		for (const auto& desc : this->descriptions)
		{
			if (desc.getDescriptor().isEqualForDescription(this->currentDescriptor))
			{
				ability = true;
				break;
			}
		}
		if (!ability)
		{
			for (const auto& extLink : this->externalLinks)
			{
				if (extLink.getDescriptor().isEqualForDescription(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
		}
		if (ability)
		{
			for (const auto& conn : this->externalConnections)
			{
				ability = false;
				if (conn.getDescriptor().isInclude(this->currentDescriptor))
				{
					ability = true;
					break;
				}
			}
			if (!ability)
			{
				this->currentDescriptor.clear();
				return this->messagePool->incorrectGroupTagInDescriptor(info);
			}
		}
		if (ability)
		{
			// Ãðóïïîâîé âõîä
			const auto count = this->inputDescriptors.size();
			size_t index = 0;
			for (index = 0; index < count; ++index)
				if (this->inputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput))
					break;
			if (index == count)
				this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput);
			// index
			this->currentDescriptor.clear();
			return 0;
		}
		else
		{
			this->currentDescriptor.clear();
			return this->messagePool->usingOfIncorrectDescriptor(info);
		}
	}
	else
	{
		// Ñâÿçàííûé âõîä
		const auto count = this->inputDescriptors.size();
		size_t index = 0;
		for (index = 0; index < count; ++index)
			if (this->inputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeInputDescriptor::Type::Input))
				break;
		if (index == count)
			this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::Input);
		// index
		this->currentDescriptor.clear();
		return 0;
	}
}

int SchemeManager::transitCircuitName(const ParseInfo& info)
{
	if (this->externalConnections.size() == 2)
	{
		const auto& name = info.token;

		// Ãðóïïîâîé âõîä
		this->currentDescriptor = this->externalConnections[0].getDescriptor();
		this->currentDescriptor.addTagName(name);
		const auto count = this->inputDescriptors.size();
		size_t index = 0;
		for (index = 0; index < count; ++index)
			if (this->inputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput))
				break;
		if (index == count)
			this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput);
		// index

		// Ãðóïïîâîé âûõîä
		this->currentDescriptor = this->externalConnections[1].getDescriptor();
		this->currentDescriptor.addTagName(name);
		const auto count1 = this->outputDescriptors.size();
		for (index = 0; index < count1; ++index)
			if (this->outputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput))
				break;
		if (index == count1)
			this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput);
		// index


		// Ãðóïïîâîé âõîä
		this->currentDescriptor = this->externalConnections[1].getDescriptor();
		this->currentDescriptor.addTagName(name);
		const auto count2 = this->inputDescriptors.size();
		for (index = 0; index < count2; ++index)
			if (this->inputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput))
				break;
		if (index == count2)
			this->inputDescriptors.emplace_back(this->currentDescriptor, SchemeInputDescriptor::Type::GroupInput);
		// index

		// Ãðóïïîâîé âûõîä
		this->currentDescriptor = this->externalConnections[0].getDescriptor();
		this->currentDescriptor.addTagName(name);
		const auto count3 = this->outputDescriptors.size();
		for (index = 0; index < count3; ++index)
			if (this->outputDescriptors[index].checkDescriptor(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput))
				break;
		if (index == count3)
			this->outputDescriptors.emplace_back(this->currentDescriptor, SchemeOutputDescriptor::Type::GroupOutput);
		// index

		return 0;
	}
	else
		return this->messagePool->unableToUseShortNameTransitCircuit(info);
}

int SchemeManager::transitCircuitAddCondition(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::transitCircuitAddConditionGroup(const ParseInfo& info)
{
	return 0;
}

int SchemeManager::transitCircuitCheckConditionGroup(const ParseInfo& info)
{
	return 0;
}

