#include <algorithm>

#include "scbSchemeManager.h"

using std::max;

int scbSchemeManager::Parse ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	if ( this->m_Submode == 0 )
	{
		if ( token == L"ПСЕВДОНИМЫ" )
		{
			this->m_Mode = 28;
			if ( this->m_Level > 1 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 1;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"НАСТРОЕЧНЫЕ" )
		{
			this->m_Mode = 12;
			if ( this->m_Level > 1 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"НАСТРОЕЧНЫЕ ПАРАМЕТРЫ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 1;
			return 0;
		}
		else if ( ( token == L"ПАРАМЕТРЫ" ) && ( this->m_Mode == 12 ) )
		{
			this->m_Mode = 13;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВНЕШНИЕ" )
		{
			this->m_Mode = 1;
			return 0;
		}
		else if ( ( token == L"ССЫЛКИ" ) && ( this->m_Mode == 1 ) )
		{
			this->m_Mode = 3;
			if ( this->m_Level > 2 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ВНЕШНИЕ ССЫЛКИ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 2;
			this->m_Submode = 0;
			return 0;
		}
		else if ( ( token == L"СВЯЗИ" ) && ( this->m_Mode == 1 ) )
		{
			this->m_Mode = 2;
			if ( this->m_Level > 3 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ВНЕШНИЕ СВЯЗИ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 3;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВНУТРЕННИЕ" )
		{
			this->m_Mode = 4;
			if ( this->m_Level > 3 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ВНУТРЕННИЕ СВЯЗИ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 3;
			return 0;
		}
		else if ( ( token == L"СВЯЗИ" ) && ( this->m_Mode == 4 ) )
		{
			this->m_Mode = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"БЛОКИ" )
		{
			this->m_Mode = 6;
			if ( this->m_Level > 4 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 4;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"РЕЛЕ" )
		{
			this->m_Mode = 7;
			if ( this->m_Level > 5 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ОБОРУДОВАНИЕ" )
		{
			this->m_Mode = 8;
			if ( this->m_Level > 5 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВСПОМОГАТЕЛЬНЫЕ" )
		{
			this->m_Mode = 9;
			if ( this->m_Level > 5 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ВСПОМОГАТЕЛЬНЫЕ ПЕРЕМЕННЫЕ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 5;
			return 0;
		}
		else if ( ( token == L"ПЕРЕМЕННЫЕ" ) && ( this->m_Mode == 9 ) )
		{
			this->m_Mode = 10;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"СОСТОЯНИЯ" )
		{
			this->m_Mode = 11;
			if ( this->m_Level > 5 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"СОБЫТИЯ" )
		{
			this->m_Mode = 14;
			if ( this->m_Level > 6 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 6;
			this->m_Submode = 0;
			return 0;
		}
        else if ( token == L"ЗАПРОС" )
        {
            this->m_Mode = 29;
            if ( this->m_Level > 6 )
            {
                scbParseInfo new_info { info };
                new_info.Token = L"ЗАПРОС ПОТРЕБНОСТЕЙ";
                return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
            }
            this->m_Level = 6;
            return 0;
        }
        else if ( ( token == L"ПОТРЕБНОСТЕЙ" ) && ( this->m_Mode == 29 ) )
        {
            this->m_Mode = 30;
            this->m_Submode = 0;
            return 0;
        }
        else if ( token == L"ПЕРЕДАЧА" )
		{
			this->m_Mode = 15;
			if ( this->m_Level > 6 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ПЕРЕДАЧА ПОТРЕБНОСТЕЙ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 6;
			return 0;
		}
		else if ( ( token == L"ПОТРЕБНОСТЕЙ" ) && ( this->m_Mode == 15 ) )
		{
			this->m_Mode = 16;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"УДОВЛЕТВОРЕНИЕ" )
		{
			this->m_Mode = 17;
			if ( this->m_Level > 6 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"УДОВЛЕТВОРЕНИЕ ПОТРЕБНОСТЕЙ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 6;
			return 0;
		}
		else if ( ( token == L"ПОТРЕБНОСТЕЙ" ) && ( this->m_Mode == 17 ) )
		{
			this->m_Mode = 18;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ТРАНЗИТНЫЕ" )
		{
			this->m_Mode = 19;
			if ( this->m_Level > 7 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"ТРАНЗИТНЫЕ ЦЕПИ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 7;
			return 0;
		}
		else if ( ( token == L"ЦЕПИ" ) && ( this->m_Mode == 19 ) )
		{
			this->m_Mode = 20;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"КРОСС" )
		{
			this->m_Mode = 21;
			if ( this->m_Level > 5 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ЛИНИИ" )
		{
			this->m_Mode = 27;
			if ( this->m_Level > 5 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 5;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВХОДЫ" )
		{
			this->m_Mode = 22;
			if ( this->m_Level > 7 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 7;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВЫХОДЫ" )
		{
			this->m_Mode = 23;
			if ( this->m_Level > 7 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 7;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"РАСЧЕТНЫЕ" )
		{
			this->m_Mode = 24;
			if ( this->m_Level > 8 )
			{
				scbParseInfo new_info { info };
				new_info.Token = L"РАСЧЕТНЫЕ ЦЕПИ";
				return this->m_MessagePool->IncorrectLevelOfBlock ( new_info );
			}
			this->m_Level = 8;
			return 0;
		}
		else if ( ( token == L"ЦЕПИ" ) && ( this->m_Mode == 24 ) )
		{
			this->m_Mode = 25;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ЧУВСТВИТЕЛЬНОСТИ" )
		{
			this->m_Mode = 26;
			if ( this->m_Level > 8 )
				return this->m_MessagePool->IncorrectLevelOfBlock ( info );
			this->m_Level = 8;
			this->m_Submode = 0;
			return 0;
		}
	}

	int res = 0;
	switch ( this->m_Mode )
	{
	case 0:
		res = this->ParseScheme ( info );
		break;
	case 28:
		res = this->ParseAlias ( info );
		break;
	case 2:
		res = this->ParseExternalConnection ( info );
		break;
	case 3:
		res = this->ParseExternalLink ( info );
		break;
	case 5:
		res = this->ParseInternalConnection ( info );
		break;
	case 6:
		res = this->ParseBlock ( info );
		break;
	case 7:
		res = this->ParseRelay ( info );
		break;
	case 8:
		res = this->ParseEquipment ( info );
		break;
	case 10:
		res = this->ParseVariable ( info );
		break;
	case 11:
		res = this->ParseStatus ( info );
		break;
	case 13:
		res = this->ParseTuning ( info );
		break;
	case 14:
		res = this->ParseEvent ( info );
		break;
    case 30:
        res = this->ParseRequestRequirement ( info );
        break;
    case 16:
		res = this->ParseTransmitRequirement ( info );
		break;
	case 18:
		res = this->ParseGrantRequirement ( info );
		break;
	case 20:
		res = this->ParseTransitCircuit ( info );
		break;
	case 21:
		res = this->ParseCross ( info );
		break;
	case 22:
		res = this->ParseInput ( info );
		break;
	case 23:
		res = this->ParseOutput ( info );
		break;
	case 25:
		res = this->ParseWorkingCircuit ( info );
		break;
	case 26:
		res = this->ParseSensitive ( info );
		break;
	case 27:
		res = this->ParseLine ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}

	// 0 - можно работать далее
	// 1 - фатальная ошибка
	return res;
}

void scbSchemeManager::Compile ()
{

}

void scbSchemeManager::FlushBinFile ( const ofstream& file )
{

}

void scbSchemeManager::FlushLogFile ( const wofstream& file )
{

}

int scbSchemeManager::ParseScheme ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			res = this->Scheme_AddNew ( info );
			res = max ( this->TagName ( info ), res );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
		{
			res = this->TagName ( info );
			this->m_Submode = 6;
		}
		break;
	case 3:
		res = this->TagNewDescriptorParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 6;
		else if ( token == L"%" )
			this->m_Submode = 37;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L">" )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"." )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		res = this->TagName ( info );
		this->m_Submode = 8;
		break;
	case 8:
		if ( token == L"{" )
		{
			res = this->Scheme_Descriptor ( info );
			this->m_Submode = 11;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		res = this->Scheme_SetMultiplicator ( info );
		this->m_Submode = 10;
		break;
	case 10:
		if ( token == L")" )
			this->m_Submode = 36;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"Размещение" )
			this->m_Submode = 12;
		else if ( token == L"Блок" )
			this->m_Submode = 30;
		else if ( token == L"Описание" )
		{
			res = this->Scheme_AddNewDescriptionGroup ( info );
			this->m_Submode = 18;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		if ( token == L":" )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		res = this->Scheme_AddNewPlacementName ( info );
		this->m_Submode = 14;
		break;
	case 14:
		if ( token == L"(" )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 16;
		break;
	case 16:
		if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Scheme_SetPlacementType ( this->m_BackupParseInfo );
			this->m_Submode = 17;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 17:
		if ( token == L";" )
			this->m_Submode = 34;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		if ( token == L":" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 20;
		break;
	case 20:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Scheme_AddNewDescriptionTag ( this->m_BackupParseInfo );
			res = max ( this->Scheme_CheckDescriptionGroup ( info ), res );
			this->m_Submode = 34;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Scheme_AddNewDescriptionTag ( this->m_BackupParseInfo );
			this->m_Submode = 19;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
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
		if ( token == L":" )
			this->m_Submode = 31;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		res = this->Scheme_AddNewBlockName ( info );
		this->m_Submode = 32;
		break;
	case 32:
		if ( token == L";" )
			this->m_Submode = 34;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 33:
		// Исключено намеренно
		break;
	case 34:
		if ( token == L"}" )
			this->m_Submode = 35;
		else if ( token == L"Блок" )
			this->m_Submode = 30;
		else if ( token == L"Размещение" )
			this->m_Submode = 12;
		else if ( token == L"Описание" )
		{
			res = this->Scheme_AddNewDescriptionGroup ( info );
			this->m_Submode = 18;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 35:
		if ( token == L";" )
		{
			res = this->Scheme_Multiplicate ( info );
			this->m_Submode = 0;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 36:
		if ( token == L"{" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 37:
		if ( token == L">" )
			this->m_Submode = 38;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 38:
		if ( token == L"." )
			this->m_Submode = 39;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 39:
		res = this->TagName ( info );
		this->m_Submode = 40;
		break;
	case 40:
		if ( token == L"(" )
		{
			res = this->Scheme_Descriptor ( info );
			this->m_Submode = 9;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseAlias ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"<" )
			this->m_Submode = 1;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 1:
		res = this->Alias_AddAlias ( info );
		this->m_Submode = 2;
		break;
	case 2:
		if ( token == L">" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"=" )
			this->m_Submode = 15;
		else if ( token == L"," )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		if ( token == L"<" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		res = this->Alias_AddAlias ( info );
		this->m_Submode = 6;
		break;
	case 6:
		if ( token == L">" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		if ( token == L"=" )
			this->m_Submode = 8;
		else if ( token == L"," )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"Сортировка" )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"(" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		if ( token == L"<" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		res = this->Alias_SortParam ( info );
		this->m_Submode = 12;
		break;
	case 12:
		if ( token == L">" )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		if ( token == L"," )
			this->m_Submode = 10;
		else if ( token == L")" )
			this->m_Submode = 14;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		if ( token == L"<" )
			this->m_Submode = 17;
		else
		{
			res = this->Alias_PreParamString ( info );
			this->m_Submode = 16;
		}
		break;
	case 16:
		if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L"<" )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		res = this->Alias_ParamString ( info );
		this->m_Submode = 18;
		break;
	case 18:
		if ( token == L">" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		if ( token == L";" )
			this->m_Submode = 0;
		else
		{
			res = this->Alias_PostParamString ( info );
			this->m_Submode = 20;
		}
		break;
	case 20:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseTuning ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"(" )
		{
			res = this->Tuning_AddNew ( info );
			res = max ( this->Tuning_CheckDescriptor ( info ), res );
			this->m_Submode = 9;
		}
		else
		{
			res = this->Tuning_AddNew ( info );
			res = max ( this->TagName ( info ), res );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
		{
			res = this->TagName ( info );
			this->m_Submode = 5;
		}
		break;
	case 3:
		res = this->TagParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		res = this->TagName ( info );
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L":" )
		{
			res = this->Tuning_Descriptor ( info );
			this->m_Submode = 8;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"(" )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 10;
		break;
	case 10:
		if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Tuning_AddNewDescriptionTag ( this->m_BackupParseInfo );
			res = max ( this->Tuning_CheckDescriptionAndTuning ( info ), res );
			this->m_Submode = 11;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Tuning_AddNewDescriptionTag ( this->m_BackupParseInfo );
			this->m_Submode = 9;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 11:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseExternalLink ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			res = this->ExternalLink_AddNew ( info );
			res = max ( this->TagName ( info ), res );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		res = this->TagNewExternalLinkParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		res = this->TagName ( info );
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L"(" )
		{
			res = this->ExternalLink_Descriptor ( info );
			this->m_Submode = 8;
		}
		else if ( token == L"," )
		{
			res = this->ExternalLink_Descriptor ( info );
			this->m_Submode = 13;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 9;
		break;
	case 9:
		if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_DescriptionTag ( this->m_BackupParseInfo );
			this->m_Submode = 10;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 10:
		if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L":" )
		{
			res = this->ExternalLink_AddConditionGroup ( info );
			this->m_Submode = 11;
		}
		else if ( token == L"{" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"<" )
			this->m_Submode = 15;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 12;
		}
		break;
	case 12:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->ExternalLink_CheckConditionGroup ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 11;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 13:
		if ( token == L"Обязательно" )
		{
			res = this->ExternalLink_Necesserily ( info );
			this->m_Submode = 10;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		// Исключен
		break;
	case 15:
		res = this->SetConditionParam ( info );
		this->m_Submode = 16;
		break;
	case 16:
		if ( token == L">" )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		if ( token == L"(" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 19;
		break;
	case 19:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 18;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 20;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 20:
		if ( token == L";" )
		{
			res = this->ExternalLink_CheckConditionGroup ( info );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"Условие" )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L":" )
		{
			res = this->ExternalLink_AddConditionGroup ( info );
			this->m_Submode = 23;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 23:
		if ( token == L"<" )
			this->m_Submode = 25;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 24;
		}
		break;
	case 24:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->ExternalLink_CheckConditionGroup ( info ), res );
			this->m_Submode = 31;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 23;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 25:
		res = this->SetConditionParam ( info );
		this->m_Submode = 26;
		break;
	case 26:
		if ( token == L">" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"(" )
			this->m_Submode = 28;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 29;
		break;
	case 29:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 28;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalLink_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 30;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 30:
		if ( token == L";" )
		{
			res = this->ExternalLink_CheckConditionGroup ( info );
			this->m_Submode = 31;
		}
		else if ( token == L"," )
			this->m_Submode = 23;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		if ( token == L"Условие" )
			this->m_Submode = 22;
		else if ( token == L"}" )
			this->m_Submode = 32;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 32:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseExternalConnection ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			res = this->ExternalConnection_AddNew ( info );
			res = max ( this->TagName ( info ), res );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		res = this->TagParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"[" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		res = this->TagGroupName ( info );
		this->m_Submode = 8;
		break;
	case 8:
		if ( token == L"]" )
		{
			res = this->ExternalConnection_Descriptor ( info );
			this->m_Submode = 9;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L":" )
		{
			res = this->ExternalConnection_AddConditionGroup ( info );
			this->m_Submode = 11;
		}
		else if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L"{" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		// Пропущен специально
		break;
	case 11:
		if ( token == L"<" )
			this->m_Submode = 15;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 12;
		}
		break;
	case 12:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->ExternalConnection_CheckConditionGroup ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 11;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 13:
	case 14:
		// Пропущены специально
		break;
	case 15:
		res = this->SetConditionParam ( info );
		this->m_Submode = 16;
		break;
	case 16:
		if ( token == L">" )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		if ( token == L"(" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 19;
		break;
	case 19:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 18;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 20;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 20:
		if ( token == L";" )
		{
			res = this->ExternalConnection_CheckConditionGroup ( info );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"Условие" )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L":" )
		{
			res = this->ExternalConnection_AddConditionGroup ( info );
			this->m_Submode = 23;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 23:
		if ( token == L"<" )
			this->m_Submode = 25;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 24;
		}
		break;
	case 24:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->ExternalConnection_CheckConditionGroup ( info ), res );
			this->m_Submode = 31;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 23;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 25:
		res = this->SetConditionParam ( info );
		this->m_Submode = 26;
		break;
	case 26:
		if ( token == L">" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"(" )
			this->m_Submode = 28;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 29;
		break;
	case 29:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 28;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 30;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 30:
		if ( token == L";" )
		{
			res = this->ExternalConnection_CheckConditionGroup ( info );
			this->m_Submode = 31;
		}
		else if ( token == L"," )
			this->m_Submode = 23;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		if ( token == L"Условие" )
			this->m_Submode = 22;
		else if ( token == L"}" )
			this->m_Submode = 32;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 32:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseInternalConnection ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			res = this->InternalConnection_AddNew ( info );
			res = max ( this->TagName ( info ), res );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		res = this->TagParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"[" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		res = this->TagGroupName ( info );
		this->m_Submode = 8;
		break;
	case 8:
		if ( token == L"]" )
		{
			res = this->InternalConnection_FirstDescriptor ( info );
			this->m_Submode = 9;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"-" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		this->m_CurrentDescriptor.Clear ();
		res = this->TagName ( info );
		this->m_Submode = 11;
		break;
	case 11:
		if ( token == L"." )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		if ( token == L"<" )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		res = this->TagParamName ( info );
		this->m_Submode = 14;
		break;
	case 14:
		if ( token == L">" )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		if ( token == L"." )
			this->m_Submode = 16;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
		if ( token == L"[" )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		res = this->TagGroupName ( info );
		this->m_Submode = 18;
		break;
	case 18:
		if ( token == L"]" )
		{
			res = this->InternalConnection_SecondDescriptor ( info );
			this->m_Submode = 19;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L":" )
		{
			res = this->InternalConnection_AddConditionGroup ( info );
			this->m_Submode = 20;
		}
		else if ( token == L"{" )
			this->m_Submode = 30;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 20:
		if ( token == L"<" )
			this->m_Submode = 22;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 21;
		}
		break;
	case 21:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->InternalConnection_CheckConditionGroup ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 20;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 22:
		res = this->SetConditionParam ( info );
		this->m_Submode = 25;
		break;
	case 25:
		if ( token == L">" )
			this->m_Submode = 26;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 26:
		if ( token == L"(" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 28;
		break;
	case 28:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 27;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 29;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 29:
		if ( token == L";" )
		{
			res = this->InternalConnection_CheckConditionGroup ( info );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
			this->m_Submode = 20;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 30:
		if ( token == L"Условие" )
			this->m_Submode = 31;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		if ( token == L":" )
		{
			res = this->InternalConnection_AddConditionGroup ( info );
			this->m_Submode = 32;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 32:
		if ( token == L"<" )
			this->m_Submode = 34;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 33;
		}
		break;
	case 33:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->InternalConnection_CheckConditionGroup ( info ), res );
			this->m_Submode = 40;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 32;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 34:
		res = this->SetConditionParam ( info );
		this->m_Submode = 35;
		break;
	case 35:
		if ( token == L">" )
			this->m_Submode = 36;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 36:
		if ( token == L"(" )
			this->m_Submode = 37;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 37:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 38;
		break;
	case 38:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 37;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->InternalConnection_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 39;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 39:
		if ( token == L";" )
		{
			res = this->InternalConnection_CheckConditionGroup ( info );
			this->m_Submode = 40;
		}
		else if ( token == L"," )
			this->m_Submode = 32;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 40:
		if ( token == L"Условие" )
			this->m_Submode = 31;
		else if ( token == L"}" )
			this->m_Submode = 41;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 41:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseBlock ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L"Использование" )
			this->m_Submode = 10;
		else
		{
			res = this->Block_AddNew ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"," )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"Тип" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"=" )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		res = this->Block_SetTypeName ( info );
		this->m_Submode = 5;
		break;
	case 5:
		if ( token == L"," )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"Размещение" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		if ( token == L"=" )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		res = this->Block_SetPlacement ( info );
		this->m_Submode = 9;
		break;
	case 9:
		if ( token == L"," )
			this->m_Submode = 20;
		else if ( token == L"{" )
			this->m_Submode = 28;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		if ( token == L"комплектов" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"из" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		if ( token == L"дополнительного" )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		if ( token == L"блока" )
		{
			res = this->ExtendedBlock_AddNew ( info );
			this->m_Submode = 14;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		res = this->ExtendedBlock_Name ( info );
		this->m_Submode = 15;
		break;
	case 15:
		if ( token == L":" )
			this->m_Submode = 16;
		else if ( token == L"{" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
		res = this->ExtendedBlock_DefaultCount ( info );
		this->m_Submode = 17;
		break;
	case 17:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		if ( token == L"Условие" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		if ( token == L"для" )
			this->m_Submode = 35;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 20:
		if ( token == L"Место" )
			this->m_Submode = 55;
		else if ( token == L"Наименование" )
		{
			this->m_Iteration = 0;
			this->m_Submode = 21;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"=" )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L"\"" )
		{
            res = this->ClearObjectName ();
			this->m_Submode = 23;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 23:
		if ( token == L"<" )
			this->m_Submode = 25;
		else
		{
			res = this->AddPatternToObjectName ( info );
			this->m_Submode = 24;
		}
		break;
	case 24:
		if ( token == L"<" )
			this->m_Submode = 25;
		else if ( token == L"\"" )
			this->m_Submode = 27;
		else
			res = this->AddPatternToObjectName ( info );
		break;
	case 25:
		res = this->AddParamToObjectName ( info );
		this->m_Submode = 26;
		break;
	case 26:
		if ( token == L">" )
			this->m_Submode = 51;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L";" )
		{
			res = this->Block_AddObjectName ( info );
			res = max ( this->Block_FixSingleName ( info ), res );
			this->m_Submode = 0;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
		this->m_Iteration = 1;
		if ( token == L"Наименование" )
			this->m_Submode = 29;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 29:
		if ( token == L"=" )
			this->m_Submode = 30;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 30:
		if ( token == L"\"" )
		{
            res = this->ClearObjectName ();
			this->m_Submode = 31;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		if ( token == L"<" )
			this->m_Submode = 33;
		else
		{
			res = this->AddPatternToObjectName ( info );
			this->m_Submode = 32;
		}
		break;
	case 32:
		if ( token == L"<" )
			this->m_Submode = 33;
		else if ( token == L"\"" )
			this->m_Submode = 49;
		else
			res = this->AddPatternToObjectName ( info );
		break;
	case 33:
		res = this->AddParamToObjectName ( info );
		this->m_Submode = 34;
		break;
	case 34:
		if ( token == L">" )
			this->m_Submode = 53;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 35:
		if ( token == L"1" )
		{
			res = this->ExtendedBlock_AddConditionGroup ( info );
			this->m_Submode = 37;
		}
		else if ( ( token == L"2" ) || ( token == L"3" ) || ( token == L"4" ) || ( token == L"5" ) ||
			( token == L"6" ) || ( token == L"7" ) || ( token == L"8" ) || ( token == L"9" ) || ( token == L"10" ) )
		{
			res = this->ExtendedBlock_AddConditionGroup ( info );
			this->m_Submode = 36;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 36:
		if ( token == L"комплектов" )
			this->m_Submode = 38;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 37:
		if ( token == L"комплекта" )
			this->m_Submode = 38;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 38:
		if ( token == L":" )
			this->m_Submode = 39;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 39:
		if ( token == L"<" )
			this->m_Submode = 41;
		else
		{
			this->m_CurrentConditionParam = -1;
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 40;
		}
		break;
	case 40:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExtendedBlock_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 39;
		}
		else if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExtendedBlock_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->ExtendedBlock_CheckConditionGroup ( info ), res );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 46;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 41:
		res = this->SetConditionParam ( info );
		this->m_Submode = 42;
		break;
	case 42:
		if ( token == L">" )
			this->m_Submode = 43;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 43:
		if ( token == L"(" )
			this->m_Submode = 44;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 44:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 45;
		break;
	case 45:
		if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExtendedBlock_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 48;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->ExtendedBlock_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 44;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 46:
		if ( token == L"}" )
			this->m_Submode = 47;
		else if ( token == L"Условие" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 47:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 48:
		if ( token == L"," )
			this->m_Submode = 39;
		else if ( token == L";" )
		{
			res = this->ExtendedBlock_CheckConditionGroup ( info );
			this->m_Submode = 46;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 49:
		if ( token == L";" )
		{
			res = this->Block_AddObjectName ( info );
			this->m_Submode = 54;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 50:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 51:
        if ( token == L"<" )
            this->m_Submode = 25;
		else if ( token == L"\"" )
			this->m_Submode = 27;
		else
		{
			res = this->AddPatternToObjectName ( info );
			this->m_Submode = 24;
		}
		break;
	case 52:
		// Исключено намеренно
		break;
	case 53:
		if ( token == L"\"" )
			this->m_Submode = 49;
		else if ( token == L"<" )
			this->m_Submode = 33;
		else
		{
			res = this->AddPatternToObjectName ( info );
			this->m_Submode = 32;
		}
		break;
	case 54:
		if ( token == L"Наименование" )
		{
			++ this->m_Iteration;
			this->m_Submode = 29;
		}
		else if ( token == L"}" )
		{
			res = this->Block_FixMultipleNames ( info );
			this->m_Submode = 47;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 55:
		if ( token == L"=" )
			this->m_Submode = 56;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 56:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 57;
		break;
	case 57:
		if ( token == L"{" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Block_SetLocation ( this->m_BackupParseInfo );
			this->m_Submode = 28;
		}
		else if ( token == L"," )
		{
			this->m_Iteration = 0;
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Block_SetLocation ( this->m_BackupParseInfo );
			this->m_Submode = 58;
		}
		else if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Block_SetLocation ( this->m_BackupParseInfo );
			res = max ( this->Block_FixSingleName ( info ), res );
			this->m_Submode = 0;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 58:
		if ( token == L"Наименование" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseRelay ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"Повторители" )
			this->m_Submode = 2;
		else
		{
			res = this->Relay_AddNew ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"," )
			this->m_Submode = 60;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"," )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"Потребность" )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		if ( token == L"=" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
        res = this->Relay_RequirementName ( info );
		this->m_Submode = 6;
		break;
	case 6:
		if ( token == L"," )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		if ( token == L"Размещение" )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"=" )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
        res = this->Relay_RequirementPlacement ( info );
		this->m_Submode = 32;
		break;
	case 10:
		if ( token == L"Место" )
			this->m_Submode = 73;
		else if ( token == L"Наименование" )
			this->m_Submode = 79;
		else if ( token == L"Перемычка" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"=" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 13;
		break;
	case 13:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetTypeName ( this->m_BackupParseInfo );
			this->m_Submode = 61;
		}
		else
			this->m_CurrentString += token;
		break;
	case 14:
		if ( token == L"=" )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		res = this->Relay_SetPlacement ( info );
		this->m_Submode = 72;
		break;
	case 16:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			res = max ( this->Relay_FixDescription ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			this->m_Submode = 66;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 17:
		if ( token == L"=" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 16;
		break;
	case 19:
		if ( token == L"=" )
			this->m_Submode = 20;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 20:
		res = this->Relay_SetBlock ( info );
		this->m_Submode = 63;
		break;
	case 21:
        if ( token == L"\"" )
        {
            res = this->ClearObjectName ();
            this->m_Submode = 22;
        }
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L"<" )
			this->m_Submode = 24;
		else
		{
            res = this->AddPatternToObjectName ( info );
			this->m_Submode = 23;
		}
		break;
	case 23:
        if ( token == L"<" )
            this->m_Submode = 24;
        else if ( token == L"\"" )
        {
            res = this->Relay_AddObjectName ( info );
            this->m_Submode = 77;
        }
        else
            res = this->AddPatternToObjectName ( info );
		break;
	case 24:
		res = this->AddParamToObjectName ( info );
		this->m_Submode = 25;
		break;
	case 25:
		if ( token == L">" )
			this->m_Submode = 26;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 26:
        if ( token == L"\"" )
        {
            res = this->Relay_AddObjectName ( info );
            this->m_Submode = 77;
        }
        else if ( token == L"<" )
            this->m_Submode = 23;
		else
		{
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 23;
		}
		break;
	case 27:
		if ( token == L"=" )
			this->m_Submode = 28;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 31;
		break;
	case 29:
		// Исключено намеренно
		break;
	case 30:
		// Исключено намеренно
		break;
	case 31:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			this->m_Submode = 78;
		}
		else if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			res = max ( this->Relay_FixDescription ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L":" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			res = max ( this->Relay_AddConditionGroup ( info ), res );
			this->m_Submode = 80;
		}
		else if ( token == L"{" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			this->m_Submode = 88;
		}
		else
			this->m_CurrentString += token;
		break;
	case 32:
		if ( token == L"{" )
			this->m_Submode = 33;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 33:
		res = this->Relay_AddNew ( info );
		this->m_Submode = 34;
		break;
	case 34:
		if ( token == L"," )
			this->m_Submode = 35;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 35:
		if ( token == L"Тип" )
			this->m_Submode = 36;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 36:
		if ( token == L"=" )
			this->m_Submode = 37;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 37:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 38;
		break;
	case 38:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetTypeName ( this->m_BackupParseInfo );
            res = max ( this->Relay_SetRequirement ( info ), res );
            this->m_Submode = 39;
		}
		else
			this->m_CurrentString += token;
		break;
	case 39:
		if ( token == L"Наименование" )
			this->m_Submode = 40;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 40:
		if ( token == L"=" )
			this->m_Submode = 41;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 41:
        if ( token == L"\"" )
        {
            res = this->ClearObjectName ();
            this->m_Submode = 42;
        }
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 42:
		if ( token == L"<" )
			this->m_Submode = 44;
		else
		{
            res = this->AddPatternToObjectName ( info );
			this->m_Submode = 43;
		}
		break;
	case 43:
		if ( token == L"<" )
			this->m_Submode = 44;
		else if ( token == L"\"" )
		{
			res = this->Relay_AddObjectName ( info );
			this->m_Submode = 47;
		}
		else
			this->m_CurrentString += token;
		break;
	case 44:
		res = this->AddParamToObjectName ( info );
		this->m_Submode = 45;
		break;
	case 45:
		if ( token == L">" )
			this->m_Submode = 46;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 46:
        if ( token == L"<" )
            this->m_Submode = 44;
		else if ( token == L"\"" )
		{
			res = this->Relay_AddObjectName ( info );
			this->m_Submode = 47;
		}
		else
		{
            res = this->AddPatternToObjectName ( info );
			this->m_Submode = 43;
		}
		break;
	case 47:
		if ( token == L"," )
			this->m_Submode = 48;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 48:
		if ( token == L"Перемычка" )
			this->m_Submode = 58;
		else if ( token == L"Потребность" )
			this->m_Submode = 51;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 49:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 50;
		break;
	case 50:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			this->m_Submode = 48;
		}
		else
			this->m_CurrentString += token;
		break;
	case 51:
		if ( token == L"от" )
			this->m_Submode = 52;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 52:
		res = this->Relay_SetRequirementFrom ( info );
		this->m_Submode = 53;
		break;
	case 53:
		if ( token == L"до" )
			this->m_Submode = 54;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 54:
		res = this->Relay_SetRequirementTo ( info );
		this->m_Submode = 55;
		break;
	case 55:
		if ( token == L";" )
		{
			res = this->Relay_FixDescription ( info );
			this->m_Submode = 56;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 56:
        if ( token == L"}" )
        {
            res = this->Relay_FixRequirement ( info );
            this->m_Submode = 57;
        }
		else
		{
			res = this->Relay_AddNew ( info );
			this->m_Submode = 34;
		}
		break;
	case 57:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 58:
        if ( token == L"=" )
            this->m_Submode = 49;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 59:
		// Исключено намеренно
		break;
	case 60:
		if ( token == L"Тип" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 61:
		if ( token == L"Размещение" )
			this->m_Submode = 14;
		else if ( token == L"Блок" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 62:
		if ( token == L"Место" )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 63:
		if ( token == L"," )
			this->m_Submode = 62;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 64:
		if ( token == L"Тип" )
			this->m_Submode = 35;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 65:
		if ( token == L"Размещение" )
			this->m_Submode = 38;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 66:
		if ( token == L"Перемычка" )
			this->m_Submode = 67;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 67:
		if ( token == L"=" )
			this->m_Submode = 68;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 68:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 71;
		break;
	case 69:
		// Исключено намеренно
		break;
	case 70:
		// Исключено намеренно
		break;
	case 71:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			res = max ( this->Relay_FixDescription ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddJumper ( this->m_BackupParseInfo );
			this->m_Submode = 66;
		}
		else
			this->m_CurrentString += token;
		break;
	case 72:
		if ( token == L";" )
		{
			res = this->Relay_FixDescription ( info );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
			this->m_Submode = 10;
		else if ( token == L":" )
		{
			res = this->Relay_AddConditionGroup ( info );
			this->m_Submode = 80;
		}
		else if ( token == L"{" )
			this->m_Submode = 88;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 73:
		if ( token == L"=" )
			this->m_Submode = 74;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 74:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 75;
		break;
	case 75:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			this->m_Submode = 76;
		}
		else if ( token == L":" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			res = max ( this->Relay_AddConditionGroup ( info ), res );
			this->m_Submode = 80;
		}
		else if ( token == L"{" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			this->m_Submode = 88;
		}
		else if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_SetLocation ( this->m_BackupParseInfo );
			res = max ( this->Relay_FixDescription ( info ), res );
			this->m_Submode = 0;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 76:
		if ( token == L"Наименование" )
			this->m_Submode = 79;
		else if ( token == L"Перемычка" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 77:
		if ( token == L"," )
			this->m_Submode = 78;
		else if ( token == L":" )
		{
			res = this->Relay_AddConditionGroup ( info );
			this->m_Submode = 80;
		}
		else if ( token == L"{" )
			this->m_Submode = 88;
		else if ( token == L";" )
		{
			res = this->Relay_FixDescription ( info );
			this->m_Submode = 0;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 78:
		if ( token == L"Перемычка" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 79:
		if ( token == L"=" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 80:
		if ( token == L"<" )
			this->m_Submode = 82;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 81;
		}
		break;
	case 81:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->Relay_CheckConditionGroup ( info ), res );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 80;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 82:
		res = this->SetConditionParam ( info );
		this->m_Submode = 83;
		break;
	case 83:
		if ( token == L">" )
			this->m_Submode = 84;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 84:
		if ( token == L"(" )
			this->m_Submode = 85;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 85:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 86;
		break;
	case 86:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 85;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 87;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 87:
		if ( token == L";" )
		{
			res = this->Relay_CheckConditionGroup ( info );
			this->m_Submode = 0;
		}
		else if ( token == L"," )
			this->m_Submode = 80;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 88:
		if ( token == L"Условие" )
			this->m_Submode = 89;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 89:
		if ( token == L":" )
		{
			res = this->Relay_AddConditionGroup ( info );
			this->m_Submode = 90;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 90:
		if ( token == L"<" )
			this->m_Submode = 92;
		else
		{
			res = this->ResetConditionParam ( info );
			this->m_BackupParseInfo = info;
			this->m_CurrentString = token;
			this->m_Submode = 91;
		}
		break;
	case 91:
		if ( token == L";" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			res = max ( this->Relay_CheckConditionGroup ( info ), res );
			this->m_Submode = 98;
		}
		else if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 90;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 92:
		res = this->SetConditionParam ( info );
		this->m_Submode = 93;
		break;
	case 93:
		if ( token == L">" )
			this->m_Submode = 94;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 94:
		if ( token == L"(" )
			this->m_Submode = 95;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 95:
		this->m_BackupParseInfo = info;
		this->m_CurrentString = token;
		this->m_Submode = 96;
		break;
	case 96:
		if ( token == L"," )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_Submode = 95;
		}
		else if ( token == L")" )
		{
			this->m_BackupParseInfo.Token = this->m_CurrentString;
			res = this->Relay_AddCondition ( this->m_BackupParseInfo );
			this->m_CurrentConditionParam = -1;
			this->m_Submode = 97;
		}
		else
		{
			this->m_CurrentString += L" ";
			this->m_CurrentString += token;
		}
		break;
	case 97:
		if ( token == L";" )
		{
			res = this->Relay_CheckConditionGroup ( info );
			this->m_Submode = 98;
		}
		else if ( token == L"," )
			this->m_Submode = 90;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 98:
		if ( token == L"Условие" )
			this->m_Submode = 89;
		else if ( token == L"}" )
		{
			res = this->Relay_FixDescription ( info );
			this->m_Submode = 99;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 99:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseEquipment ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
            res = this->Equipment_AddNew ( info );
			this->m_Submode = 1;
		}
		break;
    case 1:
        if ( token == L"," )
            this->m_Submode = 2;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 2:
        if ( token == L"Тип" )
            this->m_Submode = 3;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 3:
        if ( token == L"=" )
            this->m_Submode = 4;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 4:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 5;
		break;
	case 5:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetType ( this->m_BackupParseInfo );
            this->m_Submode = 6;
        }
        else
            this->m_CurrentString += token;
		break;
	case 6:
		if ( token == L"Номинал" )
			this->m_Submode = 7;
        else if ( token == L"Размещение" )
            this->m_Submode = 19;
        else if ( token == L"Блок" )
            this->m_Submode = 22;
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
    case 7:
        if ( token == L"=" )
            this->m_Submode = 8;
        else
            this->m_CurrentString += token;
        break;
    case 8:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 9;
        break;
    case 9:
        if (( token == L"А" ) or ( token == L"мкФ" ) or ( token == L"Ом" ) or ( token == L"кОм" ) )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetNominal ( this->m_BackupParseInfo );
            res = max ( this->Equipment_SetUnit ( info ), res );
            this->m_Submode = 12;
        }
        else if ( token == L"," )
        {
            this->m_CurrentString += L",";
            this->m_Submode = 10;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 10:
        this->m_CurrentString += token;
        this->m_BackupParseInfo.Token = this->m_CurrentString;
        res = this->Equipment_SetNominal ( this->m_BackupParseInfo );
        this->m_Submode = 11;
        break;
    case 11:
        if ( ( token == L"А" ) or ( token == L"мкФ" ) or ( token == L"Ом" ) or ( token == L"кОм" ) )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetNominal ( this->m_BackupParseInfo );
            res = max ( this->Equipment_SetUnit ( info ), res );
            this->m_Submode = 12;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 12:
        if ( token == L"," )
            this->m_Submode = 13;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 13:
        if ( token == L"Класс" )
            this->m_Submode = 14;
        else if ( token == L"Размещение" )
            this->m_Submode = 19;
        else if ( token == L"Блок" )
            this->m_Submode = 22;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 14:
        if ( token == L"питания" )
            this->m_Submode = 15;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 15:
        if ( token == L"=" )
            this->m_Submode = 16;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 16:
        res = this->Equipment_SetPowerClass ( info );
        this->m_Submode = 17;
        break;
    case 17:
        if ( token == L"," )
            this->m_Submode = 18;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 18:
        if ( token == L"Размещение" )
            this->m_Submode = 19;
        else if ( token == L"Блок" )
            this->m_Submode = 22;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 19:
        if ( token == L"=" )
            this->m_Submode = 20;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 20:
        res = this->Equipment_SetPlacement ( info );
        this->m_Submode = 21;
        break;
    case 21:
        if ( token == L"," )
            this->m_Submode = 30;
        else if ( token == L";" )
        {
            res = this->Equipment_FixDescription ( info );
            this->m_Submode = 0;
        }
        else if ( token == L":" )
        {
            res = max ( this->Equipment_AddConditionGroup ( info ), res );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 22:
        if ( token == L"=" )
            this->m_Submode = 23;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 23:
        res = this->Equipment_SetBlock ( info );
        this->m_Submode = 24;
        break;
    case 24:
        if ( token == L"," )
            this->m_Submode = 25;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 25:
        if ( token == L"Место" )
            this->m_Submode = 26;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 26:
        if ( token == L"=" )
            this->m_Submode = 27;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 27:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 28;
        break;
    case 28:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetLocation ( this->m_BackupParseInfo );
            this->m_Submode = 29;
        }
        else if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetLocation ( this->m_BackupParseInfo );
            res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L":" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetLocation ( this->m_BackupParseInfo );
            res = max ( this->Equipment_AddConditionGroup ( info ), res );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_SetLocation ( this->m_BackupParseInfo );
            this->m_Submode = 88;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 29:
        if ( token == L"Наименование" )
            this->m_Submode = 31;
        else if ( token == L"Перемычка" )
            this->m_Submode = 40;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 30:
        if ( token == L"Наименование" )
            this->m_Submode = 31;
        else if ( token == L"Перемычка" )
            this->m_Submode = 40;
        else if ( token == L"Место" )
            this->m_Submode = 26;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 31:
        if ( token == L"=" )
            this->m_Submode = 32;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 32:
        if ( token == L"\"" )
        {
            res = this->ClearObjectName ();
            this->m_Submode = 33;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 33:
        if ( token == L"<" )
            this->m_Submode = 35;
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 34;
        }
        break;
    case 34:
        if ( token == L"<" )
            this->m_Submode = 35;
        else if ( token == L"\"" )
        {
            res = this->Equipment_AddObjectName ( info );
            this->m_Submode = 38;
        }
        else
            this->m_CurrentString += token;
        break;
    case 35:
        res = this->AddParamToObjectName ( info );
        this->m_Submode = 36;
        break;
    case 36:
        if ( token == L">" )
            this->m_Submode = 37;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 37:
        if ( token == L"<" )
            this->m_Submode = 35;
        else if ( token == L"\"" )
        {
            res = this->Equipment_AddObjectName ( info );
            this->m_Submode = 38;
        }
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 34;
        }
        break;
    case 38:
        if ( token == L"," )
            this->m_Submode = 39;
        else if ( token == L";" )
        {
            res = this->Equipment_FixDescription ( info );
            this->m_Submode = 0;
        }
        else if ( token == L":" )
        {
            res = max ( this->Equipment_AddConditionGroup ( info ), res );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 39:
        if ( token == L"Перемычка" )
            this->m_Submode = 40;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 40:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 41;
        break;
    case 41:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddJumper ( this->m_BackupParseInfo );
            res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddJumper ( this->m_BackupParseInfo );
            this->m_Submode = 39;
        }
        else if ( token == L":" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddJumper ( this->m_BackupParseInfo );
            res = max ( this->Equipment_AddConditionGroup ( info ), res );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddJumper ( this->m_BackupParseInfo );
            this->m_Submode = 88;
        }
        else
            this->m_CurrentString += token;
        break;

    
    
    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            res = this->Equipment_CheckConditionGroup ( info );
            res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            res = this->Equipment_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            res = this->Equipment_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
        {
            res = this->Equipment_FixDescription ( info );
            this->m_Submode = 99;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseVariable ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			res = this->Variable_AddNew ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseStatus ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			this->m_Submode = 0;
		else
		{
			res = this->Status_AddNew ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L"=" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"1" )
		{
            res = this->Status_SetDefaultOne ( info );
			this->m_Submode = 3;
		}
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseEvent ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 5;
		}
		break;
	case 3:
        res = this->TagParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
        res = this->TagName ( info );
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L"." )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
        res = this->TagName ( info );
        res = max ( this->Event_Descriptor ( info ), res );
		this->m_Submode = 9;
		break;
	case 9:
		if ( token == L"(" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
        this->m_BackupParseInfo = info;
		this->m_Submode = 11;
		break;
	case 11:
		if ( token == L"=" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
        if ( token == L"0" )
        {
            res = this->Event_ResetStatus ( this->m_BackupParseInfo );
            this->m_Submode = 13;
        }
        else if ( token == L"1" )
        {
            res = this->Event_SetStatus ( this->m_BackupParseInfo );
            this->m_Submode = 13;
        }
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		if ( token == L"," )
			this->m_Submode = 14;
		else if ( token == L")" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
        this->m_BackupParseInfo = info;
		this->m_Submode = 15;
		break;
	case 15:
		if ( token == L"=" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
        // Исключено намеренно
		break;
	case 17:
        // Исключено намеренно
        break;
	case 18:
		if ( token == L";" )
			this->m_Submode = 0;
        else if ( token == L":" )
        {
            res = this->Event_AddConditionGroup ( info );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
            this->m_Submode = 88;
        else if ( token == L"," )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		if ( token == L"Класс" )
			this->m_Submode = 20;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 20:
		if ( token == L"вероятности" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"=" )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
		this->m_Submode = 23;
		break;
	case 23:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_ProbablityClass ( this->m_BackupParseInfo );
            this->m_Submode = 0;
        }
        else if ( token == L":" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_ProbablityClass ( this->m_BackupParseInfo );
            res = max ( this->Event_AddConditionGroup ( info ), res );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_ProbablityClass ( this->m_BackupParseInfo );
            this->m_Submode = 88;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
		break;

    
    
    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Event_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            res = this->Event_CheckConditionGroup ( info );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            res = this->Event_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Event_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Event_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            res = this->Event_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
            this->m_Submode = 99;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseRequestRequirement ( const scbParseInfo& info )
{
    const wstring& token = info.Token;
    int res = 0;
    switch ( this->m_Submode )
    {
    case 0:
        if ( token == L";" )
            break;
        else if ( token == L"(" )
            this->m_Submode = 27;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 1;
        }
        break;
    case 1:
        if ( token == L"." )
            this->m_Submode = 2;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 2:
        if ( token == L"<" )
            this->m_Submode = 5;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 3:
        // Исключено намеренно
        break;
    case 4:
        // Исключено намеренно
        break;
    case 5:
        res = this->TagParamName ( info );
        this->m_Submode = 6;
        break;
    case 6:
        if ( token == L">" )
            this->m_Submode = 7;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 7:
        if ( token == L"." )
            this->m_Submode = 8;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 8:
        if ( token == L"[" )
            this->m_Submode = 9;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 9:
        res = this->TagGroupName ( info );
        this->m_Submode = 10;
        break;
    case 10:
        if ( token == L"]" )
            this->m_Submode = 11;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 11:
        if ( token == L"." )
            this->m_Submode = 12;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 12:
        res = this->TagName ( info );
        res = max ( this->RequestedRequirement_RequestedName ( info ), res );
        this->m_Submode = 13;
        break;
    case 13:
        if ( token == L"=" )
            this->m_Submode = 14;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 14:
        if ( token == L">" )
            this->m_Submode = 15;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 15:
        if ( token == L"(" )
            this->m_Submode = 16;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 16:
        if ( token == L"0" )
        {
            res = this->RequestedRequirement_AddFakeInput ( info );
            this->m_Submode = 25;
        }
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 17;
        }
        break;
    case 17:
        if ( token == L"." )
            this->m_Submode = 18;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 18:
        if ( token == L"<" )
            this->m_Submode = 19;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 21;
        }
        break;
    case 19:
        res = this->TagParamName ( info );
        this->m_Submode = 20;
        break;
    case 20:
        if ( token == L">" )
            this->m_Submode = 21;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 21:
        if ( token == L"." )
            this->m_Submode = 22;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 22:
        res = this->TagName ( info );
        this->m_Submode = 23;
        break;
    case 23:
        if ( token == L"." )
            this->m_Submode = 24;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 24:
        res = this->TagName ( info );
        res = max ( this->RequestedRequirement_AddInputName ( info ), res );
        this->m_Submode = 25;
        break;
    case 25:
        if ( token == L")" )
        {
            res = this->RequestedRequirement_Fix ( info );
            this->m_Submode = 26;
        }
        else if ( token == L"," )
            this->m_Submode = 16;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 26:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 27:
        res = this->TagName ( info );
        this->m_Submode = 28;
        break;
    case 28:
        if ( token == L"." )
            this->m_Submode = 29;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 29:
        if ( token == L"<" )
            this->m_Submode = 30;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 32;
        }
        break;
    case 30:
        res = this->TagParamName ( info );
        this->m_Submode = 31;
        break;
    case 31:
        if ( token == L">" )
            this->m_Submode = 32;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 32:
        if ( token == L"." )
            this->m_Submode = 33;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 33:
        res = this->TagName ( info );
        this->m_Submode = 34;
        break;
    case 34:
        if ( token == L"." )
            this->m_Submode = 35;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 35:
        res = this->TagName ( info );
        res = max ( this->RequestedRequirement_RequestedName ( info ), res );
        this->m_Submode = 36;
        break;
    case 36:
        if ( token == L")" )
            this->m_Submode = 13;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
        res = this->m_MessagePool->SyntaxError ( info );
        break;
    }
    return res;
}

int scbSchemeManager::ParseTransmitRequirement ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 5;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 3;
		}
		break;
	case 3:
		if ( token == L"." )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
        res = this->TagName ( info );
        this->m_Submode = 11;
		break;
	case 5:
        res = this->TagParamName ( info );
		this->m_Submode = 6;
		break;
	case 6:
		if ( token == L">" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		if ( token == L"." )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"[" )
			this->m_Submode = 9;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 11;
		}
		break;
	case 9:
        res = this->TagGroupName ( info );
		this->m_Submode = 10;
		break;
	case 10:
		if ( token == L"]" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"." )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
        res = this->TagName ( info );
        res = max ( this->TransmitRequirement_RequestedName ( info ), res );
		this->m_Submode = 13;
		break;
	case 13:
		if ( token == L"=" )
			this->m_Submode = 14;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		if ( token == L">" )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
        if ( token == L"(" )
            this->m_Submode = 29;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 16;
        }
		break;
	case 16:
		if ( token == L"." )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		if ( token == L"<" )
			this->m_Submode = 20;
		else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 18:
		break;
	case 19:
		break;
	case 20:
        res = this->TagParamName ( info );
		this->m_Submode = 21;
		break;
	case 21:
		if ( token == L">" )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L"." )
			this->m_Submode = 23;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 23:
		if ( token == L"[" )
			this->m_Submode = 24;
		else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 24:
        res = this->TagGroupName ( info );
		this->m_Submode = 25;
		break;
	case 25:
		if ( token == L"]" )
			this->m_Submode = 26;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 26:
		if ( token == L"." )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
        res = this->TagName ( info );
        res = max ( this->TransmitRequirement_AddGrantingName ( info ), res );
		this->m_Submode = 28;
		break;
	case 28:
        if ( token == L";" )
        {
            res = this->TransmitRequirement_Fix ( info );
            this->m_Submode = 0;
        }
		else if ( token == L"," )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
    case 29:
        res = this->TagName ( info );
        this->m_Submode = 30;
        break;
    case 30:
        if ( token == L"." )
            this->m_Submode = 31;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 31:
        if ( token == L"<" )
            this->m_Submode = 32;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 34;
        }
        break;
    case 32:
        res = this->TagParamName ( info );
        this->m_Submode = 33;
        break;
    case 33:
        if ( token == L">" )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 34:
        if ( token == L"." )
            this->m_Submode = 35;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 35:
        res = this->TagName ( info );
        this->m_Submode = 36;
        break;
    case 36:
        if ( token == L"." )
            this->m_Submode = 37;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 37:
        res = this->TagName ( info );
        res = max ( this->TransmitRequirement_AddGrantingName ( info ), res );
        this->m_Submode = 38;
        break;
    case 38:
        if ( token == L")" )
            this->m_Submode = 28;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseGrantRequirement ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
        if ( token == L";" )
            break;
		else
		{
            res = this->GrantRequirement_SourceName ( info );
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"=" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
        if ( token == L">" )
            this->m_Submode = 3;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 3:
        if ( token == L"(" )
            this->m_Submode = 42;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 4;
        }
        break;
	case 4:
        if ( token == L"." )
            this->m_Submode = 5;
        else
            res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
        if ( token == L"<" )
            this->m_Submode = 6;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 6:
        res = this->TagParamName ( info );
		this->m_Submode = 7;
		break;
    case 7:
        if ( token == L">" )
            this->m_Submode = 8;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 8:
		if ( token == L"." )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"[" )
			this->m_Submode = 10;
		else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 10:
        res = this->TagGroupName ( info );
		this->m_Submode = 11;
		break;
	case 11:
		if ( token == L"]" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		if ( token == L"." )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
        res = this->TagName ( info );
        res = max ( this->GrantRequirement_AddRequirementName ( info ), res );
		this->m_Submode = 14;
		break;
	case 14:
		if ( token == L":" )
			this->m_Submode = 17;
		else if ( token == L"," )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
    case 15:
        // Исключено намеренно
        break;
    case 16:
        // Исключено намеренно
        break;
    case 17:
        res = this->TagName ( info );
        this->m_Submode = 18;
        break;
    case 18:
        if ( token == L"." )
            this->m_Submode = 19;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 19:
        if ( token == L"<" )
            this->m_Submode = 20;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 29;
        }
        break;
    case 20:
        res = this->TagParamName ( info );
        this->m_Submode = 21;
        break;
    case 21:
        if ( token == L">" )
            this->m_Submode = 22;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 22:
        if ( token == L"." )
            this->m_Submode = 23;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 23:
        res = this->TagName ( info );
        this->m_Submode = 26;
        break;
    case 24:
        // Исключено намеренно
        break;
    case 25:
        // Исключено намеренно
        break;
    case 26:
        if ( token == L"-" )
            this->m_Submode = 27;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 27:
        res = this->GrantRequirement_SetOutputCount ( info );
        this->m_Submode = 31;
        break;
    case 28:
        // Исключено намеренно
        break;
    case 29:
        if ( token == L"." )
            this->m_Submode = 30;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 30:
        res = this->TagName ( info );
        this->m_Submode = 31;
        break;
    case 31:
        if ( token == L"{" )
            this->m_Submode = 32;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 32:
        if ( token == L"Потребность" )
            this->m_Submode = 33;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 33:
        if ( token == L"от" )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 34:
        res = this->GrantRequirement_AddNewRecord ( info );
        res = max ( this->GrantRequirement_From ( info ), res );
        this->m_Submode = 35;
        break;
    case 35:
        if ( token == L"до" )
            this->m_Submode = 36;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 36:
        res = this->GrantRequirement_To ( info );
        this->m_Submode = 37;
        break;
    case 37:
        if ( token == L":" )
            this->m_Submode = 38;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 38:
        res = this->GrantRequirement_Output ( info );
        this->m_Submode = 39;
        break;
    case 39:
        if ( token == L"," )
            this->m_Submode = 38;
        else if ( token == L";" )
        {
            res = this->GrantRequirement_FixRecord ( info );
            this->m_Submode = 40;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 40:
        if ( token == L"}" )
        {
            res = this->GrantRequirement_End ( info );
            this->m_Submode = 41;
        }
        else if ( token == L"Потребность" )
            this->m_Submode = 33;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 41:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 42:
        res = this->TagName ( info );
        this->m_Submode = 43;
        break;
    case 43:
        if ( token == L"." )
            this->m_Submode = 44;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 44:
        if ( token == L"<" )
            this->m_Submode = 45;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 47;
        }
        break;
    case 45:
        res = this->TagParamName ( info );
        this->m_Submode = 46;
        break;
    case 46:
        if ( token == L">" )
            this->m_Submode = 47;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 47:
        if ( token == L"." )
            this->m_Submode = 48;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 48:
        res = this->TagName ( info );
        this->m_Submode = 49;
        break;
    case 49:
        if ( token == L"." )
            this->m_Submode = 50;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 50:
        res = this->TagName ( info );
        res = max ( this->GrantRequirement_AddRequirementName ( info ), res );
        this->m_Submode = 51;
        break;
    case 51:
        if ( token == L")" )
            this->m_Submode = 14;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseTransitCircuit ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"{" )
			this->m_Submode = 11;
		else
		{
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
			this->m_Submode = 1;
		}
		break;
	case 1:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = token;
            res = this->TransitCircuit_Name ( this->m_BackupParseInfo );
            this->m_CurrentDescriptor.Clear ();
            this->m_Submode = 0;
        }
        else if ( token == L":" )
        {
            this->m_BackupParseInfo.Token = token;
            res = this->TransitCircuit_Name ( this->m_BackupParseInfo );
            this->m_CurrentDescriptor.Clear ();
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
        {
            this->m_BackupParseInfo.Token = token;
            res = this->TransitCircuit_Name ( this->m_BackupParseInfo );
            this->m_CurrentDescriptor.Clear ();
            this->m_Submode = 88;
        }
        else if ( token == L"." )
        {
            res = this->TagName ( this->m_BackupParseInfo );
            this->m_Submode = 2;
        }
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
        res = this->TagParamName ( info );
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"[" )
			this->m_Submode = 7;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 9;
		}
		break;
	case 7:
        res = this->TagGroupName ( info );
		this->m_Submode = 8;
		break;
	case 8:
		if ( token == L"]" )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"." )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
        res = this->TagName ( info );
        res = max ( this->TransitCircuit_Output ( info ), res );
		this->m_Submode = 23;
		break;
	case 11:
        res = this->TagName ( info );
		this->m_Submode = 12;
		break;
	case 12:
		if ( token == L"." )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		if ( token == L"<" )
			this->m_Submode = 14;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 20;
		}
		break;
	case 14:
        res = this->TagParamName ( info );
		this->m_Submode = 15;
		break;
	case 15:
		if ( token == L">" )
			this->m_Submode = 16;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
		if ( token == L"." )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
        res = this->TagName ( info );
		this->m_Submode = 18;
		break;
	case 18:
        if ( token == L"." )
            this->m_Submode = 19;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 19:
        res = this->TagName ( info );
        this->m_Submode = 22;
        break;
	case 20:
        if ( token == L"." )
            this->m_Submode = 17;
        else if ( token == L"<" )
            this->m_Submode = 21;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 21:
        res = this->TagParamName ( info );
        this->m_Submode = 51;
        break;
	case 22:
        if ( token == L"}" )
        {
            res = this->TransitCircuit_TargetOutput ( info );
            this->m_Submode = 23;
        }
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 23:
		if ( token == L"<" )
			this->m_Submode = 24;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 24:
		if ( token == L"=" )
			this->m_Submode = 25;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 25:
		if ( token == L"(" )
			this->m_Submode = 38;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 26;
		}
		break;
	case 26:
		if ( token == L"." )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"<" )
			this->m_Submode = 28;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 30;
		}
		break;
	case 28:
        res = this->TagParamName ( info );
		this->m_Submode = 29;
		break;
	case 29:
		if ( token == L">" )
			this->m_Submode = 49;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 30:
		if ( token == L"." )
			this->m_Submode = 31;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 31:
		if ( token == L"<" )
			this->m_Submode = 32;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 36;
		}
		break;
	case 32:
        res = this->TagParamName ( info );
		this->m_Submode = 33;
		break;
	case 33:
		if ( token == L">" )
			this->m_Submode = 36;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 34:
        if ( token == L"[" )
            this->m_Submode = 35;
        else
        {
            res = this->TagName ( info );
            this->m_Submode = 36;
        }
        break;
	case 35:
        res = this->TagGroupName ( info );
        this->m_Submode = 50;
		break;
	case 36:
		if ( token == L"." )
			this->m_Submode = 37;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 37:
        res = this->TagName ( info );
        res = max ( this->TransitCircuit_Input ( info ), res );
		this->m_Submode = 48;
		break;
	case 38:
        res = this->TagName ( info );
		this->m_Submode = 39;
		break;
	case 39:
		if ( token == L"." )
			this->m_Submode = 40;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 40:
		if ( token == L"<" )
			this->m_Submode = 41;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 43;
		}
		break;
	case 41:
        res = this->TagParamName ( info );
		this->m_Submode = 42;
		break;
	case 42:
		if ( token == L">" )
			this->m_Submode = 43;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 43:
		if ( token == L"." )
			this->m_Submode = 44;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 44:
        res = this->TagName ( info );
		this->m_Submode = 45;
		break;
	case 45:
		if ( token == L"." )
			this->m_Submode = 46;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 46:
        res = this->TagName ( info );
        res = max ( this->TransitCircuit_FreeInput ( info ), res );
		this->m_Submode = 47;
		break;
	case 47:
		if ( token == L")" )
			this->m_Submode = 48;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 48:
		if ( token == L":" )
			this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 49:
        if ( token == L"." )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 50:
        if ( token == L"]" )
            this->m_Submode = 36;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 51:
        if ( token == L">" )
            this->m_Submode = 18;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->TransitCircuit_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            res = this->TransitCircuit_CheckConditionGroup ( info );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            res = this->TransitCircuit_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->TransitCircuit_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->TransitCircuit_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            res = this->TransitCircuit_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
            this->m_Submode = 99;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseCross ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"Размещение" )
			this->m_Submode = 1;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 1:
		if ( token == L"=" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
        res = this->Cross_Placement ( info );
		this->m_Submode = 13;
		break;
	case 3:
		if ( token == L"=" )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
        res = this->TagName ( info );
		this->m_Submode = 5;
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"<" )
			this->m_Submode = 7;
		else
		{
            res = this->TagName ( info );
			this->m_Submode = 9;
		}
		break;
	case 7:
        res = this->TagParamName ( info );
		this->m_Submode = 8;
		break;
	case 8:
		if ( token == L">" )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"." )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
        res = this->TagName ( info );
		this->m_Submode = 76;
		break;
	case 11:
		if ( token == L"=" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
        res = this->Cross_Cable ( info );
		this->m_Submode = 73;
		break;
	case 13:
		if ( token == L"," )
			this->m_Submode = 14;
        else if ( token == L"{" )
            this->m_Submode = 15;
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		if ( token == L"Место" )
			this->m_Submode = 58;
//		else if ( token == L"Объект" )
//			this->m_Submode = 3;
        else if ( token == L"Порядок" )
            this->m_Submode = 78;
        else if ( token == L"Кабель" )
            this->m_Submode = 11;
        else if ( token == L"Общее" )
            this->m_Submode = 83;
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
        res = this->Cross_AddNew ( info );
        this->m_Submode = 16;
		break;
	case 16:
		if ( token == L"," )
			this->m_Submode = 17;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 17:
		if ( token == L"Наименование" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		if ( token == L"=" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
    case 19:
        if ( token == L"\"" )
        {
            res = this->ClearObjectName ();
            this->m_Submode = 20;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 20:
        if ( token == L"<" )
            this->m_Submode = 22;
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 21;
        }
        break;
    case 21:
        if ( token == L"<" )
            this->m_Submode = 22;
        else if ( token == L"\"" )
        {
            res = this->Cross_Name ( info );
            this->m_Submode = 25;
        }
        else
            res = this->AddPatternToObjectName ( info );
        break;
    case 22:
        this->AddParamToObjectName ( info );
        this->m_Submode = 23;
        break;
    case 23:
        if ( token == L">" )
            this->m_Submode = 24;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 24:
        if ( token == L"<" )
            this->m_Submode = 22;
        else if ( token == L"\"" )
        {
            res = this->Cross_Name ( info );
            this->m_Submode = 25;
        }
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 21;
        }
        break;
    case 25:
        if ( token == L"," )
            this->m_Submode = 26;
        else if ( token == L";" )
            this->m_Submode = 34;
        else if ( token == L":" )
            this->m_Submode = 36;
        else if ( token == L"{" )
            this->m_Submode = 45;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 26:
		if ( token == L"Контакт" )
			this->m_Submode = 27;
        else if ( token == L"Количество" )
            this->m_Submode = 31;
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"=" )
			this->m_Submode = 28;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
        res = this->Cross_AddContact ( info );
		this->m_Submode = 29;
		break;
	case 29:
		if ( token == L":" )
			this->m_Submode = 36;
        else if ( token == L"{" )
            this->m_Submode = 45;
        else if ( token == L";" )
			this->m_Submode = 34;
		else if ( token == L"," )
			this->m_Submode = 30;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 30:
        if ( token == L"Количество" )
            this->m_Submode = 31;
        else
        {
            res = this->Cross_AddContact ( info );
            this->m_Submode = 29;
        }
        break;
    case 31:
        if ( token == L"=" )
            this->m_Submode = 32;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 32:
        res = this->Cross_Count ( info );
        this->m_Submode = 33;
        break;
    case 33:
        if ( token == L":" )
            this->m_Submode = 36;
        else if ( token == L"{" )
            this->m_Submode = 45;
        else if ( token == L";" )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 34:
        if ( token == L"}" )
            this->m_Submode = 35;
        else
        {
            res = this->Cross_AddNew ( info );
            this->m_Submode = 16;
        }
        break;
    case 35:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 36:
        res = this->Cross_AddConditionGroup ( info );
        if ( token == L"<" )
            this->m_Submode = 38;
        else
        {
            res = max ( this->ResetConditionParam ( info ), res );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 37;
        }
        break;
	case 37:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 36;
        }
        else if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Cross_CheckConditionGroup ( info ), res );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 34;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
	case 38:
        res = this->SetConditionParam ( info );
        this->m_Submode = 39;
        break;
	case 39:
        if ( token == L">" )
            this->m_Submode = 40;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 40:
        if ( token == L"(" )
            this->m_Submode = 41;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 41:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 42;
        break;
	case 42:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 41;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 44;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
	case 43:
        // Исключено намеренно
        break;
	case 44:
        if ( token == L"," )
            this->m_Submode = 36;
        else if ( token == L";" )
        {
            res = this->Cross_CheckConditionGroup ( info );
            this->m_Submode = 34;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 45:
        if ( token == L"Условие" )
            this->m_Submode = 46;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 46:
        if ( token == L":" )
        {
            res = this->Cross_AddConditionGroup ( info );
            this->m_Submode = 47;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 47:
        if ( token == L"<" )
            this->m_Submode = 49;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 48;
        }
        break;
    case 48:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 47;
        }
        else if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Cross_CheckConditionGroup ( info ), res );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 54;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 49:
        res = this->SetConditionParam ( info );
        this->m_Submode = 50;
        break;
    case 50:
        if ( token == L">" )
            this->m_Submode = 51;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 51:
        if ( token == L"(" )
            this->m_Submode = 52;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 52:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 53;
        break;
    case 53:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 52;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Cross_CheckConditionGroup ( info ), res );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 55;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 54:
        if ( token == L"Условие" )
            this->m_Submode = 46;
        else if ( token == L"}" )
            this->m_Submode = 56;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 55:
        if ( token == L"," )
            this->m_Submode = 47;
        else if ( token == L";" )
            this->m_Submode = 54;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 56:
        if ( token == L";" )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 57:
        // Исключено намеренно
        break;
	case 58:
		if ( token == L"=" )
			this->m_Submode = 59;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 59:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
		this->m_Submode = 74;
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
        if ( token == L"," )
            this->m_Submode = 82;
        else if ( token == L"{" )
            this->m_Submode = 15;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 74:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_Location ( this->m_BackupParseInfo );
            this->m_Submode = 75;
        }
        else if ( token == L"{" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Cross_Location ( this->m_BackupParseInfo );
            this->m_Submode = 15;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 75:
//        if ( token == L"Объект" )
  //          this->m_Submode = 3;
        if ( token == L"Порядок" )
            this->m_Submode = 78;
        else if ( token == L"Кабель" )
            this->m_Submode = 11;
        else if ( token == L"Общее" )
            this->m_Submode = 83;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 76:
        if ( token == L"," )
            this->m_Submode = 77;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 77:
        if ( token == L"Порядок" )
            this->m_Submode = 78;
        else if ( token == L"Кабель" )
            this->m_Submode = 11;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 78:
        if ( token == L"=" )
            this->m_Submode = 79;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 79:
        res = this->Cross_Order ( info );
        this->m_Submode = 80;
        break;
    case 80:
        if ( token == L"," )
            this->m_Submode = 81;
        else if ( token == L"{" )
            this->m_Submode = 15;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 81:
        if ( token == L"Кабель" )
            this->m_Submode = 11;
        else if ( token == L"Общее" )
            this->m_Submode = 83;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 82:
        if ( token == L"Общее" )
            this->m_Submode = 83;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 83:
        if ( token == L"наименование" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"=" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        if ( token == L"\"" )
        {
            res = this->ClearObjectName ();
            this->m_Submode = 86;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 86:
        if ( token == L"<" )
            this->m_Submode = 88;
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 87;
        }
        break;
    case 87:
        if ( token == L"<" )
        {
            this->m_Submode = 88;
        }
        else if ( token == L"\"" )
        {
            res = this->Cross_GeneralName ( info );
            this->m_Submode = 91;
        }
        else
            res = this->AddPatternToObjectName ( info );
        break;
    case 88:
        res = this->AddParamToObjectName ( info );
        this->m_Submode = 89;
        break;
    case 89:
        if ( token == L">" )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 88;
        else if ( token == L"\"" )
        {
            res = this->Cross_GeneralName ( info );
            this->m_Submode = 91;
        }
        else
        {
            res = this->AddPatternToObjectName ( info );
            this->m_Submode = 87;
        }
        break;
    case 91:
        if ( token == L"{" )
            this->m_Submode = 15;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseInput ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"<" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"=" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"0" )
			this->m_Submode = 4;
		else if ( token == L"1" )
			this->m_Submode = 4;
		else if ( token == L"(" )
			this->m_Submode = 16;
		else
		{
			// TODO
			this->m_Submode = 5;
		}
		break;
	case 4:
		if ( token == L";" )
		{
            // TODO
			this->m_Submode = 0;
		}
		else if ( token == L":" )
			this->m_Submode = 60;
        else if ( token == L"{" )
            this->m_Submode = 68;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 37;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		// TODO
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L">" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"." )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"<" )
			this->m_Submode = 12;
		else
		{
			// TODO
			this->m_Submode = 14;
		}
		break;
	case 10:
        if ( token == L"." )
            this->m_Submode = 11;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 11:
		if ( token == L"[" )
			this->m_Submode = 40;
        else
        {
            // TODO
            this->m_Submode = 14;
        }
		break;
	case 12:
		// TODO
		this->m_Submode = 13;
		break;
	case 13:
		if ( token == L">" )
			this->m_Submode = 14;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 14:
		if ( token == L"." )
			this->m_Submode = 15;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		// TODO
		this->m_Submode = 29;
		break;
	case 16:
		// TODO
		this->m_Submode = 17;
		break;
	case 17:
		if ( token == L"." )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 18:
		if ( token == L"<" )
			this->m_Submode = 19;
		else
		{
			// TODO
			this->m_Submode = 21;
		}
		break;
	case 19:
		// TODO
		this->m_Submode = 20;
		break;
	case 20:
		if ( token == L">" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"." )
			this->m_Submode = 22;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		// TODO
		this->m_Submode = 23;
		break;
	case 23:
		if ( token == L"." )
			this->m_Submode = 24;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 24:
		// TODO
		this->m_Submode = 25;
		break;
	case 25:
		if ( token == L")" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 26:
		if ( token == L"Обязательно" )
			this->m_Submode = 27;
		else if ( token == L"Шина" )
			this->m_Submode = 27;
		else if ( token == L"Цепочка" )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"," )
			this->m_Submode = 26;
		else if ( token == L";" )
		{
			this->m_Submode = 0;
		}
		else if ( token == L":" )
			this->m_Submode = 80;
		else if ( token == L"{" )
			this->m_Submode = 88;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 28:
        if ( token == L";" )
        {
            this->m_Submode = 0;
        }
        else if ( token == L":" )
            this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 29:
        if ( token == L"," )
            this->m_Submode = 30;
        else if ( token == L";" )
        {
            this->m_Submode = 0;
        }
        else if ( token == L":" )
            this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 30:
        if ( token == L"Необязательно" )
            this->m_Submode = 28;
        else
            res = this->m_MessagePool->SyntaxError ( info );
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
		if ( token == L"<" )
			this->m_Submode = 6;
		else
		{
			// TODO
			this->m_Submode = 8;
		}
		break;
	case 38:
		break;
	case 39:
		break;
    case 40:
        // TODO
        this->m_Submode = 41;
        break;
    case 41:
        if ( token == L"]" )
            this->m_Submode = 14;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;





    case 60:
        if ( token == L"<" )
            this->m_Submode = 62;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 61;
        }
        break;
    case 61:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 60;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 62:
        res = this->SetConditionParam ( info );
        this->m_Submode = 63;
        break;
    case 63:
        if ( token == L">" )
            this->m_Submode = 64;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 64:
        if ( token == L"(" )
            this->m_Submode = 65;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 65:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 66;
        break;
    case 66:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 65;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 67;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 67:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            //res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 60;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 68:
        if ( token == L"Условие" )
            this->m_Submode = 69;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 69:
        if ( token == L":" )
        {
            //res = this->Equipment_AddConditionGroup ( info );
            this->m_Submode = 70;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 70:
        if ( token == L"<" )
            this->m_Submode = 72;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 71;
        }
        break;
    case 71:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 78;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 70;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 72:
        res = this->SetConditionParam ( info );
        this->m_Submode = 73;
        break;
    case 73:
        if ( token == L">" )
            this->m_Submode = 74;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 74:
        if ( token == L"(" )
            this->m_Submode = 75;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 75:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 76;
        break;
    case 76:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 75;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 77;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 77:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            this->m_Submode = 78;
        }
        else if ( token == L"," )
            this->m_Submode = 70;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 78:
        if ( token == L"Условие" )
            this->m_Submode = 69;
        else if ( token == L"}" )
        {
            //res = this->Equipment_FixDescription ( info );
            this->m_Submode = 79;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 79:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else if ( token == L"Питание" )
            this->m_Submode = 100;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            //res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            //res = this->Equipment_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
        {
            //res = this->Equipment_FixDescription ( info );
            this->m_Submode = 99;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 100:
        if ( token == L"=" )
            this->m_Submode = 101;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 101:
        // TODO
        this->m_Submode = 102;
        break;
    case 102:
        if ( token == L"(" )
            this->m_Submode = 103;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 103:
        // TODO
        this->m_Submode = 104;
        break;
    case 104:
        // TODO
        this->m_Submode = 105;
        break;
    case 105:
        if ( token == L"," )
            this->m_Submode = 104;
        else if ( token == L")" )
            this->m_Submode = 87;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseOutput ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
        else if ( token == L"0" )
        {
            // TODO
            this->m_Submode = 1;
        }
        else if ( token == L"1" )
        {
            // TODO
            this->m_Submode = 1;
        }
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"=" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L">" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"{" )
			this->m_Submode = 14;
		else
		{
			// TODO
			this->m_Submode = 4;
		}
		break;
	case 4:
		if ( token == L"." )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"<" )
			this->m_Submode = 6;
		else
		{
			// TODO
			this->m_Submode = 29;
		}
		break;
	case 6:
		// TODO
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L">" )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"." )
			this->m_Submode = 9;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L"[" )
			this->m_Submode = 10;
		else
		{
			// TODO
			this->m_Submode = 12;
		}
		break;
	case 10:
		// TODO
		this->m_Submode = 11;
		break;
	case 11:
		if ( token == L"]" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		if ( token == L"." )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		// TODO
		this->m_Submode = 26;
		break;
	case 14:
		// TODO
		this->m_Submode = 15;
		break;
	case 15:
		if ( token == L"." )
			this->m_Submode = 16;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
		if ( token == L"<" )
			this->m_Submode = 17;
		else
		{
			// TODO
			this->m_Submode = 21;
		}
		break;
	case 17:
		// TODO
		this->m_Submode = 18;
		break;
	case 18:
		if ( token == L">" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		if ( token == L"." )
			this->m_Submode = 20;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 20:
    	// TODO
	    this->m_Submode = 23;
		break;
	case 21:
        if ( token == L"." )
            this->m_Submode = 22;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 22:
		if ( token == L"<" )
			this->m_Submode = 31;
        else
        {
            // TODO
            this->m_Submode = 23;
        }
		break;
	case 23:
		if ( token == L"." )
			this->m_Submode = 24;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 24:
		// TODO
		this->m_Submode = 25;
		break;
	case 25:
		if ( token == L"}" )
			this->m_Submode = 33;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 26:
		if ( token == L";" )
		{
            // TODO
			this->m_Submode = 0;
		}
		else if ( token == L":" )
			this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else if ( token == L"," )
			this->m_Submode = 27;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 27:
		if ( token == L"Обязательно" )
			this->m_Submode = 28;
		else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 28:
		if ( token == L";" )
		{
			this->m_Submode = 0;
		}
		else if ( token == L":" )
			this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 29:
        if ( token == L"." )
            this->m_Submode = 30;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
	case 30:
        // TODO
        this->m_Submode = 12;
		break;
    case 31:
        // TODO
        this->m_Submode = 32;
        break;
    case 32:
        if ( token == L">" )
            this->m_Submode = 23;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 33:
        if ( token == L";" )
        {
            // TODO
            this->m_Submode = 0;
        }
        else if ( token == L":" )
            this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else if ( token == L"," )
            this->m_Submode = 34;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 34:
        if ( token == L"Необязательно" )
            this->m_Submode = 35;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 35:
        if ( token == L";" )
        {
            // TODO
            this->m_Submode = 0;
        }
        else if ( token == L":" )
            this->m_Submode = 80;
        else if ( token == L"{" )
            this->m_Submode = 88;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            //res = max ( this->Equipment_FixDescription ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            //res = this->Equipment_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            //res = max ( this->Equipment_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            //res = this->Equipment_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            //res = this->Equipment_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
        {
            //res = this->Equipment_FixDescription ( info );
            this->m_Submode = 99;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseWorkingCircuit ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"=" )
			this->m_Submode = 2;
		else if ( token == L"@" )
			this->m_Submode = 13;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"0" )
			this->m_Submode = 3;
		else if ( token == L"1" )
			this->m_Submode = 3;
		else if ( token == L"(" )
			this->m_Submode = 8;
		else if ( token == L"!" )
			this->m_Submode = 7;
		else
		{
			// TODO
			this->m_Submode = 10;
		}
		break;
	case 3:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		if ( token == L"=" )
			this->m_Submode = 6;
		else if ( token == L"+" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"=" )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		if ( token == L"(" )
			this->m_Submode = 8;
		else if ( token == L"!" )
			this->m_Submode = 7;
		else
		{
			// TODO
			this->m_Submode = 10;
		}
		break;
	case 7:
		// TODO
		this->m_Submode = 10;
		break;
	case 8:
		// TODO
		this->m_Submode = 9;
		break;
	case 9:
		if ( token == L")" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		if ( token == L"&" )
			this->m_Submode = 6;
		else if ( token == L";" )
			this->m_Submode = 0;
		else if ( token == L"." )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		// TODO
		this->m_Submode = 12;
		break;
	case 12:
		if ( token == L"&" )
			this->m_Submode = 6;
		else if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 13:
		// TODO
		this->m_Submode = 4;
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseSensitive ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"(" )
			this->m_Submode = 1;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 1:
		// TODO
		this->m_Submode = 2;
		break;
	case 2:
		if ( token == L")" )
			this->m_Submode = 3;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 3:
		if ( token == L"=" )
			this->m_Submode = 5;
		else if ( token == L"," )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		if ( token == L"(" )
			this->m_Submode = 1;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"(" )
			this->m_Submode = 9;
		else if ( token == L"!" )
			this->m_Submode = 6;
		else
		{
			// TODO
			this->m_Submode = 7;
		}
		break;
	case 6:
		// TODO
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L"." )
			this->m_Submode = 8;
		else if ( token == L"&" )
			this->m_Submode = 5;
		else if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		// TODO
		this->m_Submode = 11;
		break;
	case 9:
		// TODO
		this->m_Submode = 10;
		break;
	case 10:
		if ( token == L")" )
			this->m_Submode = 11;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 11:
		if ( token == L"&" )
			this->m_Submode = 5;
		else if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbSchemeManager::ParseLine ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else if ( token == L"Объект" )
			this->m_Submode = 1;
		break;
	case 1:
		if ( token == L"=" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
        res = this->TagName ( info );
		this->m_Submode = 3;
		break;
	case 3:
		if ( token == L"." )
			this->m_Submode = 4;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 4:
		if ( token == L"<" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
        res = this->TagParamName ( info );
		this->m_Submode = 6;
		break;
	case 6:
		if ( token == L">" )
			this->m_Submode = 7;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 7:
		if ( token == L"." )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
        res = this->TagName ( info );
        res = max ( this->Line_Descriptor ( info ), res );
		this->m_Submode = 9;
		break;
	case 9:
		if ( token == L"{" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
    case 10:
        res = this->Line_AddNew ( info );
        res = max ( this->Line_Descriptor ( info ), res );
        this->m_Submode = 11;
        break;
    case 11:
        if ( token == L";" )
            this->m_Submode = 12;
        else if ( token == L":" )
        {
            res = this->Line_AddConditionGroup ( info );
            this->m_Submode = 80;
        }
        else if ( token == L"{" )
            this->m_Submode = 88;
        break;
    case 12:
        if ( token == L"}" )
        {
            this->m_CurrentDescriptor.Clear ();
            this->m_Submode = 13;
        }
        else
        {
            res = this->Line_AddNew ( info );
            res = max ( this->Line_Descriptor ( info ), res );
            this->m_Submode = 11;
        }
        break;
    case 13:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;

    case 80:
        if ( token == L"<" )
            this->m_Submode = 82;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 81;
        }
        break;
    case 81:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Line_CheckConditionGroup ( info ), res );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 80;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 82:
        res = this->SetConditionParam ( info );
        this->m_Submode = 83;
        break;
    case 83:
        if ( token == L">" )
            this->m_Submode = 84;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 84:
        if ( token == L"(" )
            this->m_Submode = 85;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 85:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 86;
        break;
    case 86:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 85;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 87;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 87:
        if ( token == L";" )
        {
            res = this->Line_CheckConditionGroup ( info );
            this->m_Submode = 0;
        }
        else if ( token == L"," )
            this->m_Submode = 80;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 88:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 89:
        if ( token == L":" )
        {
            res = this->Line_AddConditionGroup ( info );
            this->m_Submode = 90;
        }
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 90:
        if ( token == L"<" )
            this->m_Submode = 92;
        else
        {
            res = this->ResetConditionParam ( info );
            this->m_BackupParseInfo = info;
            this->m_CurrentString = token;
            this->m_Submode = 91;
        }
        break;
    case 91:
        if ( token == L";" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            res = max ( this->Line_CheckConditionGroup ( info ), res );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 90;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 92:
        res = this->SetConditionParam ( info );
        this->m_Submode = 93;
        break;
    case 93:
        if ( token == L">" )
            this->m_Submode = 94;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 94:
        if ( token == L"(" )
            this->m_Submode = 95;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 95:
        this->m_BackupParseInfo = info;
        this->m_CurrentString = token;
        this->m_Submode = 96;
        break;
    case 96:
        if ( token == L"," )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_Submode = 95;
        }
        else if ( token == L")" )
        {
            this->m_BackupParseInfo.Token = this->m_CurrentString;
            res = this->Line_AddCondition ( this->m_BackupParseInfo );
            this->m_CurrentConditionParam = -1;
            this->m_Submode = 97;
        }
        else
        {
            this->m_CurrentString += L" ";
            this->m_CurrentString += token;
        }
        break;
    case 97:
        if ( token == L";" )
        {
            res = this->Line_CheckConditionGroup ( info );
            this->m_Submode = 98;
        }
        else if ( token == L"," )
            this->m_Submode = 90;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 98:
        if ( token == L"Условие" )
            this->m_Submode = 89;
        else if ( token == L"}" )
            this->m_Submode = 99;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    case 99:
        if ( token == L";" )
            this->m_Submode = 0;
        else
            res = this->m_MessagePool->SyntaxError ( info );
        break;
    default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}
