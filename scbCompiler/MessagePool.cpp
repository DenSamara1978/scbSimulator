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
	this->pool.emplace_back(L"%compilationerror Синтаксическая ошибка в строке %row, позиция %pos.%br", info.row, info.pos);
	return 1;
}

int MessagePool::incorrectTypeOfFile()
{
	this->pool.emplace_back(L"%compilationerror Неверный формат входного файла.%br");
	return 1;
}

int MessagePool::fatalError()
{
	this->pool.emplace_back(L"%compilationerror Фатальная ошибка, компиляция прервана.%br");
	return 1;
}

int MessagePool::incorrectLevelOfBlock(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Ошибка расположения блока данных %param1 в строке %row.%br", info.row, info.token);
	return 1;
}

int MessagePool::nameAlwaysUsed(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Повторное использование имени '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::invalidMultiplicatorArgument(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый аргумент мультипликатора '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор параметра '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Необъявленный параметр '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorTagOrder(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый формат дескриптора на элементе '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorGroupTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый групповой элемент '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptorTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый тэг дескриптора '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectDescriptionTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый тэг описания '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfDescriptionTag(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Повторное использование тэга описания '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectPlacementType(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый тип размещения '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::unknownTypeOfRelay(const wstring& name, const wstring& type, const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неизвестный тип '%param2' реле '%param1' в строке %row.%br", info.row, name, type);
	return 0;
}

int MessagePool::unknownTypeOfEquipment(const wstring& name, const wstring& type, const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неизвестный тип '%param2' оборудования '%param1' в строке %row.%br", info.row, name, type);
	return 0;
}

int MessagePool::unknownTypeOfBlock(const ParseInfo& info, const wstring& name)
{
	this->pool.emplace_back(L"%compilationerror Неизвестный тип '%param2' блока '%param1' в строке %row.%br", info.row, info.pos, name, info.token);
	return 0;
}

int MessagePool::incorrectOrderOfDescription(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неверный порядок следования описания '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfDescription(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор описания '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::deviceCantHaveAnyJumper(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство, имеющее тип '%param1', не может иметь перемычек, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHaveThisJumper(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство, имеющее тип '%param1', не может иметь перемычку %param2, в строке %row, позиция %pos.%br", info.row, info.pos, type, info.token);
	return 0;
}

int MessagePool::deviceHasIncompleteSetOfJumpers(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Устройство имеет неполный набор перемычек, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantHaveNominal(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство типа %param1 не может иметь номинал, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHaveNominal(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство типа %param1 должно иметь номинал, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHavePowerClass(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство типа %param1 должно иметь класс питания, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceMustHaveObjectName(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство типа %param1 должно иметь наименование, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHaveThisUnit(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Неверная единица измерения номинала устройства типа %param1, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::deviceCantHavePowerClass(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Устройство типа %param1 не имеет класса питания, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::incorrectPowerClass(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый класс питания, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfJumper(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор перемычки, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfContact(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор контактов, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantHaveThisContact(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Устройство не имеет указанных контактов, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceHasIncompatibleSetOfJumpers(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Устройство имеет несовместимый набор перемычек, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::relayCantUseToCoverAnyRequirement(const ParseInfo& info, const wstring& type)
{
	this->pool.emplace_back(L"%compilationerror Реле, имеющее тип '%param1', не может применяться для удовлетворения потребностей, в строке %row, позиция %pos.%br", info.row, info.pos, type);
	return 0;
}

int MessagePool::numberExcepted(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Ожидается корректное число в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::numberIsOutOfRange(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Число превосходит допустимый диапазон, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfPlacementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор имени размещения '%param1' в одном описании, в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incorrectRepeatOfPlacementType(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор того же типа размещения '%param1' в одном описании, в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::inexactRepeatOfPlacement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неточный повтор размещения в разных описаниях в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::multiplicatingDescriptorMustBeSingle(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Мультиплицируемый дескриптор должен быть единственным дескриптором, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::differentDescriptionGroupsAreEqual(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationwarning Заявлены совпадающие секции описаний, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectSectionBlockInAloneDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Немультиплицируемый дескриптор не может иметь секцию Блок, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::tooMuchSectionBlockInDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимое количество секций Блок, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectCoincidingDescriptors(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Заявлены совпадающие дескрипторы, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectCoincidingDescriptionSets(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Заявлены совпадающие группы описаний, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectDescriptorPresence(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимое наличие дескриптора в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectDescriptorAbsence(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимое отсутствие дескриптора в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::usingOfIncorrectDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый дескриптор в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unachievableDescriptionCombination(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недостижимая комбинация описаний в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyConnection(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Мультиплицируеый дексриптор не может иметь связей, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyExternalLink(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Мультиплицируеый дексриптор не может иметь внешних ссылок, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyExtendedBlock(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Мультиплицируеый дексриптор не может использовать комплекты внешних блоков, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::multiplicatingDescriptorCantHaveAnyAliases(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Мультиплицируеый дексриптор не может использовать псевдонимы, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::conditionParamIsRequired(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Условие требует уточнения параметром, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::conditionParamIsNotRequired(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Условие не требует уточнения параметром, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::cantHaveAnyInternalConnections(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Невозможно создание любых внутренних связей, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExternalConnections(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Невозможно создание любых внешних связей, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExternalLinks(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Невозможно создание любых внешних ссылок, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::cantHaveAnyExtendedBlocks(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Невозможно использование любых комплектов дополнительных блоков, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::descriptorWithoutParameterMustBeSingle(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Беспараметрический основной дескриптор может быть только один, в строке %row позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::usingInternalConnectionWithSameDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимая внутренняя связь внутри одного дескриптора, в строке %row позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::invalidExtendedBlockCountArgument(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый аргумент количества комплектов '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::undefinedPlacementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неопределенное имя размещения '%param1' в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::incompatiblePlacement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Объект не может быть расположен в размещении '%param1', в строке %row, позиция %pos.%br", info.row, info.pos, info.token);
	return 0;
}

int MessagePool::simpleDescriptorCantHaveAlternativeNames(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Немультиплицируемый дескриптор не может иметь блоков с альтернативными именами, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::incorrectCountOfAlternativeNames(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Несоответствие количества альтернативных имен и мультипликатором схемы, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::locationStillOccupied(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Указанное место в размещении уже занято, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::deviceCantOccupyTheLocation(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Устройство не может занимать указанное место, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::inactiveParameter(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Указан недостижимый параметр, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::requirementDoesntCoverWholeRange(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Потребность не покрывается сплошным диапазоном, в строке %row.%br", info.row);
	return 0;
}

int MessagePool::requirementFromIsGreaterThanTo(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Потребности указаны не в возврастающем порядке, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::nameMustBeTheStatus(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Указываемое имя должно быть состонием, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::nameWasNotFound(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Указываемое имя не найдено, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор дескриптора, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfRequirementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор имени потребности, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRepeatOfRequirementDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Недопустимый повтор дескриптора потребности, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectRequirementName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Имя потребности не найдено, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectProbablityClass(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Неверный класс вероятности, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectCountOfOutput(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Несоответствие количества выходов, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::incorrectGroupTagInDescriptor(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Указанный групповой тэг дескриптора не перечислен во внешних связях, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::moreThanOneRecordForThisNumberOfRequestingRequirement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Более одной записи для указанного номера потребности, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unableToGrantThisRequirement(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Отсутствует возможность удовлетворить указанную потребность, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::wholeInputsInRequestingRequirementAreZero(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror В запросе потребности не указан ни один вход, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::requirementNameMustBeNonDescriptionName(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Имя потребности не может быть именем тэга, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}

int MessagePool::unableToUseShortNameTransitCircuit(const ParseInfo& info)
{
	this->pool.emplace_back(L"%compilationerror Невозможно использовать краткое имя транзитной цепи, в строке %row, позиция %pos.%br", info.row, info.pos);
	return 0;
}
