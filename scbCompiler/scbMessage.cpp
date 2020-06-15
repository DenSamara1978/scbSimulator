#include <utility>
#include "scbMessage.h"

void scbMessage::ConstructStrings ()
{
	if ( this->m_StringForConsole.find ( L"%compilationwarning" ) != wstring::npos )
		this->m_MessageType = MessageType::Warning;

	wstring substr, consoleStr, logStr;

	auto emplace = [&substr, &consoleStr, &logStr] ( wstring& console, wstring& log )
	{
		auto pos = console.find ( substr );
		auto length = substr.length ();
		if ( pos != wstring::npos )
			console.replace ( pos, length, consoleStr );
		pos = log.find ( substr );
		length = substr.length ();
		if ( pos != wstring::npos )
			log.replace ( pos, length, logStr );
	};

	substr = L"%compilationerror";
	consoleStr = L" - Ошибка компиляции :";
	logStr = L"<B style=\"color: red;\">Ошибка компиляции :</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%compilationwarning";
	consoleStr = L" - Предупреждение компиляции :";
	logStr = L"<B style=\"color: #E0A000;\">Предупреждение компиляции :</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%param1";
	consoleStr = this->m_Param1;
	logStr = L"<B style=\"color: fuchsia;\">" + this->m_Param1 + L"</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%param2";
	consoleStr = this->m_Param2;
	logStr = L"<B style=\"color: fuchsia;\">" + this->m_Param2 + L"</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%row";
	consoleStr = std::to_wstring ( this->m_Row) ;
	logStr = L"<B style=\"color: red;\">" + consoleStr + L"</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%pos";
	consoleStr = std::to_wstring ( this->m_Position );
	logStr = L"<B style=\"color: red;\">" + consoleStr + L"</B>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );

	substr = L"%br";
	consoleStr = L"";
	logStr = L"<BR>";
	emplace ( this->m_StringForConsole, this->m_StringForLog );
}
