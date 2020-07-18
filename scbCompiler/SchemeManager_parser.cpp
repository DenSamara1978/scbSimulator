#include <algorithm>

#include "SchemeManager.h"

using std::max;

int SchemeManager::parse(const ParseInfo& info)
{
	const wstring& token = info.token;
	if (this->submode == 0)
	{
		if (token == L"ПСЕВДОНИМЫ")
		{
			this->mode = 28;
			if (this->level > 1)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 1;
			this->submode = 0;
			return 0;
		}
		else if (token == L"НАСТРОЕЧНЫЕ")
		{
			this->mode = 12;
			if (this->level > 1)
			{
				ParseInfo new_info {info};
				new_info.token = L"НАСТРОЕЧНЫЕ ПАРАМЕТРЫ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 1;
			return 0;
		}
		else if ((token == L"ПАРАМЕТРЫ") and (this->mode == 12))
		{
			this->mode = 13;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ВНЕШНИЕ")
		{
			this->mode = 1;
			return 0;
		}
		else if ((token == L"ССЫЛКИ") and (this->mode == 1))
		{
			this->mode = 3;
			if (this->level > 2)
			{
				ParseInfo new_info {info};
				new_info.token = L"ВНЕШНИЕ ССЫЛКИ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 2;
			this->submode = 0;
			return 0;
		}
		else if ((token == L"СВЯЗИ") and (this->mode == 1))
		{
			this->mode = 2;
			if (this->level > 3)
			{
				ParseInfo new_info {info};
				new_info.token = L"ВНЕШНИЕ СВЯЗИ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 3;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ВНУТРЕННИЕ")
		{
			this->mode = 4;
			if (this->level > 3)
			{
				ParseInfo new_info {info};
				new_info.token = L"ВНУТРЕННИЕ СВЯЗИ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 3;
			return 0;
		}
		else if ((token == L"СВЯЗИ") and (this->mode == 4))
		{
			this->mode = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"БЛОКИ")
		{
			this->mode = 6;
			if (this->level > 4)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 4;
			this->submode = 0;
			return 0;
		}
		else if (token == L"РЕЛЕ")
		{
			this->mode = 7;
			if (this->level > 5)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ОБОРУДОВАНИЕ")
		{
			this->mode = 8;
			if (this->level > 5)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ВСПОМОГАТЕЛЬНЫЕ")
		{
			this->mode = 9;
			if (this->level > 5)
			{
				ParseInfo new_info {info};
				new_info.token = L"ВСПОМОГАТЕЛЬНЫЕ ПЕРЕМЕННЫЕ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 5;
			return 0;
		}
		else if ((token == L"ПЕРЕМЕННЫЕ") && (this->mode == 9))
		{
			this->mode = 10;
			this->submode = 0;
			return 0;
		}
		else if (token == L"СОСТОЯНИЯ")
		{
			this->mode = 11;
			if (this->level > 5)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"СОБЫТИЯ")
		{
			this->mode = 14;
			if (this->level > 6)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 6;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ЗАПРОС")
		{
			this->mode = 29;
			if (this->level > 6)
			{
				ParseInfo new_info {info};
				new_info.token = L"ЗАПРОС ПОТРЕБНОСТЕЙ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 6;
			return 0;
		}
		else if ((token == L"ПОТРЕБНОСТЕЙ") and (this->mode == 29))
		{
			this->mode = 30;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ПЕРЕДАЧА")
		{
			this->mode = 15;
			if (this->level > 6)
			{
				ParseInfo new_info {info};
				new_info.token = L"ПЕРЕДАЧА ПОТРЕБНОСТЕЙ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 6;
			return 0;
		}
		else if ((token == L"ПОТРЕБНОСТЕЙ") and (this->mode == 15))
		{
			this->mode = 16;
			this->submode = 0;
			return 0;
		}
		else if (token == L"УДОВЛЕТВОРЕНИЕ")
		{
			this->mode = 17;
			if (this->level > 6)
			{
				ParseInfo new_info {info};
				new_info.token = L"УДОВЛЕТВОРЕНИЕ ПОТРЕБНОСТЕЙ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 6;
			return 0;
		}
		else if ((token == L"ПОТРЕБНОСТЕЙ") and (this->mode == 17))
		{
			this->mode = 18;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ТРАНЗИТНЫЕ")
		{
			this->mode = 19;
			if (this->level > 7)
			{
				ParseInfo new_info {info};
				new_info.token = L"ТРАНЗИТНЫЕ ЦЕПИ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 7;
			return 0;
		}
		else if ((token == L"ЦЕПИ") and (this->mode == 19))
		{
			this->mode = 20;
			this->submode = 0;
			return 0;
		}
		else if (token == L"КРОСС")
		{
			this->mode = 21;
			if (this->level > 5)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ЛИНИИ")
		{
			this->mode = 27;
			if (this->level > 5)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 5;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ВХОДЫ")
		{
			this->mode = 22;
			if (this->level > 7)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 7;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ВЫХОДЫ")
		{
			this->mode = 23;
			if (this->level > 7)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 7;
			this->submode = 0;
			return 0;
		}
		else if (token == L"РАСЧЕТНЫЕ")
		{
			this->mode = 24;
			if (this->level > 8)
			{
				ParseInfo new_info {info};
				new_info.token = L"РАСЧЕТНЫЕ ЦЕПИ";
				return this->messagePool->incorrectLevelOfBlock(new_info);
			}
			this->level = 8;
			return 0;
		}
		else if ((token == L"ЦЕПИ") and (this->mode == 24))
		{
			this->mode = 25;
			this->submode = 0;
			return 0;
		}
		else if (token == L"ЧУВСТВИТЕЛЬНОСТИ")
		{
			this->mode = 26;
			if (this->level > 8)
				return this->messagePool->incorrectLevelOfBlock(info);
			this->level = 8;
			this->submode = 0;
			return 0;
		}
	}

	int res = 0;
	switch (this->mode)
	{
		case 0:
			res = this->parseScheme(info);
			break;
		case 28:
			res = this->parseAlias(info);
			break;
		case 2:
			res = this->parseExternalConnection(info);
			break;
		case 3:
			res = this->parseExternalLink(info);
			break;
		case 5:
			res = this->parseInternalConnection(info);
			break;
		case 6:
			res = this->parseBlock(info);
			break;
		case 7:
			res = this->parseRelay(info);
			break;
		case 8:
			res = this->parseEquipment(info);
			break;
		case 10:
			res = this->parseVariable(info);
			break;
		case 11:
			res = this->parseStatus(info);
			break;
		case 13:
			res = this->parseTuning(info);
			break;
		case 14:
			res = this->parseEvent(info);
			break;
		case 30:
			res = this->parseRequestRequirement(info);
			break;
		case 16:
			res = this->parseTransmitRequirement(info);
			break;
		case 18:
			res = this->parseGrantRequirement(info);
			break;
		case 20:
			res = this->parseTransitCircuit(info);
			break;
		case 21:
			res = this->parseCross(info);
			break;
		case 22:
			res = this->parseInput(info);
			break;
		case 23:
			res = this->parseOutput(info);
			break;
		case 25:
			res = this->parseWorkingCircuit(info);
			break;
		case 26:
			res = this->parseSensitive(info);
			break;
		case 27:
			res = this->parseLine(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}

	// 0 - можно работать далее
	// 1 - фатальная ошибка
	return res;
}

void SchemeManager::compile()
{

}

void SchemeManager::flushBinFile(const ofstream& file)
{

}

void SchemeManager::flushLogFile(const wofstream& file)
{

}

int SchemeManager::parseScheme(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->schemeAddNew(info);
				res = max(this->tagName(info), res);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
			{
				res = this->tagName(info);
				this->submode = 6;
			}
			break;
		case 3:
			res = this->tagNewDescriptorParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 6;
			else if (token == L"%")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L">")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L".")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			res = this->tagName(info);
			this->submode = 8;
			break;
		case 8:
			if (token == L"{")
			{
				res = this->schemeDescriptor(info);
				this->submode = 11;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			res = this->schemeSetMultiplicator(info);
			this->submode = 10;
			break;
		case 10:
			if (token == L")")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"Размещение")
				this->submode = 12;
			else if (token == L"Блок")
				this->submode = 30;
			else if (token == L"Описание")
			{
				res = this->schemeAddNewDescriptionGroup(info);
				this->submode = 18;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L":")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			res = this->schemeAddNewPlacementName(info);
			this->submode = 14;
			break;
		case 14:
			if (token == L"(")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 16;
			break;
		case 16:
			if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->schemeSetPlacementType(this->backupParseInfo);
				this->submode = 17;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 17:
			if (token == L";")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L":")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 20;
			break;
		case 20:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->schemeAddNewDescriptionTag(this->backupParseInfo);
				res = max(this->schemeCheckDescriptionGroup(info), res);
				this->submode = 34;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->schemeAddNewDescriptionTag(this->backupParseInfo);
				this->submode = 19;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 21:
			// Исключено намеренно
			break;
		case 22:
			// Исключено намеренно
			break;
		case 23:
			// Исключено намеренно
			break;
		case 24:
			// Исключено намеренно
			break;
		case 25:
			// Исключено намеренно
			break;
		case 26:
			// Исключено намеренно
			break;
		case 27:
			// Исключено намеренно
			break;
		case 28:
			// Исключено намеренно
			break;
		case 29:
			// Исключено намеренно
			break;
		case 30:
			if (token == L":")
				this->submode = 31;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			res = this->schemeAddNewBlockName(info);
			this->submode = 32;
			break;
		case 32:
			if (token == L";")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			// Исключено намеренно
			break;
		case 34:
			if (token == L"}")
				this->submode = 35;
			else if (token == L"Блок")
				this->submode = 30;
			else if (token == L"Размещение")
				this->submode = 12;
			else if (token == L"Описание")
			{
				res = this->schemeAddNewDescriptionGroup(info);
				this->submode = 18;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			if (token == L";")
			{
				res = this->schemeMultiplicate(info);
				this->submode = 0;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			if (token == L"{")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			if (token == L">")
				this->submode = 38;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 38:
			if (token == L".")
				this->submode = 39;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 39:
			res = this->tagName(info);
			this->submode = 40;
			break;
		case 40:
			if (token == L"(")
			{
				res = this->schemeDescriptor(info);
				this->submode = 9;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseAlias(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"<")
				this->submode = 1;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 1:
			res = this->aliasAddAlias(info);
			this->submode = 2;
			break;
		case 2:
			if (token == L">")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"=")
				this->submode = 15;
			else if (token == L",")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			if (token == L"<")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			res = this->aliasAddAlias(info);
			this->submode = 6;
			break;
		case 6:
			if (token == L">")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L"=")
				this->submode = 8;
			else if (token == L",")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"Сортировка")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L"(")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			if (token == L"<")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			res = this->aliasSortParam(info);
			this->submode = 12;
			break;
		case 12:
			if (token == L">")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			if (token == L",")
				this->submode = 10;
			else if (token == L")")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L"<")
				this->submode = 17;
			else
			{
				res = this->aliasPreParamString(info);
				this->submode = 16;
			}
			break;
		case 16:
			if (token == L";")
				this->submode = 0;
			else if (token == L"<")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			res = this->aliasParamString(info);
			this->submode = 18;
			break;
		case 18:
			if (token == L">")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L";")
				this->submode = 0;
			else
			{
				res = this->aliasPostParamString(info);
				this->submode = 20;
			}
			break;
		case 20:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseTuning(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"(")
			{
				res = this->tuningAddNew(info);
				res = max(this->tuningCheckDescriptor(info), res);
				this->submode = 9;
			}
			else
			{
				res = this->tuningAddNew(info);
				res = max(this->tagName(info), res);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
			{
				res = this->tagName(info);
				this->submode = 5;
			}
			break;
		case 3:
			res = this->tagParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			res = this->tagName(info);
			this->submode = 7;
			break;
		case 7:
			if (token == L":")
			{
				res = this->tuningDescriptor(info);
				this->submode = 8;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"(")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 10;
			break;
		case 10:
			if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->tuningAddNewDescriptionTag(this->backupParseInfo);
				res = max(this->tuningCheckDescriptionAndTuning(info), res);
				this->submode = 11;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->tuningAddNewDescriptionTag(this->backupParseInfo);
				this->submode = 9;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 11:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseExternalLink(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->externalLinkAddNew(info);
				res = max(this->tagName(info), res);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			res = this->tagNewExternalLinkParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			res = this->tagName(info);
			this->submode = 7;
			break;
		case 7:
			if (token == L"(")
			{
				res = this->externalLinkDescriptor(info);
				this->submode = 8;
			}
			else if (token == L",")
			{
				res = this->externalLinkDescriptor(info);
				this->submode = 13;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 9;
			break;
		case 9:
			if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkDescriptionTag(this->backupParseInfo);
				this->submode = 10;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 10:
			if (token == L";")
				this->submode = 0;
			else if (token == L":")
			{
				res = this->externalLinkAddConditionGroup(info);
				this->submode = 11;
			}
			else if (token == L"{")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"<")
				this->submode = 15;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 12;
			}
			break;
		case 12:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				res = max(this->externalLinkCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->submode = 11;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 13:
			if (token == L"Обязательно")
			{
				res = this->externalLinkNecesserily(info);
				this->submode = 10;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			// Исключен
			break;
		case 15:
			res = this->setConditionParam(info);
			this->submode = 16;
			break;
		case 16:
			if (token == L">")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			if (token == L"(")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 19;
			break;
		case 19:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->submode = 18;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 20;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 20:
			if (token == L";")
			{
				res = this->externalLinkCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L"Условие")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L":")
			{
				res = this->externalLinkAddConditionGroup(info);
				this->submode = 23;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			if (token == L"<")
				this->submode = 25;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 24;
			}
			break;
		case 24:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				res = max(this->externalLinkCheckConditionGroup(info), res);
				this->submode = 31;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->submode = 23;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 25:
			res = this->setConditionParam(info);
			this->submode = 26;
			break;
		case 26:
			if (token == L">")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L"(")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 29;
			break;
		case 29:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->submode = 28;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalLinkAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 30;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 30:
			if (token == L";")
			{
				res = this->externalLinkCheckConditionGroup(info);
				this->submode = 31;
			}
			else if (token == L",")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"Условие")
				this->submode = 22;
			else if (token == L"}")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseExternalConnection(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->externalConnectionAddNew(info);
				res = max(this->tagName(info), res);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			res = this->tagParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"[")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			res = this->tagGroupName(info);
			this->submode = 8;
			break;
		case 8:
			if (token == L"]")
			{
				res = this->externalConnectionDescriptor(info);
				this->submode = 9;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L":")
			{
				res = this->externalConnectionAddConditionGroup(info);
				this->submode = 11;
			}
			else if (token == L";")
				this->submode = 0;
			else if (token == L"{")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			// Пропущен специально
			break;
		case 11:
			if (token == L"<")
				this->submode = 15;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 12;
			}
			break;
		case 12:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				res = max(this->externalConnectionCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->submode = 11;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 13:
		case 14:
			// Пропущены специально
			break;
		case 15:
			res = this->setConditionParam(info);
			this->submode = 16;
			break;
		case 16:
			if (token == L">")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			if (token == L"(")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 19;
			break;
		case 19:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->submode = 18;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 20;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 20:
			if (token == L";")
			{
				res = this->externalConnectionCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L"Условие")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L":")
			{
				res = this->externalConnectionAddConditionGroup(info);
				this->submode = 23;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			if (token == L"<")
				this->submode = 25;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 24;
			}
			break;
		case 24:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				res = max(this->externalConnectionCheckConditionGroup(info), res);
				this->submode = 31;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->submode = 23;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 25:
			res = this->setConditionParam(info);
			this->submode = 26;
			break;
		case 26:
			if (token == L">")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L"(")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 29;
			break;
		case 29:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->submode = 28;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->externalConnectionAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 30;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 30:
			if (token == L";")
			{
				res = this->externalConnectionCheckConditionGroup(info);
				this->submode = 31;
			}
			else if (token == L",")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"Условие")
				this->submode = 22;
			else if (token == L"}")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseInternalConnection(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->internalConnectionAddNew(info);
				res = max(this->tagName(info), res);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			res = this->tagParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"[")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			res = this->tagGroupName(info);
			this->submode = 8;
			break;
		case 8:
			if (token == L"]")
			{
				res = this->internalConnectionFirstDescriptor(info);
				this->submode = 9;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L"-")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			this->currentDescriptor.clear();
			res = this->tagName(info);
			this->submode = 11;
			break;
		case 11:
			if (token == L".")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L"<")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			res = this->tagParamName(info);
			this->submode = 14;
			break;
		case 14:
			if (token == L">")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L".")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			if (token == L"[")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			res = this->tagGroupName(info);
			this->submode = 18;
			break;
		case 18:
			if (token == L"]")
			{
				res = this->internalConnectionSecondDescriptor(info);
				this->submode = 19;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L";")
				this->submode = 0;
			else if (token == L":")
			{
				res = this->internalConnectionAddConditionGroup(info);
				this->submode = 20;
			}
			else if (token == L"{")
				this->submode = 30;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			if (token == L"<")
				this->submode = 22;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 21;
			}
			break;
		case 21:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				res = max(this->internalConnectionCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->submode = 20;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 22:
			res = this->setConditionParam(info);
			this->submode = 25;
			break;
		case 25:
			if (token == L">")
				this->submode = 26;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L"(")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 28;
			break;
		case 28:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->submode = 27;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 29;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 29:
			if (token == L";")
			{
				res = this->internalConnectionCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L"Условие")
				this->submode = 31;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L":")
			{
				res = this->internalConnectionAddConditionGroup(info);
				this->submode = 32;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L"<")
				this->submode = 34;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 33;
			}
			break;
		case 33:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				res = max(this->internalConnectionCheckConditionGroup(info), res);
				this->submode = 40;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->submode = 32;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 34:
			res = this->setConditionParam(info);
			this->submode = 35;
			break;
		case 35:
			if (token == L">")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			if (token == L"(")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 38;
			break;
		case 38:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->submode = 37;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->internalConnectionAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 39;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 39:
			if (token == L";")
			{
				res = this->internalConnectionCheckConditionGroup(info);
				this->submode = 40;
			}
			else if (token == L",")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			if (token == L"Условие")
				this->submode = 31;
			else if (token == L"}")
				this->submode = 41;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 41:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseBlock(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				this->submode = 0;
			else if (token == L"Использование")
				this->submode = 10;
			else
			{
				res = this->blockAddNew(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L",")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"Тип")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"=")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			res = this->blockSetTypeName(info);
			this->submode = 5;
			break;
		case 5:
			if (token == L",")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"Размещение")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L"=")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			res = this->blockSetPlacement(info);
			this->submode = 9;
			break;
		case 9:
			if (token == L",")
				this->submode = 20;
			else if (token == L"{")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			if (token == L"комплектов")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"из")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L"дополнительного")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			if (token == L"блока")
			{
				res = this->extendedBlockAddNew(info);
				this->submode = 14;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			res = this->extendedBlockName(info);
			this->submode = 15;
			break;
		case 15:
			if (token == L":")
				this->submode = 16;
			else if (token == L"{")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			res = this->extendedBlockDefaultCount(info);
			this->submode = 17;
			break;
		case 17:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L"Условие")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L"для")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			if (token == L"Место")
				this->submode = 55;
			else if (token == L"Наименование")
			{
				this->iteration = 0;
				this->submode = 21;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L"=")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 23;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			if (token == L"<")
				this->submode = 25;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 24;
			}
			break;
		case 24:
			if (token == L"<")
				this->submode = 25;
			else if (token == L"\"")
				this->submode = 27;
			else
				res = this->addPatternToObjectName(info);
			break;
		case 25:
			res = this->addParamToObjectName(info);
			this->submode = 26;
			break;
		case 26:
			if (token == L">")
				this->submode = 51;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L";")
			{
				res = this->blockAddObjectName(info);
				res = max(this->blockFixSingleName(info), res);
				this->submode = 0;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			this->iteration = 1;
			if (token == L"Наименование")
				this->submode = 29;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 29:
			if (token == L"=")
				this->submode = 30;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 31;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"<")
				this->submode = 33;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 32;
			}
			break;
		case 32:
			if (token == L"<")
				this->submode = 33;
			else if (token == L"\"")
				this->submode = 49;
			else
				res = this->addPatternToObjectName(info);
			break;
		case 33:
			res = this->addParamToObjectName(info);
			this->submode = 34;
			break;
		case 34:
			if (token == L">")
				this->submode = 53;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			if (token == L"1")
			{
				res = this->extendedBlockAddConditionGroup(info);
				this->submode = 37;
			}
			else if ((token == L"2") or (token == L"3") or (token == L"4") or (token == L"5") or
				(token == L"6") or (token == L"7") or (token == L"8") or (token == L"9") or (token == L"10"))
			{
				res = this->extendedBlockAddConditionGroup(info);
				this->submode = 36;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			if (token == L"комплектов")
				this->submode = 38;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			if (token == L"комплекта")
				this->submode = 38;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 38:
			if (token == L":")
				this->submode = 39;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 39:
			if (token == L"<")
				this->submode = 41;
			else
			{
				this->currentConditionParam = -1;
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 40;
			}
			break;
		case 40:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->extendedBlockAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 39;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->extendedBlockAddCondition(this->backupParseInfo);
				res = max(this->extendedBlockCheckConditionGroup(info), res);
				this->currentConditionParam = -1;
				this->submode = 46;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 41:
			res = this->setConditionParam(info);
			this->submode = 42;
			break;
		case 42:
			if (token == L">")
				this->submode = 43;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 43:
			if (token == L"(")
				this->submode = 44;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 44:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 45;
			break;
		case 45:
			if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->extendedBlockAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 48;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->extendedBlockAddCondition(this->backupParseInfo);
				this->submode = 44;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 46:
			if (token == L"}")
				this->submode = 47;
			else if (token == L"Условие")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 47:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 48:
			if (token == L",")
				this->submode = 39;
			else if (token == L";")
			{
				res = this->extendedBlockCheckConditionGroup(info);
				this->submode = 46;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 49:
			if (token == L";")
			{
				res = this->blockAddObjectName(info);
				this->submode = 54;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 50:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 51:
			if (token == L"<")
				this->submode = 25;
			else if (token == L"\"")
				this->submode = 27;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 24;
			}
			break;
		case 52:
			// Исключено намеренно
			break;
		case 53:
			if (token == L"\"")
				this->submode = 49;
			else if (token == L"<")
				this->submode = 33;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 32;
			}
			break;
		case 54:
			if (token == L"Наименование")
			{
				++ this->iteration;
				this->submode = 29;
			}
			else if (token == L"}")
			{
				res = this->blockFixMultipleNames(info);
				this->submode = 47;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 55:
			if (token == L"=")
				this->submode = 56;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 56:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 57;
			break;
		case 57:
			if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->blockSetLocation(this->backupParseInfo);
				this->submode = 28;
			}
			else if (token == L",")
			{
				this->iteration = 0;
				this->backupParseInfo.token = this->currentString;
				res = this->blockSetLocation(this->backupParseInfo);
				this->submode = 58;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->blockSetLocation(this->backupParseInfo);
				res = max(this->blockFixSingleName(info), res);
				this->submode = 0;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 58:
			if (token == L"Наименование")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseRelay(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"Повторители")
				this->submode = 2;
			else
			{
				res = this->relayAddNew(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L",")
				this->submode = 60;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L",")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"Потребность")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			if (token == L"=")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			res = this->relayRequirementName(info);
			this->submode = 6;
			break;
		case 6:
			if (token == L",")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L"Размещение")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"=")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			res = this->relayRequirementPlacement(info);
			this->submode = 32;
			break;
		case 10:
			if (token == L"Место")
				this->submode = 73;
			else if (token == L"Наименование")
				this->submode = 79;
			else if (token == L"Перемычка")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"=")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 13;
			break;
		case 13:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetTypeName(this->backupParseInfo);
				this->submode = 61;
			}
			else
				this->currentString += token;
			break;
		case 14:
			if (token == L"=")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			res = this->relaySetPlacement(info);
			this->submode = 72;
			break;
		case 16:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				res = max(this->relayFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				this->submode = 66;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 17:
			if (token == L"=")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 16;
			break;
		case 19:
			if (token == L"=")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			res = this->relaySetBlock(info);
			this->submode = 63;
			break;
		case 21:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 22;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L"<")
				this->submode = 24;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 23;
			}
			break;
		case 23:
			if (token == L"<")
				this->submode = 24;
			else if (token == L"\"")
			{
				res = this->relayAddObjectName(info);
				this->submode = 77;
			}
			else
				res = this->addPatternToObjectName(info);
			break;
		case 24:
			res = this->addParamToObjectName(info);
			this->submode = 25;
			break;
		case 25:
			if (token == L">")
				this->submode = 26;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L"\"")
			{
				res = this->relayAddObjectName(info);
				this->submode = 77;
			}
			else if (token == L"<")
				this->submode = 23;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 23;
			}
			break;
		case 27:
			if (token == L"=")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 31;
			break;
		case 29:
			// Исключено намеренно
			break;
		case 30:
			// Исключено намеренно
			break;
		case 31:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				this->submode = 78;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				res = max(this->relayFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				res = max(this->relayAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				this->submode = 88;
			}
			else
				this->currentString += token;
			break;
		case 32:
			if (token == L"{")
				this->submode = 33;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			res = this->relayAddNew(info);
			this->submode = 34;
			break;
		case 34:
			if (token == L",")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			if (token == L"Тип")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			if (token == L"=")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 38;
			break;
		case 38:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetTypeName(this->backupParseInfo);
				res = max(this->relaySetRequirement(info), res);
				this->submode = 39;
			}
			else
				this->currentString += token;
			break;
		case 39:
			if (token == L"Наименование")
				this->submode = 40;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			if (token == L"=")
				this->submode = 41;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 41:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 42;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 42:
			if (token == L"<")
				this->submode = 44;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 43;
			}
			break;
		case 43:
			if (token == L"<")
				this->submode = 44;
			else if (token == L"\"")
			{
				res = this->relayAddObjectName(info);
				this->submode = 47;
			}
			else
				this->currentString += token;
			break;
		case 44:
			res = this->addParamToObjectName(info);
			this->submode = 45;
			break;
		case 45:
			if (token == L">")
				this->submode = 46;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 46:
			if (token == L"<")
				this->submode = 44;
			else if (token == L"\"")
			{
				res = this->relayAddObjectName(info);
				this->submode = 47;
			}
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 43;
			}
			break;
		case 47:
			if (token == L",")
				this->submode = 48;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 48:
			if (token == L"Перемычка")
				this->submode = 58;
			else if (token == L"Потребность")
				this->submode = 51;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 49:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 50;
			break;
		case 50:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				this->submode = 48;
			}
			else
				this->currentString += token;
			break;
		case 51:
			if (token == L"от")
				this->submode = 52;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 52:
			res = this->relaySetRequirementFrom(info);
			this->submode = 53;
			break;
		case 53:
			if (token == L"до")
				this->submode = 54;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 54:
			res = this->relaySetRequirementTo(info);
			this->submode = 55;
			break;
		case 55:
			if (token == L";")
			{
				res = this->relayFixDescription(info);
				this->submode = 56;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 56:
			if (token == L"}")
			{
				res = this->relayFixRequirement(info);
				this->submode = 57;
			}
			else
			{
				res = this->relayAddNew(info);
				this->submode = 34;
			}
			break;
		case 57:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 58:
			if (token == L"=")
				this->submode = 49;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 59:
			// Исключено намеренно
			break;
		case 60:
			if (token == L"Тип")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 61:
			if (token == L"Размещение")
				this->submode = 14;
			else if (token == L"Блок")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 62:
			if (token == L"Место")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 63:
			if (token == L",")
				this->submode = 62;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 64:
			if (token == L"Тип")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 65:
			if (token == L"Размещение")
				this->submode = 38;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 66:
			if (token == L"Перемычка")
				this->submode = 67;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 67:
			if (token == L"=")
				this->submode = 68;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 68:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 71;
			break;
		case 69:
			// Исключено намеренно
			break;
		case 70:
			// Исключено намеренно
			break;
		case 71:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				res = max(this->relayFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddJumper(this->backupParseInfo);
				this->submode = 66;
			}
			else
				this->currentString += token;
			break;
		case 72:
			if (token == L";")
			{
				res = this->relayFixDescription(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 10;
			else if (token == L":")
			{
				res = this->relayAddConditionGroup(info);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 73:
			if (token == L"=")
				this->submode = 74;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 74:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 75;
			break;
		case 75:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				this->submode = 76;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				res = max(this->relayAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				this->submode = 88;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relaySetLocation(this->backupParseInfo);
				res = max(this->relayFixDescription(info), res);
				this->submode = 0;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 76:
			if (token == L"Наименование")
				this->submode = 79;
			else if (token == L"Перемычка")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 77:
			if (token == L",")
				this->submode = 78;
			else if (token == L":")
			{
				res = this->relayAddConditionGroup(info);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			else if (token == L";")
			{
				res = this->relayFixDescription(info);
				this->submode = 0;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 78:
			if (token == L"Перемычка")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 79:
			if (token == L"=")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				res = max(this->relayCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				res = this->relayCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				res = this->relayAddConditionGroup(info);
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				res = max(this->relayCheckConditionGroup(info), res);
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->relayAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				res = this->relayCheckConditionGroup(info);
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
			{
				res = this->relayFixDescription(info);
				this->submode = 99;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseEquipment(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->equipmentAddNew(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L",")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"Тип")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"=")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 5;
			break;
		case 5:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetType(this->backupParseInfo);
				this->submode = 6;
			}
			else
				this->currentString += token;
			break;
		case 6:
			if (token == L"Номинал")
				this->submode = 7;
			else if (token == L"Размещение")
				this->submode = 19;
			else if (token == L"Блок")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L"=")
				this->submode = 8;
			else
				this->currentString += token;
			break;
		case 8:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 9;
			break;
		case 9:
			if ((token == L"А") or (token == L"мкФ") or (token == L"Ом") or (token == L"кОм"))
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetNominal(this->backupParseInfo);
				res = max(this->equipmentSetUnit(info), res);
				this->submode = 12;
			}
			else if (token == L",")
			{
				this->currentString += L",";
				this->submode = 10;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			this->currentString += token;
			this->backupParseInfo.token = this->currentString;
			res = this->equipmentSetNominal(this->backupParseInfo);
			this->submode = 11;
			break;
		case 11:
			if ((token == L"А") or (token == L"мкФ") or (token == L"Ом") or (token == L"кОм"))
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetNominal(this->backupParseInfo);
				res = max(this->equipmentSetUnit(info), res);
				this->submode = 12;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L",")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			if (token == L"Класс")
				this->submode = 14;
			else if (token == L"Размещение")
				this->submode = 19;
			else if (token == L"Блок")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L"питания")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L"=")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			res = this->equipmentSetPowerClass(info);
			this->submode = 17;
			break;
		case 17:
			if (token == L",")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L"Размещение")
				this->submode = 19;
			else if (token == L"Блок")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L"=")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			res = this->equipmentSetPlacement(info);
			this->submode = 21;
			break;
		case 21:
			if (token == L",")
				this->submode = 30;
			else if (token == L";")
			{
				res = this->equipmentFixDescription(info);
				this->submode = 0;
			}
			else if (token == L":")
			{
				res = max(this->equipmentAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L"=")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			res = this->equipmentSetBlock(info);
			this->submode = 24;
			break;
		case 24:
			if (token == L",")
				this->submode = 25;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 25:
			if (token == L"Место")
				this->submode = 26;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L"=")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 28;
			break;
		case 28:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetLocation(this->backupParseInfo);
				this->submode = 29;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetLocation(this->backupParseInfo);
				res = max(this->equipmentFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetLocation(this->backupParseInfo);
				res = max(this->equipmentAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentSetLocation(this->backupParseInfo);
				this->submode = 88;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 29:
			if (token == L"Наименование")
				this->submode = 31;
			else if (token == L"Перемычка")
				this->submode = 40;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L"Наименование")
				this->submode = 31;
			else if (token == L"Перемычка")
				this->submode = 40;
			else if (token == L"Место")
				this->submode = 26;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"=")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 33;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			if (token == L"<")
				this->submode = 35;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 34;
			}
			break;
		case 34:
			if (token == L"<")
				this->submode = 35;
			else if (token == L"\"")
			{
				res = this->equipmentAddObjectName(info);
				this->submode = 38;
			}
			else
				this->currentString += token;
			break;
		case 35:
			res = this->addParamToObjectName(info);
			this->submode = 36;
			break;
		case 36:
			if (token == L">")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			if (token == L"<")
				this->submode = 35;
			else if (token == L"\"")
			{
				res = this->equipmentAddObjectName(info);
				this->submode = 38;
			}
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 34;
			}
			break;
		case 38:
			if (token == L",")
				this->submode = 39;
			else if (token == L";")
			{
				res = this->equipmentFixDescription(info);
				this->submode = 0;
			}
			else if (token == L":")
			{
				res = max(this->equipmentAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 39:
			if (token == L"Перемычка")
				this->submode = 40;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 41;
			break;
		case 41:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddJumper(this->backupParseInfo);
				res = max(this->equipmentFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddJumper(this->backupParseInfo);
				this->submode = 39;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddJumper(this->backupParseInfo);
				res = max(this->equipmentAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddJumper(this->backupParseInfo);
				this->submode = 88;
			}
			else
				this->currentString += token;
			break;



		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				res = max(this->equipmentCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				res = this->equipmentCheckConditionGroup(info);
				res = max(this->equipmentFixDescription(info), res);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				res = this->equipmentAddConditionGroup(info);
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				res = max(this->equipmentCheckConditionGroup(info), res);
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->equipmentAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				res = this->equipmentCheckConditionGroup(info);
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
			{
				res = this->equipmentFixDescription(info);
				this->submode = 99;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseVariable(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->variableAddNew(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseStatus(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				this->submode = 0;
			else
			{
				res = this->statusAddNew(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L";")
				this->submode = 0;
			else if (token == L"=")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"1")
			{
				res = this->statusSetDefaultOne(info);
				this->submode = 3;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseEvent(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->tagName(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
			{
				res = this->tagName(info);
				this->submode = 5;
			}
			break;
		case 3:
			res = this->tagParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			res = this->tagName(info);
			this->submode = 7;
			break;
		case 7:
			if (token == L".")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			res = this->tagName(info);
			res = max(this->eventDescriptor(info), res);
			this->submode = 9;
			break;
		case 9:
			if (token == L"(")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			this->backupParseInfo = info;
			this->submode = 11;
			break;
		case 11:
			if (token == L"=")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L"0")
			{
				res = this->eventResetStatus(this->backupParseInfo);
				this->submode = 13;
			}
			else if (token == L"1")
			{
				res = this->eventSetStatus(this->backupParseInfo);
				this->submode = 13;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			if (token == L",")
				this->submode = 14;
			else if (token == L")")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			this->backupParseInfo = info;
			this->submode = 15;
			break;
		case 15:
			if (token == L"=")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			// Исключено намеренно
			break;
		case 17:
			// Исключено намеренно
			break;
		case 18:
			if (token == L";")
				this->submode = 0;
			else if (token == L":")
			{
				res = this->eventAddConditionGroup(info);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			else if (token == L",")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L"Класс")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			if (token == L"вероятности")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L"=")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 23;
			break;
		case 23:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventProbablityClass(this->backupParseInfo);
				this->submode = 0;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventProbablityClass(this->backupParseInfo);
				res = max(this->eventAddConditionGroup(info), res);
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventProbablityClass(this->backupParseInfo);
				this->submode = 88;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;



		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				res = max(this->eventCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				res = this->eventCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				res = this->eventAddConditionGroup(info);
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				res = max(this->eventCheckConditionGroup(info), res);
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->eventAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				res = this->eventCheckConditionGroup(info);
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
				this->submode = 99;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseRequestRequirement(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"(")
				this->submode = 27;
			else
			{
				res = this->tagName(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			// Исключено намеренно
			break;
		case 4:
			// Исключено намеренно
			break;
		case 5:
			res = this->tagParamName(info);
			this->submode = 6;
			break;
		case 6:
			if (token == L">")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L".")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"[")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			res = this->tagGroupName(info);
			this->submode = 10;
			break;
		case 10:
			if (token == L"]")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L".")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			res = this->tagName(info);
			res = max(this->requestedRequirementRequestedName(info), res);
			this->submode = 13;
			break;
		case 13:
			if (token == L"=")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L">")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L"(")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			if (token == L"0")
			{
				res = this->requestedRequirementAddFakeInput(info);
				this->submode = 25;
			}
			else
			{
				res = this->tagName(info);
				this->submode = 17;
			}
			break;
		case 17:
			if (token == L".")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L"<")
				this->submode = 19;
			else
			{
				res = this->tagName(info);
				this->submode = 21;
			}
			break;
		case 19:
			res = this->tagParamName(info);
			this->submode = 20;
			break;
		case 20:
			if (token == L">")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L".")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			res = this->tagName(info);
			this->submode = 23;
			break;
		case 23:
			if (token == L".")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			res = this->tagName(info);
			res = max(this->requestedRequirementAddInputName(info), res);
			this->submode = 25;
			break;
		case 25:
			if (token == L")")
			{
				res = this->requestedRequirementFix(info);
				this->submode = 26;
			}
			else if (token == L",")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			res = this->tagName(info);
			this->submode = 28;
			break;
		case 28:
			if (token == L".")
				this->submode = 29;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 29:
			if (token == L"<")
				this->submode = 30;
			else
			{
				res = this->tagName(info);
				this->submode = 32;
			}
			break;
		case 30:
			res = this->tagParamName(info);
			this->submode = 31;
			break;
		case 31:
			if (token == L">")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L".")
				this->submode = 33;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			res = this->tagName(info);
			this->submode = 34;
			break;
		case 34:
			if (token == L".")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			res = this->tagName(info);
			res = max(this->requestedRequirementRequestedName(info), res);
			this->submode = 36;
			break;
		case 36:
			if (token == L")")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseTransmitRequirement(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->tagName(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 5;
			else
			{
				res = this->tagName(info);
				this->submode = 3;
			}
			break;
		case 3:
			if (token == L".")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			res = this->tagName(info);
			this->submode = 11;
			break;
		case 5:
			res = this->tagParamName(info);
			this->submode = 6;
			break;
		case 6:
			if (token == L">")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L".")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"[")
				this->submode = 9;
			else
			{
				res = this->tagName(info);
				this->submode = 11;
			}
			break;
		case 9:
			res = this->tagGroupName(info);
			this->submode = 10;
			break;
		case 10:
			if (token == L"]")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L".")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			res = this->tagName(info);
			res = max(this->transmitRequirementRequestedName(info), res);
			this->submode = 13;
			break;
		case 13:
			if (token == L"=")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L">")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L"(")
				this->submode = 29;
			else
			{
				res = this->tagName(info);
				this->submode = 16;
			}
			break;
		case 16:
			if (token == L".")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			if (token == L"<")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			break;
		case 19:
			break;
		case 20:
			res = this->tagParamName(info);
			this->submode = 21;
			break;
		case 21:
			if (token == L">")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L".")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			if (token == L"[")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			res = this->tagGroupName(info);
			this->submode = 25;
			break;
		case 25:
			if (token == L"]")
				this->submode = 26;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L".")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			res = this->tagName(info);
			res = max(this->transmitRequirementAddGrantingName(info), res);
			this->submode = 28;
			break;
		case 28:
			if (token == L";")
			{
				res = this->transmitRequirementFix(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 29:
			res = this->tagName(info);
			this->submode = 30;
			break;
		case 30:
			if (token == L".")
				this->submode = 31;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"<")
				this->submode = 32;
			else
			{
				res = this->tagName(info);
				this->submode = 34;
			}
			break;
		case 32:
			res = this->tagParamName(info);
			this->submode = 33;
			break;
		case 33:
			if (token == L">")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 34:
			if (token == L".")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			res = this->tagName(info);
			this->submode = 36;
			break;
		case 36:
			if (token == L".")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			res = this->tagName(info);
			res = max(this->transmitRequirementAddGrantingName(info), res);
			this->submode = 38;
			break;
		case 38:
			if (token == L")")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseGrantRequirement(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				res = this->grantRequirementSourceName(info);
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L"=")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L">")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"(")
				this->submode = 42;
			else
			{
				res = this->tagName(info);
				this->submode = 4;
			}
			break;
		case 4:
			if (token == L".")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L"<")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			res = this->tagParamName(info);
			this->submode = 7;
			break;
		case 7:
			if (token == L">")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L".")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L"[")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			res = this->tagGroupName(info);
			this->submode = 11;
			break;
		case 11:
			if (token == L"]")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L".")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			res = this->tagName(info);
			res = max(this->grantRequirementAddRequirementName(info), res);
			this->submode = 14;
			break;
		case 14:
			if (token == L":")
				this->submode = 17;
			else if (token == L",")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			// Исключено намеренно
			break;
		case 16:
			// Исключено намеренно
			break;
		case 17:
			res = this->tagName(info);
			this->submode = 18;
			break;
		case 18:
			if (token == L".")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L"<")
				this->submode = 20;
			else
			{
				res = this->tagName(info);
				this->submode = 29;
			}
			break;
		case 20:
			res = this->tagParamName(info);
			this->submode = 21;
			break;
		case 21:
			if (token == L">")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L".")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			res = this->tagName(info);
			this->submode = 26;
			break;
		case 24:
			// Исключено намеренно
			break;
		case 25:
			// Исключено намеренно
			break;
		case 26:
			if (token == L"-")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			res = this->grantRequirementSetOutputCount(info);
			this->submode = 31;
			break;
		case 28:
			// Исключено намеренно
			break;
		case 29:
			if (token == L".")
				this->submode = 30;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			res = this->tagName(info);
			this->submode = 31;
			break;
		case 31:
			if (token == L"{")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			if (token == L"Потребность")
				this->submode = 33;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			if (token == L"от")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 34:
			res = this->grantRequirementAddNewRecord(info);
			res = max(this->grantRequirementFrom(info), res);
			this->submode = 35;
			break;
		case 35:
			if (token == L"до")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			res = this->grantRequirementTo(info);
			this->submode = 37;
			break;
		case 37:
			if (token == L":")
				this->submode = 38;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 38:
			res = this->grantRequirementOutput(info);
			this->submode = 39;
			break;
		case 39:
			if (token == L",")
				this->submode = 38;
			else if (token == L";")
			{
				res = this->grantRequirementFixRecord(info);
				this->submode = 40;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			if (token == L"}")
			{
				res = this->grantRequirementEnd(info);
				this->submode = 41;
			}
			else if (token == L"Потребность")
				this->submode = 33;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 41:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 42:
			res = this->tagName(info);
			this->submode = 43;
			break;
		case 43:
			if (token == L".")
				this->submode = 44;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 44:
			if (token == L"<")
				this->submode = 45;
			else
			{
				res = this->tagName(info);
				this->submode = 47;
			}
			break;
		case 45:
			res = this->tagParamName(info);
			this->submode = 46;
			break;
		case 46:
			if (token == L">")
				this->submode = 47;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 47:
			if (token == L".")
				this->submode = 48;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 48:
			res = this->tagName(info);
			this->submode = 49;
			break;
		case 49:
			if (token == L".")
				this->submode = 50;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 50:
			res = this->tagName(info);
			res = max(this->grantRequirementAddRequirementName(info), res);
			this->submode = 51;
			break;
		case 51:
			if (token == L")")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseTransitCircuit(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"{")
				this->submode = 11;
			else
			{
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L";")
			{
				this->backupParseInfo.token = token;
				res = this->transitCircuitName(this->backupParseInfo);
				this->currentDescriptor.clear();
				this->submode = 0;
			}
			else if (token == L":")
			{
				this->backupParseInfo.token = token;
				res = this->transitCircuitName(this->backupParseInfo);
				this->currentDescriptor.clear();
				this->submode = 80;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = token;
				res = this->transitCircuitName(this->backupParseInfo);
				this->currentDescriptor.clear();
				this->submode = 88;
			}
			else if (token == L".")
			{
				res = this->tagName(this->backupParseInfo);
				this->submode = 2;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			res = this->tagParamName(info);
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"[")
				this->submode = 7;
			else
			{
				res = this->tagName(info);
				this->submode = 9;
			}
			break;
		case 7:
			res = this->tagGroupName(info);
			this->submode = 8;
			break;
		case 8:
			if (token == L"]")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L".")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			res = this->tagName(info);
			res = max(this->transitCircuitOutput(info), res);
			this->submode = 23;
			break;
		case 11:
			res = this->tagName(info);
			this->submode = 12;
			break;
		case 12:
			if (token == L".")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			if (token == L"<")
				this->submode = 14;
			else
			{
				res = this->tagName(info);
				this->submode = 20;
			}
			break;
		case 14:
			res = this->tagParamName(info);
			this->submode = 15;
			break;
		case 15:
			if (token == L">")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			if (token == L".")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			res = this->tagName(info);
			this->submode = 18;
			break;
		case 18:
			if (token == L".")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			res = this->tagName(info);
			this->submode = 22;
			break;
		case 20:
			if (token == L".")
				this->submode = 17;
			else if (token == L"<")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			res = this->tagParamName(info);
			this->submode = 51;
			break;
		case 22:
			if (token == L"}")
			{
				res = this->transitCircuitTargetOutput(info);
				this->submode = 23;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 23:
			if (token == L"<")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			if (token == L"=")
				this->submode = 25;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 25:
			if (token == L"(")
				this->submode = 38;
			else
			{
				res = this->tagName(info);
				this->submode = 26;
			}
			break;
		case 26:
			if (token == L".")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L"<")
				this->submode = 28;
			else
			{
				res = this->tagName(info);
				this->submode = 30;
			}
			break;
		case 28:
			res = this->tagParamName(info);
			this->submode = 29;
			break;
		case 29:
			if (token == L">")
				this->submode = 49;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L".")
				this->submode = 31;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			if (token == L"<")
				this->submode = 32;
			else
			{
				res = this->tagName(info);
				this->submode = 36;
			}
			break;
		case 32:
			res = this->tagParamName(info);
			this->submode = 33;
			break;
		case 33:
			if (token == L">")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 34:
			if (token == L"[")
				this->submode = 35;
			else
			{
				res = this->tagName(info);
				this->submode = 36;
			}
			break;
		case 35:
			res = this->tagGroupName(info);
			this->submode = 50;
			break;
		case 36:
			if (token == L".")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 37:
			res = this->tagName(info);
			res = max(this->transitCircuitInput(info), res);
			this->submode = 48;
			break;
		case 38:
			res = this->tagName(info);
			this->submode = 39;
			break;
		case 39:
			if (token == L".")
				this->submode = 40;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			if (token == L"<")
				this->submode = 41;
			else
			{
				res = this->tagName(info);
				this->submode = 43;
			}
			break;
		case 41:
			res = this->tagParamName(info);
			this->submode = 42;
			break;
		case 42:
			if (token == L">")
				this->submode = 43;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 43:
			if (token == L".")
				this->submode = 44;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 44:
			res = this->tagName(info);
			this->submode = 45;
			break;
		case 45:
			if (token == L".")
				this->submode = 46;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 46:
			res = this->tagName(info);
			res = max(this->transitCircuitFreeInput(info), res);
			this->submode = 47;
			break;
		case 47:
			if (token == L")")
				this->submode = 48;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 48:
			if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 49:
			if (token == L".")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 50:
			if (token == L"]")
				this->submode = 36;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 51:
			if (token == L">")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				res = max(this->transitCircuitCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				res = this->transitCircuitCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				res = this->transitCircuitAddConditionGroup(info);
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				res = max(this->transitCircuitCheckConditionGroup(info), res);
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->transitCircuitAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				res = this->transitCircuitCheckConditionGroup(info);
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
				this->submode = 99;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseCross(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"Размещение")
				this->submode = 1;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 1:
			if (token == L"=")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			res = this->crossPlacement(info);
			this->submode = 13;
			break;
		case 3:
			if (token == L"=")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			res = this->tagName(info);
			this->submode = 5;
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"<")
				this->submode = 7;
			else
			{
				res = this->tagName(info);
				this->submode = 9;
			}
			break;
		case 7:
			res = this->tagParamName(info);
			this->submode = 8;
			break;
		case 8:
			if (token == L">")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L".")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			res = this->tagName(info);
			this->submode = 76;
			break;
		case 11:
			if (token == L"=")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			res = this->crossCable(info);
			this->submode = 73;
			break;
		case 13:
			if (token == L",")
				this->submode = 14;
			else if (token == L"{")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L"Место")
				this->submode = 58;
			//		else if ( token == L"Объект" )
			//			this->submode = 3;
			else if (token == L"Порядок")
				this->submode = 78;
			else if (token == L"Кабель")
				this->submode = 11;
			else if (token == L"Общее")
				this->submode = 83;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			res = this->crossAddNew(info);
			this->submode = 16;
			break;
		case 16:
			if (token == L",")
				this->submode = 17;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 17:
			if (token == L"Наименование")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L"=")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 20;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			if (token == L"<")
				this->submode = 22;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 21;
			}
			break;
		case 21:
			if (token == L"<")
				this->submode = 22;
			else if (token == L"\"")
			{
				res = this->crossName(info);
				this->submode = 25;
			}
			else
				res = this->addPatternToObjectName(info);
			break;
		case 22:
			this->addParamToObjectName(info);
			this->submode = 23;
			break;
		case 23:
			if (token == L">")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			if (token == L"<")
				this->submode = 22;
			else if (token == L"\"")
			{
				res = this->crossName(info);
				this->submode = 25;
			}
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 21;
			}
			break;
		case 25:
			if (token == L",")
				this->submode = 26;
			else if (token == L";")
				this->submode = 34;
			else if (token == L":")
				this->submode = 36;
			else if (token == L"{")
				this->submode = 45;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L"Контакт")
				this->submode = 27;
			else if (token == L"Количество")
				this->submode = 31;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L"=")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			res = this->crossAddContact(info);
			this->submode = 29;
			break;
		case 29:
			if (token == L":")
				this->submode = 36;
			else if (token == L"{")
				this->submode = 45;
			else if (token == L";")
				this->submode = 34;
			else if (token == L",")
				this->submode = 30;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L"Количество")
				this->submode = 31;
			else
			{
				res = this->crossAddContact(info);
				this->submode = 29;
			}
			break;
		case 31:
			if (token == L"=")
				this->submode = 32;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 32:
			res = this->crossCount(info);
			this->submode = 33;
			break;
		case 33:
			if (token == L":")
				this->submode = 36;
			else if (token == L"{")
				this->submode = 45;
			else if (token == L";")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 34:
			if (token == L"}")
				this->submode = 35;
			else
			{
				res = this->crossAddNew(info);
				this->submode = 16;
			}
			break;
		case 35:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 36:
			res = this->crossAddConditionGroup(info);
			if (token == L"<")
				this->submode = 38;
			else
			{
				res = max(this->resetConditionParam(info), res);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 37;
			}
			break;
		case 37:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				this->submode = 36;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				res = max(this->crossCheckConditionGroup(info), res);
				this->currentConditionParam = -1;
				this->submode = 34;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 38:
			res = this->setConditionParam(info);
			this->submode = 39;
			break;
		case 39:
			if (token == L">")
				this->submode = 40;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 40:
			if (token == L"(")
				this->submode = 41;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 41:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 42;
			break;
		case 42:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				this->submode = 41;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 44;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 43:
			// Исключено намеренно
			break;
		case 44:
			if (token == L",")
				this->submode = 36;
			else if (token == L";")
			{
				res = this->crossCheckConditionGroup(info);
				this->submode = 34;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 45:
			if (token == L"Условие")
				this->submode = 46;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 46:
			if (token == L":")
			{
				res = this->crossAddConditionGroup(info);
				this->submode = 47;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 47:
			if (token == L"<")
				this->submode = 49;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 48;
			}
			break;
		case 48:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				this->submode = 47;
			}
			else if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				res = max(this->crossCheckConditionGroup(info), res);
				this->currentConditionParam = -1;
				this->submode = 54;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 49:
			res = this->setConditionParam(info);
			this->submode = 50;
			break;
		case 50:
			if (token == L">")
				this->submode = 51;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 51:
			if (token == L"(")
				this->submode = 52;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 52:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 53;
			break;
		case 53:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				this->submode = 52;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossAddCondition(this->backupParseInfo);
				res = max(this->crossCheckConditionGroup(info), res);
				this->currentConditionParam = -1;
				this->submode = 55;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 54:
			if (token == L"Условие")
				this->submode = 46;
			else if (token == L"}")
				this->submode = 56;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 55:
			if (token == L",")
				this->submode = 47;
			else if (token == L";")
				this->submode = 54;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 56:
			if (token == L";")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 57:
			// Исключено намеренно
			break;
		case 58:
			if (token == L"=")
				this->submode = 59;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 59:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 74;
			break;
		case 60:
			// Исключено намеренно
			break;
		case 61:
			// Исключено намеренно
			break;
		case 62:
			// Исключено намеренно
			break;
		case 63:
			// Исключено намеренно
			break;
		case 64:
			// Исключено намеренно
			break;
		case 65:
			// Исключено намеренно
			break;
		case 66:
			// Исключено намеренно
			break;
		case 67:
			// Исключено намеренно
			break;
		case 68:
			// Исключено намеренно
			break;
		case 69:
			// Исключено намеренно
			break;
		case 70:
			// Исключено намеренно
			break;
		case 71:
			// Исключено намеренно
			break;
		case 72:
			// Исключено намеренно
			break;
		case 73:
			if (token == L",")
				this->submode = 82;
			else if (token == L"{")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 74:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossLocation(this->backupParseInfo);
				this->submode = 75;
			}
			else if (token == L"{")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->crossLocation(this->backupParseInfo);
				this->submode = 15;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 75:
			//        if ( token == L"Объект" )
			  //          this->submode = 3;
			if (token == L"Порядок")
				this->submode = 78;
			else if (token == L"Кабель")
				this->submode = 11;
			else if (token == L"Общее")
				this->submode = 83;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 76:
			if (token == L",")
				this->submode = 77;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 77:
			if (token == L"Порядок")
				this->submode = 78;
			else if (token == L"Кабель")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 78:
			if (token == L"=")
				this->submode = 79;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 79:
			res = this->crossOrder(info);
			this->submode = 80;
			break;
		case 80:
			if (token == L",")
				this->submode = 81;
			else if (token == L"{")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 81:
			if (token == L"Кабель")
				this->submode = 11;
			else if (token == L"Общее")
				this->submode = 83;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 82:
			if (token == L"Общее")
				this->submode = 83;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 83:
			if (token == L"наименование")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"=")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			if (token == L"\"")
			{
				res = this->clearObjectName();
				this->submode = 86;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 86:
			if (token == L"<")
				this->submode = 88;
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 87;
			}
			break;
		case 87:
			if (token == L"<")
			{
				this->submode = 88;
			}
			else if (token == L"\"")
			{
				res = this->crossGeneralName(info);
				this->submode = 91;
			}
			else
				res = this->addPatternToObjectName(info);
			break;
		case 88:
			res = this->addParamToObjectName(info);
			this->submode = 89;
			break;
		case 89:
			if (token == L">")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 88;
			else if (token == L"\"")
			{
				res = this->crossGeneralName(info);
				this->submode = 91;
			}
			else
			{
				res = this->addPatternToObjectName(info);
				this->submode = 87;
			}
			break;
		case 91:
			if (token == L"{")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseInput(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				// TODO
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L"<")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"=")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"0")
				this->submode = 4;
			else if (token == L"1")
				this->submode = 4;
			else if (token == L"(")
				this->submode = 16;
			else
			{
				// TODO
				this->submode = 5;
			}
			break;
		case 4:
			if (token == L";")
			{
				// TODO
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 60;
			else if (token == L"{")
				this->submode = 68;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 37;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			// TODO
			this->submode = 7;
			break;
		case 7:
			if (token == L">")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L".")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L"<")
				this->submode = 12;
			else
			{
				// TODO
				this->submode = 14;
			}
			break;
		case 10:
			if (token == L".")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"[")
				this->submode = 40;
			else
			{
				// TODO
				this->submode = 14;
			}
			break;
		case 12:
			// TODO
			this->submode = 13;
			break;
		case 13:
			if (token == L">")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 14:
			if (token == L".")
				this->submode = 15;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			// TODO
			this->submode = 29;
			break;
		case 16:
			// TODO
			this->submode = 17;
			break;
		case 17:
			if (token == L".")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 18:
			if (token == L"<")
				this->submode = 19;
			else
			{
				// TODO
				this->submode = 21;
			}
			break;
		case 19:
			// TODO
			this->submode = 20;
			break;
		case 20:
			if (token == L">")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L".")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			// TODO
			this->submode = 23;
			break;
		case 23:
			if (token == L".")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			// TODO
			this->submode = 25;
			break;
		case 25:
			if (token == L")")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L"Обязательно")
				this->submode = 27;
			else if (token == L"Шина")
				this->submode = 27;
			else if (token == L"Цепочка")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L",")
				this->submode = 26;
			else if (token == L";")
			{
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			if (token == L";")
			{
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 29:
			if (token == L",")
				this->submode = 30;
			else if (token == L";")
			{
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			if (token == L"Необязательно")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 31:
			break;
		case 32:
			break;
		case 33:
			break;
		case 34:
			break;
		case 35:
			break;
		case 36:
			break;
		case 37:
			if (token == L"<")
				this->submode = 6;
			else
			{
				// TODO
				this->submode = 8;
			}
			break;
		case 38:
			break;
		case 39:
			break;
		case 40:
			// TODO
			this->submode = 41;
			break;
		case 41:
			if (token == L"]")
				this->submode = 14;
			else
				res = this->messagePool->syntaxError(info);
			break;





		case 60:
			if (token == L"<")
				this->submode = 62;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 61;
			}
			break;
		case 61:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 60;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 62:
			res = this->setConditionParam(info);
			this->submode = 63;
			break;
		case 63:
			if (token == L">")
				this->submode = 64;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 64:
			if (token == L"(")
				this->submode = 65;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 65:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 66;
			break;
		case 66:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 65;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 67;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 67:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				//res = max ( this->equipmentFixDescription ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 60;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 68:
			if (token == L"Условие")
				this->submode = 69;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 69:
			if (token == L":")
			{
				//res = this->equipmentAddConditionGroup ( info );
				this->submode = 70;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 70:
			if (token == L"<")
				this->submode = 72;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 71;
			}
			break;
		case 71:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 78;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 70;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 72:
			res = this->setConditionParam(info);
			this->submode = 73;
			break;
		case 73:
			if (token == L">")
				this->submode = 74;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 74:
			if (token == L"(")
				this->submode = 75;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 75:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 76;
			break;
		case 76:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 75;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 77;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 77:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				this->submode = 78;
			}
			else if (token == L",")
				this->submode = 70;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 78:
			if (token == L"Условие")
				this->submode = 69;
			else if (token == L"}")
			{
				//res = this->equipmentFixDescription ( info );
				this->submode = 79;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 79:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 80:
			if (token == L"<")
				this->submode = 82;
			else if (token == L"Питание")
				this->submode = 100;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				//res = max ( this->equipmentFixDescription ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				//res = this->equipmentAddConditionGroup ( info );
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
			{
				//res = this->equipmentFixDescription ( info );
				this->submode = 99;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 100:
			if (token == L"=")
				this->submode = 101;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 101:
			// TODO
			this->submode = 102;
			break;
		case 102:
			if (token == L"(")
				this->submode = 103;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 103:
			// TODO
			this->submode = 104;
			break;
		case 104:
			// TODO
			this->submode = 105;
			break;
		case 105:
			if (token == L",")
				this->submode = 104;
			else if (token == L")")
				this->submode = 87;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseOutput(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"0")
			{
				// TODO
				this->submode = 1;
			}
			else if (token == L"1")
			{
				// TODO
				this->submode = 1;
			}
			else
			{
				// TODO
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L"=")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L">")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"{")
				this->submode = 14;
			else
			{
				// TODO
				this->submode = 4;
			}
			break;
		case 4:
			if (token == L".")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L"<")
				this->submode = 6;
			else
			{
				// TODO
				this->submode = 29;
			}
			break;
		case 6:
			// TODO
			this->submode = 7;
			break;
		case 7:
			if (token == L">")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L".")
				this->submode = 9;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L"[")
				this->submode = 10;
			else
			{
				// TODO
				this->submode = 12;
			}
			break;
		case 10:
			// TODO
			this->submode = 11;
			break;
		case 11:
			if (token == L"]")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			if (token == L".")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			// TODO
			this->submode = 26;
			break;
		case 14:
			// TODO
			this->submode = 15;
			break;
		case 15:
			if (token == L".")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			if (token == L"<")
				this->submode = 17;
			else
			{
				// TODO
				this->submode = 21;
			}
			break;
		case 17:
			// TODO
			this->submode = 18;
			break;
		case 18:
			if (token == L">")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			if (token == L".")
				this->submode = 20;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 20:
			// TODO
			this->submode = 23;
			break;
		case 21:
			if (token == L".")
				this->submode = 22;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L"<")
				this->submode = 31;
			else
			{
				// TODO
				this->submode = 23;
			}
			break;
		case 23:
			if (token == L".")
				this->submode = 24;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 24:
			// TODO
			this->submode = 25;
			break;
		case 25:
			if (token == L"}")
				this->submode = 33;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 26:
			if (token == L";")
			{
				// TODO
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else if (token == L",")
				this->submode = 27;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 27:
			if (token == L"Обязательно")
				this->submode = 28;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 28:
			if (token == L";")
			{
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 29:
			if (token == L".")
				this->submode = 30;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 30:
			// TODO
			this->submode = 12;
			break;
		case 31:
			// TODO
			this->submode = 32;
			break;
		case 32:
			if (token == L">")
				this->submode = 23;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 33:
			if (token == L";")
			{
				// TODO
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else if (token == L",")
				this->submode = 34;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 34:
			if (token == L"Необязательно")
				this->submode = 35;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 35:
			if (token == L";")
			{
				// TODO
				this->submode = 0;
			}
			else if (token == L":")
				this->submode = 80;
			else if (token == L"{")
				this->submode = 88;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				//res = max ( this->equipmentFixDescription ( info ), res );
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				//res = this->equipmentAddConditionGroup ( info );
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				//res = max ( this->equipmentCheckConditionGroup ( info ), res );
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				//res = this->equipmentAddCondition ( this->backupParseInfo );
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				//res = this->equipmentCheckConditionGroup ( info );
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
			{
				//res = this->equipmentFixDescription ( info );
				this->submode = 99;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseWorkingCircuit(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				// TODO
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L"=")
				this->submode = 2;
			else if (token == L"@")
				this->submode = 13;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"0")
				this->submode = 3;
			else if (token == L"1")
				this->submode = 3;
			else if (token == L"(")
				this->submode = 8;
			else if (token == L"!")
				this->submode = 7;
			else
			{
				// TODO
				this->submode = 10;
			}
			break;
		case 3:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			if (token == L"=")
				this->submode = 6;
			else if (token == L"+")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L"=")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			if (token == L"(")
				this->submode = 8;
			else if (token == L"!")
				this->submode = 7;
			else
			{
				// TODO
				this->submode = 10;
			}
			break;
		case 7:
			// TODO
			this->submode = 10;
			break;
		case 8:
			// TODO
			this->submode = 9;
			break;
		case 9:
			if (token == L")")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			if (token == L"&")
				this->submode = 6;
			else if (token == L";")
				this->submode = 0;
			else if (token == L".")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			// TODO
			this->submode = 12;
			break;
		case 12:
			if (token == L"&")
				this->submode = 6;
			else if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 13:
			// TODO
			this->submode = 4;
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseSensitive(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"(")
				this->submode = 1;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 1:
			// TODO
			this->submode = 2;
			break;
		case 2:
			if (token == L")")
				this->submode = 3;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 3:
			if (token == L"=")
				this->submode = 5;
			else if (token == L",")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			if (token == L"(")
				this->submode = 1;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L"(")
				this->submode = 9;
			else if (token == L"!")
				this->submode = 6;
			else
			{
				// TODO
				this->submode = 7;
			}
			break;
		case 6:
			// TODO
			this->submode = 7;
			break;
		case 7:
			if (token == L".")
				this->submode = 8;
			else if (token == L"&")
				this->submode = 5;
			else if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			// TODO
			this->submode = 11;
			break;
		case 9:
			// TODO
			this->submode = 10;
			break;
		case 10:
			if (token == L")")
				this->submode = 11;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 11:
			if (token == L"&")
				this->submode = 5;
			else if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

int SchemeManager::parseLine(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else if (token == L"Объект")
				this->submode = 1;
			break;
		case 1:
			if (token == L"=")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			res = this->tagName(info);
			this->submode = 3;
			break;
		case 3:
			if (token == L".")
				this->submode = 4;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 4:
			if (token == L"<")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			res = this->tagParamName(info);
			this->submode = 6;
			break;
		case 6:
			if (token == L">")
				this->submode = 7;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 7:
			if (token == L".")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			res = this->tagName(info);
			res = max(this->lineDescriptor(info), res);
			this->submode = 9;
			break;
		case 9:
			if (token == L"{")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			res = this->lineAddNew(info);
			res = max(this->lineDescriptor(info), res);
			this->submode = 11;
			break;
		case 11:
			if (token == L";")
				this->submode = 12;
			else if (token == L":")
			{
				res = this->lineAddConditionGroup(info);
				this->submode = 80;
			}
			else if (token == L"{")
				this->submode = 88;
			break;
		case 12:
			if (token == L"}")
			{
				this->currentDescriptor.clear();
				this->submode = 13;
			}
			else
			{
				res = this->lineAddNew(info);
				res = max(this->lineDescriptor(info), res);
				this->submode = 11;
			}
			break;
		case 13:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;

		case 80:
			if (token == L"<")
				this->submode = 82;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 81;
			}
			break;
		case 81:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				res = max(this->lineCheckConditionGroup(info), res);
				this->submode = 0;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->submode = 80;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 82:
			res = this->setConditionParam(info);
			this->submode = 83;
			break;
		case 83:
			if (token == L">")
				this->submode = 84;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 84:
			if (token == L"(")
				this->submode = 85;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 85:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 86;
			break;
		case 86:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->submode = 85;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 87;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 87:
			if (token == L";")
			{
				res = this->lineCheckConditionGroup(info);
				this->submode = 0;
			}
			else if (token == L",")
				this->submode = 80;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 88:
			if (token == L"Условие")
				this->submode = 89;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 89:
			if (token == L":")
			{
				res = this->lineAddConditionGroup(info);
				this->submode = 90;
			}
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 90:
			if (token == L"<")
				this->submode = 92;
			else
			{
				res = this->resetConditionParam(info);
				this->backupParseInfo = info;
				this->currentString = token;
				this->submode = 91;
			}
			break;
		case 91:
			if (token == L";")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				res = max(this->lineCheckConditionGroup(info), res);
				this->submode = 98;
			}
			else if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->submode = 90;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 92:
			res = this->setConditionParam(info);
			this->submode = 93;
			break;
		case 93:
			if (token == L">")
				this->submode = 94;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 94:
			if (token == L"(")
				this->submode = 95;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 95:
			this->backupParseInfo = info;
			this->currentString = token;
			this->submode = 96;
			break;
		case 96:
			if (token == L",")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->submode = 95;
			}
			else if (token == L")")
			{
				this->backupParseInfo.token = this->currentString;
				res = this->lineAddCondition(this->backupParseInfo);
				this->currentConditionParam = -1;
				this->submode = 97;
			}
			else
			{
				this->currentString += L" ";
				this->currentString += token;
			}
			break;
		case 97:
			if (token == L";")
			{
				res = this->lineCheckConditionGroup(info);
				this->submode = 98;
			}
			else if (token == L",")
				this->submode = 90;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 98:
			if (token == L"Условие")
				this->submode = 89;
			else if (token == L"}")
				this->submode = 99;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 99:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}
