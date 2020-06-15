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
	this->m_Pool.emplace_back ( L"%compilationerror Синтаксическая ошибка в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 1;
}

int scbMessagePool::IncorrectTypeOfFile ()
{
	this->m_Pool.emplace_back ( L"%compilationerror Неверный формат входного файла.%br" );
	return 1;
}

int scbMessagePool::FatalError ()
{
	this->m_Pool.emplace_back ( L"%compilationerror Фатальная ошибка, компиляция прервана.%br" );
	return 1;
}

int scbMessagePool::IncorrectLevelOfBlock ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Ошибка расположения блока данных %param1 в строке %row.%br", info.Row, info.Token );
	return 1;
}

int scbMessagePool::NameAlwaysUsed ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Повторное использование имени '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::InvalidMultiplicatorArgument ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый аргумент мультипликатора '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор параметра '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Необъявленный параметр '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorTagOrder ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый формат дескриптора на элементе '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorGroupTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый групповой элемент '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptorTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый тэг дескриптора '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectDescriptionTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый тэг описания '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfDescriptionTag ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Повторное использование тэга описания '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectPlacementType ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый тип размещения '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::UnknownTypeOfRelay ( const wstring& name, const wstring& type, const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Неизвестный тип '%param2' реле '%param1' в строке %row.%br", info.Row, name, type );
	return 0;
}

int scbMessagePool::UnknownTypeOfEquipment ( const wstring& name, const wstring& type, const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Неизвестный тип '%param2' оборудования '%param1' в строке %row.%br", info.Row, name, type );
    return 0;
}

int scbMessagePool::UnknownTypeOfBlock ( const scbParseInfo& info, const wstring& name )
{
	this->m_Pool.emplace_back ( L"%compilationerror Неизвестный тип '%param2' блока '%param1' в строке %row.%br", info.Row, info.Pos, name, info.Token );
	return 0;
}

int scbMessagePool::IncorrectOrderOfDescription ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Неверный порядок следования описания '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfDescription ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор описания '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::DeviceCantHaveAnyJumper ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror Устройство, имеющее тип '%param1', не может иметь перемычек, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
	return 0;
}

int scbMessagePool::DeviceCantHaveThisJumper ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror Устройство, имеющее тип '%param1', не может иметь перемычку %param2, в строке %row, позиция %pos.%br", info.Row, info.Pos, type, info.Token );
	return 0;
}

int scbMessagePool::DeviceHasIncompleteSetOfJumpers ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Устройство имеет неполный набор перемычек, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::DeviceCantHaveNominal ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство типа %param1 не может иметь номинал, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHaveNominal ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство типа %param1 должно иметь номинал, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHavePowerClass ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство типа %param1 должно иметь класс питания, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceMustHaveObjectName ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство типа %param1 должно иметь наименование, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceCantHaveThisUnit ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Неверная единица измерения номинала устройства типа %param1, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::DeviceCantHavePowerClass ( const scbParseInfo& info, const wstring& type )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство типа %param1 не имеет класса питания, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
    return 0;
}

int scbMessagePool::IncorrectPowerClass ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый класс питания, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfJumper ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор перемычки, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfContact ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор контактов, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::DeviceCantHaveThisContact ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Устройство не имеет указанных контактов, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::DeviceHasIncompatibleSetOfJumpers ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Устройство имеет несовместимый набор перемычек, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::RelayCantUseToCoverAnyRequirement ( const scbParseInfo& info, const wstring& type )
{
	this->m_Pool.emplace_back ( L"%compilationerror Реле, имеющее тип '%param1', не может применяться для удовлетворения потребностей, в строке %row, позиция %pos.%br", info.Row, info.Pos, type );
	return 0;
}

int scbMessagePool::NumberExcepted ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Ожидается корректное число в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::NumberIsOutOfRange ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Число превосходит допустимый диапазон, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfPlacementName ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор имени размещения '%param1' в одном описании, в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncorrectRepeatOfPlacementType ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор того же типа размещения '%param1' в одном описании, в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::InexactRepeatOfPlacement ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Неточный повтор размещения в разных описаниях в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorMustBeSingle ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Мультиплицируемый дескриптор должен быть единственным дескриптором, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::DifferentDescriptionGroupsAreEqual ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationwarning Заявлены совпадающие секции описаний, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectSectionBlockInAloneDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Немультиплицируемый дескриптор не может иметь секцию Блок, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::TooMuchSectionBlockInDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимое количество секций Блок, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectCoincidingDescriptors ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Заявлены совпадающие дескрипторы, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectCoincidingDescriptionSets ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Заявлены совпадающие группы описаний, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectDescriptorPresence ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимое наличие дескриптора в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::IncorrectDescriptorAbsence ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимое отсутствие дескриптора в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UsingOfIncorrectDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый дескриптор в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UnachievableDescriptionCombination ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недостижимая комбинация описаний в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyConnection ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Мультиплицируеый дексриптор не может иметь связей, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyExternalLink ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Мультиплицируеый дексриптор не может иметь внешних ссылок, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyExtendedBlock ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Мультиплицируеый дексриптор не может использовать комплекты внешних блоков, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::MultiplicatingDescriptorCantHaveAnyAliases ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Мультиплицируеый дексриптор не может использовать псевдонимы, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::ConditionParamIsRequired ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Условие требует уточнения параметром, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::ConditionParamIsNotRequired ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Условие не требует уточнения параметром, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::CantHaveAnyInternalConnections ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Невозможно создание любых внутренних связей, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExternalConnections ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Невозможно создание любых внешних связей, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExternalLinks ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Невозможно создание любых внешних ссылок, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::CantHaveAnyExtendedBlocks ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Невозможно использование любых комплектов дополнительных блоков, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::DescriptorWithoutParameterMustBeSingle ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Беспараметрический основной дескриптор может быть только один, в строке %row позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::UsingInternalConnectionWithSameDescriptor ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимая внутренняя связь внутри одного дескриптора, в строке %row позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::InvalidExtendedBlockCountArgument ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Недопустимый аргумент количества комплектов '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::UndefinedPlacementName ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Неопределенное имя размещения '%param1' в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::IncompatiblePlacement ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Объект не может быть расположен в размещении '%param1', в строке %row, позиция %pos.%br", info.Row, info.Pos, info.Token );
	return 0;
}

int scbMessagePool::SimpleDescriptorCantHaveAlternativeNames ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Немультиплицируемый дескриптор не может иметь блоков с альтернативными именами, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::IncorrectCountOfAlternativeNames ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Несоответствие количества альтернативных имен и мультипликатором схемы, в строке %row.%br", info.Row );
	return 0;
}

int scbMessagePool::LocationStillOccupied ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Указанное место в размещении уже занято, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::DeviceCantOccupyTheLocation ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Устройство не может занимать указанное место, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::InactiveParameter ( const scbParseInfo& info )
{
	this->m_Pool.emplace_back ( L"%compilationerror Указан недостижимый параметр, в строке %row, позиция %pos.%br", info.Row, info.Pos );
	return 0;
}

int scbMessagePool::RequirementDoesntCoverWholeRange ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Потребность не покрывается сплошным диапазоном, в строке %row.%br", info.Row );
    return 0;
}

int scbMessagePool::RequirementFromIsGreaterThanTo ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Потребности указаны не в возврастающем порядке, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::NameMustBeTheStatus ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Указываемое имя должно быть состонием, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::NameWasNotFound ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Указываемое имя не найдено, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор дескриптора, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfRequirementName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор имени потребности, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRepeatOfRequirementDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Недопустимый повтор дескриптора потребности, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectRequirementName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Имя потребности не найдено, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectProbablityClass ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Неверный класс вероятности, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectCountOfOutput ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Несоответствие количества выходов, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::IncorrectGroupTagInDescriptor ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Указанный групповой тэг дескриптора не перечислен во внешних связях, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::MoreThanOneRecordForThisNumberOfRequestingRequirement ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Более одной записи для указанного номера потребности, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::UnableToGrantThisRequirement ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Отсутствует возможность удовлетворить указанную потребность, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::WholeInputsInRequestingRequirementAreZero ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror В запросе потребности не указан ни один вход, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::RequirementNameMustBeNonDescriptionName ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Имя потребности не может быть именем тэга, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}

int scbMessagePool::UnableToUseShortNameTransitCircuit ( const scbParseInfo& info )
{
    this->m_Pool.emplace_back ( L"%compilationerror Невозможно использовать краткое имя транзитной цепи, в строке %row, позиция %pos.%br", info.Row, info.Pos );
    return 0;
}
