#pragma once

#include <string>
#include <unordered_map>

using std::wstring;
using std::unordered_map;

class Message
{
public:
	enum class MessageType
	{
		Error = 0,
		Warning,
	};

	Message(const wstring& message);
	Message(const wstring& message, const wstring& param1);
	Message(const wstring& message, const wstring& param1, const wstring& param2);
	Message(const wstring& message, int row);
	Message(const wstring& message, int row, const wstring& param1);
	Message(const wstring& message, int row, const wstring& param1, const wstring& param2);
	Message(const wstring& message, int row, int position);
	Message(const wstring& message, int row, int position, const wstring& param1);
	Message(const wstring& message, int row, int position, const wstring& param1, const wstring& param2);
	const wstring& getStringForConsole() const;
	const wstring& getStringForLog() const;
	bool isError() const;
	bool isWarning() const;

private:
	void constructStrings();

	MessageType messageType;
	wstring message;
	int row;
	int position;
	wstring param1;
	wstring param2;

	wstring stringForConsole;
	wstring stringForLog;

};

inline Message::Message(const wstring& message) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, const wstring& param1) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	param1(param1)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, const wstring& param1, const wstring& param2) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	param1(param1),
	param2(param2)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row, const wstring& param1) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row),
	param1(param1)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row, const wstring& param1, const wstring& param2) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row),
	param1(param1),
	param2(param2)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row, int position) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row),
	position(position)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row, int position, const wstring& param1) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row),
	position(position),
	param1(param1)
{
	this->constructStrings();
}

inline Message::Message(const wstring& message, int row, int position, const wstring& param1, const wstring& param2) :
	messageType(MessageType::Error),
	stringForConsole(message),
	stringForLog(message),
	row(row),
	position(position),
	param1(param1),
	param2(param2)
{
	this->constructStrings();
}

inline const wstring& Message::getStringForConsole() const
{
	return this->stringForConsole;
}

inline const wstring& Message::getStringForLog() const
{
	return this->stringForLog;
}

inline bool Message::isError() const
{
	return (this->messageType == MessageType::Error);
}

inline bool Message::isWarning() const
{
	return (this->messageType == MessageType::Warning);
}
