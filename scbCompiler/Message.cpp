#include <utility>
#include "Message.h"

void Message::constructStrings()
{
	if (this->stringForConsole.find(L"%compilationwarning") != wstring::npos)
		this->messageType = MessageType::Warning;

	wstring substr, consoleStr, logStr;

	auto emplace = [&substr, &consoleStr, &logStr] (wstring& console, wstring& log)
	{
		auto pos = console.find(substr);
		auto length = substr.length();
		if (pos != wstring::npos)
			console.replace(pos, length, consoleStr);
		pos = log.find(substr);
		length = substr.length();
		if (pos != wstring::npos)
			log.replace(pos, length, logStr);
	};

	substr = L"%compilationerror";
	consoleStr = L" - Ошибка компиляции :";
	logStr = L"<B style=\"color: red;\">Ошибка компиляции :</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%compilationwarning";
	consoleStr = L" - Предупреждение компиляции :";
	logStr = L"<B style=\"color: #E0A000;\">Предупреждение компиляции :</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%param1";
	consoleStr = this->param1;
	logStr = L"<B style=\"color: fuchsia;\">" + this->param1 + L"</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%param2";
	consoleStr = this->param2;
	logStr = L"<B style=\"color: fuchsia;\">" + this->param2 + L"</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%row";
	consoleStr = std::to_wstring(this->row);
	logStr = L"<B style=\"color: red;\">" + consoleStr + L"</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%pos";
	consoleStr = std::to_wstring(this->position);
	logStr = L"<B style=\"color: red;\">" + consoleStr + L"</B>";
	emplace(this->stringForConsole, this->stringForLog);

	substr = L"%br";
	consoleStr = L"";
	logStr = L"<BR>";
	emplace(this->stringForConsole, this->stringForLog);
}
